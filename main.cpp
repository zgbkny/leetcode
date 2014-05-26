#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include "include/ArrayCode.h"
using namespace std;


bool isValidSudoku(vector<vector<char> > &board)
{
    map<int, int> mp;
    int i = 0, j = 0, k = 0;
    for (i = 0; i < 9; i++) {
        vector<char> tmp = board[i];
        mp.clear();
        for (j = 0; j < 9; j++) {
            if (tmp[j] != '.' && (tmp[j] > 47 && tmp[j] < 58)) {
                if (mp[tmp[j]] > 0) return false;
            }
        }
    }
    for (i = 0; i < 9; i++) {
        mp.clear();
        for (j = 0; j < 9; j++) {
            vector<char> tmp = board[j];
            if (tmp[i] != '.' && (tmp[i] > 47 && tmp[i] < 58)) {
                if (mp[tmp[i]] > 0) return false;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mp.clear();
            for (k = 0; k < 3; k++) {

            }
        }
    }
    return true;
}
int bof(FILE *badfile){
    char buffer[20];
    fread(buffer, sizeof(char), 100, badfile);
    return 1;
}
int ArrayCode::tt = 0;
int main(){
    int n = 10;
    cout << n << endl;
    (void)n;
    cout << n << endl;
    /*FILE *badfile;
    badfile = fopen("badfile", "r");
    bof(badfile);
    printf("Returned Properly\n");
    fclose(badfile);


    static int64_t hh = 999;
    int64_t &hs = hh;
    cout << hs << endl;

    ArrayCode ac;
    ac.set();
    cout << ac.h << endl;

    ArrayCode ac;

    ac.init();
    ac.output();*/
    return 0;
}
