#include <iostream>
#include <fstream>
#include <pthread.h>
#include "arguments.h"

using namespace std;

void result(string directory, string output) {
    ifstream fin(directory);
    int op;
    double number, res;
    string buff;
    if (!fin.is_open()) {
        cout << "Wrong file!" << endl;
        return;
    }
    else {
        getline(fin, buff);
        op = stoi(buff);
       
        res = op == 2 ? 1 : 0;
        getline(fin, buff);
        
        fin.close();
    }

    for (int i = 0; i < buff.length(); i++) {
        string tmp;
        while (isdigit(buff[i]) || buff[i] == '.') {
            tmp += buff[i];
            i++;
        }
        number = stod(tmp);
        switch (op) {
            case 1: {
                res += number;
                break;
            }
            case 2: {
                res *= number;
                break;
            }
            case 3: {
                res += number * number;
                break;
            }
            default: {
                cout << "Wrong operation!" << endl;
                return;
            }
        }
    }
    ofstream fout(output, ios_base::app);
    fout<<"Path: "<<directory<<", operation: "<<op<<", result: "<<res<<endl;
    fout.close();  
}

