#ifndef EXERCISE05_EX5_H
#define EXERCISE05_EX5_H

#include <fstream>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include "Element.h"

using namespace std;

class Ex5 {
private:
    double** xs;
    double** tv;
    int mu; // total x vectors. (i of xs matrix)
    int n;  // x vector's size. (j of xs matrix)
    int m;  // tv vector's size. (j of tv matrix)
    int iter;

public:
    Ex5(ifstream& ifs, string init_filename) {
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
//        if(count_lines(ifs) != mu) { quit(); }
        genXs(ifs, init_filename);
        genTv();
    }
    int count_lines(ifstream& ifs) {
        string temp;
        int lines = 0;
        while(getline(ifs, temp)){
            lines++;
        }
        ifs.clear();
        ifs.seekg(0, ios::beg);

        return lines;
    }
    int token_counter(string s){
        stringstream ss;
        string buffer;
        ss << s;
        int i = 0;
        while( getline(ss, buffer, ' ')) {
            i ++;
        }
        return i;
    }
    void tokenizer(string s, string *tokens) {
        stringstream ss;
        string buffer;
        ss << s;
        int i = 0;
        while( getline(ss, buffer, ' ')) {
            tokens[i] = buffer;
            i ++;
        }
    }
    void genXs(ifstream& ifs, string init_filename) {
        string line;
        getline(ifs, line);
        xs = new double*[mu];
        for(int i = 0; i < mu ; i ++ ) {
            xs[i] = new double[n];
        }
        int i=0;
        while(getline(ifs, line)) {
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
    void genTv() {
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
    double** genTv2(double** Xs, int size) {
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
    int* ParetoRanking(double** tv, int total_v, int v_size) {
        /** Algorithm which takes a set of target-vectors (tv) and calculates each vector's RANK.
         *  The RANK of a tv is the number of tvs that REIGN
         * @param tv array of t.vs
         * @param total_v total t.vs given
         * @param v_size the size of each t.v
         *
         * @return 1-D array of integers, with the ith represents the ith t.v ranks.
         */

        int* ranks = new int[total_v];
        bool cond1, cond2;
        for (int c = 0; c < total_v; c++) {
            ranks[c] = 0;
        }
        for (int i = 0; i < total_v; i++) { // check all tv.
            for (int j = i+1; j < total_v; j++) { // check tv[i] with all other vectors in his set.
                cond1 = false;
                cond2 = true;
                for (int e = 0; e < v_size; e++) {
                    if (tv[i][e] < tv[j][e]) { cond1 = true; }
                    if (tv[i][e] > tv[j][e]) { cond2 = false; }
                }

                if (cond1 && cond2) { // tv[i] reigns over tv[j]
                    ranks[j]++;
                }
                if (!cond1 && !cond2) { // tv[j] reigns over tv[i]
                    ranks[i]++;
                }
            }
        }

        return ranks;
    }
    void ElementsReordering(Element** elements, int size) {
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
    void ParetoSorting(Element** elements, double** tv, int size) {
        int* pr = ParetoRanking(tv, size, m);
        for(int i = 0; i < size; i ++) {  /// update ranking of all elements on array
            (*elements)[i].updateRank(pr[i]);
        }
        ElementsReordering(elements, size);
    }
    void simulate(ofstream& output_file) {
        Element* elem;      /// mu size
        Element* elem_temp; /// 2*mu size
        double** xs_temp;   /// 2*mu size
        double** tv_temp;   /// 2*mu size
        double r;

        elem = new Element[mu];
        for (int i = 0; i < mu; i ++) {
            elem[i] = Element(xs[i], tv[i], n, m);
        }

        int c = iter;
        while (c > 0) {
            xs_temp = new double*[2 * mu];
            elem_temp = new Element[2 * mu];

            srand((unsigned) time(0));

            for (int i = 0; i < 2 * mu; i++) {
                xs_temp[i] = new double[n];
                for (int j = 0; j < n; j++) {
                    if (i < mu) {
                        xs_temp[i][j] = elem[i].getX(j);
                    }
                    else {
                        r = (double) (rand() % 100);
                        r /= 100;
                        xs_temp[i][j] = elem->getX(i) + r;
                    }
                }
            }

            tv_temp = genTv2(xs_temp, 2 * mu);

            for (int i = 0; i < 2 * mu; i++) {
                elem_temp[i] = Element(xs_temp[i], tv_temp[i], n, m);
            }

            ParetoSorting(&elem_temp, tv_temp, 2 * mu);

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
};


#endif