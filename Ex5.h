//
// Created by omri on 01/09/2022.
//

#ifndef EXERCISE05_EX5_H
#define EXERCISE05_EX5_H

#include <fstream>
#include <sstream>

using namespace std;

class Ex5 {
private:
    double** Xs, **TV;
    int mu, n, m, iter;
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
        Xs = new double*[mu];
        for(int i = 0; i < mu ; i ++ ) {
            Xs[i] = new double[n];
        }
        int i=0;
        while(getline(ifs, line)) {
            if (token_counter(line) != n) {
                quit();
            }
            string tokens[n];
            tokenizer(line, tokens);
            for (int j = 0; j < n; j++) {
                istringstream(tokens[j]) >> Xs[i][j];
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
        TV = new double* [mu];
        for(int i = 0; i < mu; i ++) {
            TV[i] = new double[m];
            for(int e = 0; e < m; e ++) {
                TV[i][e] = 0;
                for(int j = 0; j < n; j ++) {
                    TV[i][e] += ((Xs[i][j] - (e + 1)) * (Xs[i][j] - (e + 1)));
                }
            }
        }
    }

};


#endif //EXERCISE05_EX5_H


//for(int i = 0; i < mu; i ++) {
//    for(int e = 0; e < m; e ++) {
//        cout << TV[i][e] << ' ';
//    }
//    cout << endl;
//}