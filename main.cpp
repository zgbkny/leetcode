#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include "include/ArrayCode.h"
#include "include/StringCode.h"

using namespace std;



int main(){
    string s(".,");
    char *test1 = "aaa";
    char *test2 = "sdfg world ";

    StringCode sc;
    cout << sc.lengthOfLastWord(test2);
    //cout << sc.strStr(test1, test2);
        /*vector<int> a;
    a.push_back(0);
    a.push_back(1);
    vector<vector<int> >data;
    data.push_back(a);
    ArrasyCode ac;
    //ac.getPermutation(9, 130453);
    ac.setZeroes(data);
    cout << a[1];*/
    return 0;
}
