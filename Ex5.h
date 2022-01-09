//
// Created by omri on 01/09/2022.
//

#ifndef EXERCISE05_EX5_H
#define EXERCISE05_EX5_H

#include <fstream>
#include <sstream>

using namespace std;

class Ex5 {
private:
    double** xs, **tv;
    int mu; // total x vectors. (i of xs matrix)
    int n;  // total x elements. (j of xs matrix)
    int m;  // total tv elements. (j of tv matrix)
    int iter;
public:
    Ex5(ifstream& ifs) {
        string line;
        getline(ifs, line, ' ');
        istringstream(line) >> mu;
        getline(ifs, line, ' ');
        istringstream(line) >> n;
        getline(ifs, line, ' ');
        istringstream(line) >> m;
        getline(ifs, line, ' ');
        istringstream(line) >> iter;
        if(count_lines(ifs) != mu) {
            quit();
        }
        getline(ifs, line);
        xs = new double*[mu];
        for(int i = 0; i < mu ; i ++ ) {
            xs[i] = new double[n];
        }
        int i=0;
        while(getline(ifs, line)) {
            if (token_counter(line) != n) {
                quit();
            }
            string tokens[n];
            tokenizer(line, tokens);
            for (int j = 0; j < n; j++) {
                istringstream(tokens[j]) >> xs[i][j];
            }
            i++;
        }
        generateTV();
        int* pr = ParetoRanking(tv, mu, m);
        for (int i = 0; i < m; i++) {
            cout << pr[i] << " ";
        }
    };
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
    void quit() { cerr << "ERROR: Invalid input."; exit(-1); }
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
    void generateTV() {
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
    int* ParetoRanking(double **tv, int total_v, int v_size) {
        /** an algorithm that takes a set of target-vectors (t.v) and calculates each vector's dimension.
         * @param tv array of t.vs
         * @param total_v total t.vs given
         * @param v_size the size of each t.v
         *
         * @return 1-D array of integers, with the ith represents the ith t.v dimension.
         */

        int* dims = new int[total_v];
        bool cond1, cond2;
        int c, dim;

        for (int i = 0; i < total_v; i++) { // check all tv.
            cond1 = false;
            cond2 = true;
            dim = 0;

            for (int j = 0; j < total_v; j++) { // check tv[i] with all other vectors in his set.
                if (i == j) { continue; }
                c = 0;
                for (int e = 0; e < v_size; e++) {
                    if (tv[i][e] < tv[j][e]) { cond1 = true; }
                    else if (! (tv[i][e] <= tv[j][e])) { cond1 = false; }
                }

                if (cond1 and cond2) { // tv[i] reigns over tv[j]
                    dim++;
                }
            }

            dims[i] = dim;
        }

        return dims;
    }
};


#endif //EXERCISE05_EX5_H


//for(int i = 0; i < mu; i ++) {
//    for(int e = 0; e < m; e ++) {
//        cout << tv[i][e] << ' ';
//    }
//    cout << endl;
//}