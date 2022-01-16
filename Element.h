#ifndef EXERCISE05_ELEMENT_H
#define EXERCISE05_ELEMENT_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

class Element {
private:
    double* x;
    double* t;
    int rank;
    int x_size;
    int t_size;
    bool flag;

public:
    Element();
    Element(double* x, double* t, int x_size, int t_size);
    void updateRank(int r);
    string toString();
    int getRank();
    bool getFlag();
    void setFlag(bool b);
    double getX(int i);
    void print_double(double d);
};


#endif
