#include <iostream>

#include "Ex5.h"
int main(int argc, char** argv) {
    if(argc != 3) {
        cerr << "ERROR: Invalid input.";
    }
    ifstream ifs(argv[1]);
    Ex5* ex5 = new Ex5(ifs);


    return 0;
}
