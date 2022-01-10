//
// Created by omri on 01/09/2022.
//

#ifndef EXERCISE05_EX5_H
#define EXERCISE05_EX5_H

#include "Element.h"

#include <fstream>
#include <sstream>

using namespace std;

class Ex5 {
private:
    double** xs; // variable-vectors. (mu x n)
    double **tv; // target-vectors matrix. (mu x m)
    int mu;      // total x vectors. (i of xs matrix)
    int n;       // total x elements. (j of xs matrix)
    int m;       // total tv elements. (j of tv matrix)
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
    int* ParetoRanking(double **tv, int size, int dim) {
        /** an algorithm that takes a set of target-vectors (tv) and calculates each tv RANK.
         *  the RANK of a tv is the number of other vectors within his set that REIGN over him:
         *      for every i:    tv[a][i] <= tv[b][i]
         *      a j exists:     tv[a][j] < tv[b][j]
         *      then tv j REIGNS over tv i.
         *
         * @param tv array of tvs.
         * @param size total tvs given.
         * @param dim dimension of each tv.
         *
         * @return 1-D array of integers, with the ith represents the ith tv dimension.
         */

        int* ranks = new int[size];
        bool cond1, cond2;
        int rank;

        for (int i = 0; i < size; i++) {
            cond1 = false;
            cond2 = true;
            rank = 0;
            for (int j = 0; j < size; j++) { // check tv[i] with all other vectors in his set.
                if (i == j) { continue; } // don't check tv with itself.
                for (int e = 0; e < dim; e++) {
                    if (tv[i][e] < tv[j][e]) { cond1 = true; }
                    else if (! (tv[i][e] <= tv[j][e])) { cond1 = false; }
                }
                if (cond1 and cond2) { // tv[j] reigns over tv[i], then dim of tv[i] increments.
                    rank++;
                }
            }

            ranks[i] = rank;
        }

        return ranks;
    }
    void ElementsReordering(Element** element_arr, int size) {
        Element* copy = new Element[size];
        int* ranks = ParetoRanking()
        for (int i = 0; i < size; i++) {

        }

    }
};


#endif //EXERCISE05_EX5_H


//for(int i = 0; i < mu; i ++) {
//    for(int e = 0; e < m; e ++) {
//        cout << tv[i][e] << ' ';
//    }
//    cout << endl;
//}