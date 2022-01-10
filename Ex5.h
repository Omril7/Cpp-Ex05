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
    int* ParetoRanking(double** tv, int total_v, int v_size);
    void ElementsReordering(Element** elements, int size);
    void ParetoSorting(Element** elements, double** tv, int size);
    void simulate(ofstream& output_file);
};


#endif