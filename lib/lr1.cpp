#include "lr1.h"
#include <string>
#include <set>
#include <iostream>
using namespace std;


bool PRINT_STEP(int step) {
    cout << "[TEST OUTPUT] Step: " << step << "\n";
    return true;
}

pair<vector<pair<int, int>>, vector<string>> find_pairs(const vector<int>& arr) {
    vector<pair<int, int>> pairs;//1
    vector<string> errors;//1
    PRINT_STEP(1);

    if (arr.empty() && PRINT_STEP(2)) { //2
        errors.push_back("Array is empty");//3
        PRINT_STEP(3);
    }

    if (arr.size() > 1024 && PRINT_STEP(4)) {//4
        errors.push_back("Array length out of range");//5
        PRINT_STEP(5);
    }

    if (!errors.empty() && PRINT_STEP(6)) { //6
        PRINT_STEP(14);
        return make_pair(pairs, errors); //14
    }
    int fl7 = false;
    int fl8 = false;
    int fl9 = false;
    int fl10 = false;
    int fl11 = false;
    for (int i = 0; i < arr.size(); ++i) { //7
        if (!fl7) {
            PRINT_STEP(7);
            fl7 = true;
        }
        if (arr[i] % 5 == 0) { //8
            if (!fl8) {
                PRINT_STEP(8);
                fl8 = true;
            }
            for (int j = 0; j < arr.size(); ++j) {//9
                if (!fl9) {
                    PRINT_STEP(9);
                    fl9 = true;
                }
                if (arr[j] < 0) { //10
                    if (!fl10) {
                        PRINT_STEP(10);
                        fl10 = true;
                    }
                    pairs.push_back(make_pair(i, arr[i]));//11
                    pairs.push_back(make_pair(j, arr[j]));//11
                    if (!fl11) {
                        PRINT_STEP(11);
                        fl11 = true;
                    }
                    
                }
            }
        }
    }

    if (pairs.empty() && PRINT_STEP(12)) { //12
        errors.push_back("No pairs found");//13
        PRINT_STEP(13);
    }
    PRINT_STEP(14);
    return make_pair(pairs, errors);//14
}
