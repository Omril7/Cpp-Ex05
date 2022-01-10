#include <iostream>

#include "Ex5.h"
int main(int argc, char** argv) {
    if(argc != 3) { cerr << "ERROR: Invalid input."; }
    ifstream init_file(argv[1]);
    ofstream output_file(argv[2]);
    if (!init_file) { cerr << "ERROR: Invalid input." << endl; exit(-1); }
    //if (!output_file) { cerr << "ERROR: Invalid input." << endl; exit(-1); }

    Ex5* ex5 = new Ex5(init_file);

    Element e;
    return 0;
}
