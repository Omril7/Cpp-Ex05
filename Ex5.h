#ifndef EXERCISE05_EX5_H
#define EXERCISE05_EX5_H

#include <iostream>
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
    Ex5(ifstream& ifs, string init_filename);
    int count_lines(ifstream& ifs);
    int token_counter(string s);
    void tokenizer(string s, string *tokens);
    void genXs(ifstream& ifs, string init_filename);
    void genTv();
    double** genTv2(double** Xs, int size);
    template<typename T> int* ParetoRankingGen(T** tv, int total_v, int v_size) {
        /** Algorithm which takes a set of target-vectors (tv) and calculates each vector's RANK.
         *  The RANK of a tv is the number of tvs that REIGN
         *  '<' and '>' operators must be overloaded for T type.
         * @param tv array of t.vs
         * @param total_v total t.vs given
         * @param v_size the size of each t.v
         *
         * @return 1-D array of integers, with the ith represents the ith t.v ranks.
         */

        int *ranks = new int[total_v];
        bool cond1, cond2;
        for (int c = 0; c < total_v; c++) {
            ranks[c] = 0;
        }
        for (int i = 0; i < total_v; i++) { // check all tv.
            for (int j = i + 1; j < total_v; j++) { // check tv[i] with all other vectors in his set.
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
    };
    void ElementsReordering(Element** elements, int size);
    template<typename T> void ParetoSortingGen(Element** elements, T** tv, int size) {
        /**
         * '<' and '>' operators must be overloaded for T type.
         **/
        int* pr = ParetoRankingGen<T>(tv, size, m);
        for(int i = 0; i < size; i ++) {  /// update ranking of all elements on array
            (*elements)[i].updateRank(pr[i]);
        }
        ElementsReordering(elements, size);
    };
    void simulate(ofstream& output_file);
};


#endif