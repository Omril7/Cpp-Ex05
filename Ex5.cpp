#include "Ex5.h"

Ex5::Ex5(ifstream& ifs, string init_filename) {
    string line;
    for (int i = 0; i < 4; i++) {
        if (getline(ifs, line, ' ')) {
            switch (i) {
                case 0: istringstream(line) >> mu; break;
                case 1: istringstream(line) >> n; break;
                case 2: istringstream(line) >> m; break;
                case 3: istringstream(line) >> iter; break;
            }
        }
        else {
            cerr << "ERROR: simulation definition in " << init_filename << " is invalid\n"; exit(-1);
        }
    }
    if ((count_lines(ifs) != mu) or (mu > 10000) or (m >= n) or (n > 100)) {
        cerr << "ERROR: simulation definition in " << init_filename << " is invalid\n";
        exit(-1);
    }
    genXs(ifs, init_filename);
    genTv();
}
int Ex5::count_lines(ifstream& ifs) {
    string temp;
    int lines = 0;
    while (getline(ifs, temp)){
        lines++;
    }
    ifs.clear();
    ifs.seekg(0, ios::beg);

    return lines;
}
int Ex5::token_counter(string s){
    stringstream ss;
    string buffer;
    ss << s;
    int i = 0;
    while (getline(ss, buffer, ' ')) {
        i ++;
    }
    return i;
}
void Ex5::tokenizer(string s, string *tokens) {
    stringstream ss;
    string buffer;
    ss << s;
    int i = 0;
    while (getline(ss, buffer, ' ')) {
        tokens[i] = buffer;
        i ++;
    }
}
void Ex5::genXs(ifstream& ifs, string init_filename) {
    string line;
    getline(ifs, line);
    xs = new double*[mu];
    for (int i = 0; i < mu ; i ++ ) {
        xs[i] = new double[n];
    }
    int i=0;
    while (getline(ifs, line)) {
        if (token_counter(line) != n) {
            cerr << "ERROR: population definition in " << init_filename << " at line " << i << " is invalid\n"; exit(-1);
        }
        string tokens[n];
        tokenizer(line, tokens);
        for (int j = 0; j < n; j++) {
            istringstream(tokens[j]) >> xs[i][j];
        }
        i++;
    }
}
void Ex5::genTv() {
    tv = new double* [mu];
    for(int i = 0; i < mu; i ++) {
        tv[i] = new double[m];
        for(int e = 0; e < m; e ++) {
            tv[i][e] = 0;
            for(int j = 0; j < n; j ++) {
                tv[i][e] += ((xs[i][j] - (e + 1)) * (xs[i][j] - (e + 1)));
            }
        }
    }
}
double** Ex5::genTv2(double** Xs, int size) {
    double** mytv = new double*[size];
    for(int i = 0; i < size; i ++) {
        mytv[i] = new double[m];
        for(int e = 0; e < m; e ++) {
            mytv[i][e] = 0;
            for(int j = 0; j < n; j ++) {
                mytv[i][e] += ((Xs[i][j] - (e + 1)) * (Xs[i][j] - (e + 1)));
            }
        }
    }
    return mytv;
}
void Ex5::ElementsReordering(Element** elements, int size) {
    Element cpy[size];
    int minRank;
    for(int i = 0; i < size; i ++) {
        minRank = size;
        for(int j = 0; j < size; j ++) {
            if((*elements)[j].getRank() < minRank && (! (*elements)[j].getFlag())) {
                minRank = (*elements)[j].getRank();
            }
        }
        int tempRank = minRank;
        for(int j = 0; j < size; j ++) {
            if( ((*elements)[j].getRank() == tempRank) && (! (*elements)[j].getFlag()) ) {
                cpy[i] = (*elements)[j];
                (*elements)[j].setFlag(true);
                break;
            }
        }
    }
    for(int i = 0; i < size; i ++) {
        (*elements)[i] = cpy[i];
    }
}
void Ex5::simulate(ofstream& output_file) {
    Element* elem;      /// mu size
    Element* elem_temp; /// 2*mu size
    double** xs_temp;   /// 2*mu size
    double** tv_temp;   /// 2*mu size
    double r;

    elem = new Element[mu];
    for (int i = 0; i < mu; i ++) {
        elem[i] = Element(xs[i], tv[i], n, m);
    }

    xs_temp = new double*[2 * mu];
    for (int i = 0; i < 2 * mu; i++) {
        xs_temp[i] = new double[n];
    }
    elem_temp = new Element[2 * mu];

    int c = iter;
    while (c > 0) {
        srand((unsigned) time(0));
        for (int i = 0; i < 2 * mu; i++) {
            for (int j = 0; j < n; j++) {
                if (i < mu) {
                    xs_temp[i][j] = elem[i].getX(j);
                }
                else {
                    r = (double) (rand() % 1000);
                    r /= 1000;
                    xs_temp[i][j] = elem->getX(i) + r;
                }
            }
        }

        tv_temp = genTv2(xs_temp, 2 * mu);

        for (int i = 0; i < 2 * mu; i++) {
            elem_temp[i] = Element(xs_temp[i], tv_temp[i], n, m);
        }

        ParetoSortingGen<double>(&elem_temp, tv_temp, 2 * mu);

        for (int i = 0; i < mu; i++) {
            elem[i] = elem_temp[i];
        }
        c--;
    }
    for(int i = 0; i < mu ; i ++) {
        output_file << elem[i].toString();
        if(i < mu-1) {
            output_file << endl;
        }
    }
}
