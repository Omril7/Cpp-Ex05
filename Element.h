//
// Created by omril on 01/10/2022.
//

#ifndef EXERCISE05_ELEMENT_H
#define EXERCISE05_ELEMENT_H


class Element {
private:
    double* x;
    double* t;
    int rank;
    int x_size;
    int t_size;
public:
    Element(double* x, double* t, int x_size, int t_size) {
        this->x = x;
        this->t = t;
        this->x_size = x_size;
        this->t_size = t_size;
        rank = 0;
    }
    void updateRank(int r) {
        rank = r;
    }
    void printX(){
        for(int i = 0; i < x_size ; i ++) {
            std::cout << x[i] << ' ';
        }
    }
    void printT(){
        for(int i = 0; i < t_size ; i ++) {
            std::cout << t[i] << ' ';
        }
    }
    void printRank(){
        std::cout << rank;
    }
};


#endif //EXERCISE05_ELEMENT_H
