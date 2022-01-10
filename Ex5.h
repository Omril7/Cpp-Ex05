//
// Created by omri on 01/09/2022.
//

#ifndef EXERCISE05_EX5_H
#define EXERCISE05_EX5_H

#include <fstream>
#include <sstream>
#include <iterator>
#include "Element.h"

using namespace std;

class Ex5 {
private:
    double** xs, **tv;
    int mu; // total x vectors. (i of xs matrix)
    int n;  // x vector's size. (j of xs matrix)
    int m;  // tv vector's size. (j of tv matrix)
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

//        Element* elements = new Element[mu];
//        for(int i = 0; i < mu ; i ++) {
//            elements[i] = Element(xs[i], tv[i], n, m);
//        }
//        ParetoSorting(&elements, mu);
//        for(int i = 0; i < mu ; i ++) {
//            elements[i].printT();
//            cout << endl;
//        }
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
    int* ParetoRanking(double** tv, int total_v, int v_size) {
        /** an algorithm that takes a set of target-vectors (t.v) and calculates each vector's ranks.
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
    void ParetoSorting(Element** elements, int size) {
        int* pr = ParetoRanking(tv, mu, m);
        for(int i = 0; i < mu; i ++) {  /// update ranking of all elements on array
            (*elements)[i].updateRank(pr[i]);
        }
        ElementsReordering(elements, mu);
    }


    void init() {
        while(iter >0) {


            iter --;
        }
    }
};


#endif //EXERCISE05_EX5_H