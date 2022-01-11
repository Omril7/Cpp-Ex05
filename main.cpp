
#include "Ex5.h"

int main(int argc, char** argv) {
    if (argc != 3) { cerr << "ERROR: Invalid input." << endl; exit(-1); }
    ifstream init_file(argv[1]);
    ofstream output_file(argv[2]);
    if (!init_file) { cerr << "ERROR: " << argv[1] << "does not exist or cannot be opened\n"; exit(-1); }
    if (!output_file) { cerr << "ERROR: " << argv[2] << "does not exist or cannot be opened\n"; exit(-1); }

    Ex5* ex5 = new Ex5(init_file, argv[1]);
    ex5->simulate(output_file);

    return 0;
}