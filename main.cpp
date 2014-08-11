#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include "include/ArrayCode.h"
#include "include/StringCode.h"
#include "include/TreeCode.h"
using namespace std;



int main()
{

    unsigned short us = 100000;
    float f = 100000000000;
    cout << f;
    cout << (int)us << endl;
    string s(".,");
    char *test1 = "aaa";
    char *test2 = "()()";

    StringCode sc;
    cout << sc.longestValidParentheses(test2);
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
