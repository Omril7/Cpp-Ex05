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
    bool flag;
public:
    Element() {
        x = NULL;
        t = NULL;
        x_size = 0;
        t_size = 0;
        rank = 0;
        flag = false;
    }
    Element(double* x, double* t, int x_size, int t_size) {
        this->x = x;
        this->t = t;
        this->x_size = x_size;
        this->t_size = t_size;
        rank = 0;
        flag = false;
    }
//    Element& operator=(Element& other) {
//        if(this != &other) {
//            x = other.x;
//            t = other.t;
//            rank = other.rank;
//            x_size = other.x_size;
//            t_size = other.t_size;
//        }
//        return *this;
//    }
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
    int getRank() {
        return rank;
    }
    bool getFlag() {
        return flag;
    }
    void setFlag(bool b) {
        flag = b;
    }
};


#endif //EXERCISE05_ELEMENT_H
