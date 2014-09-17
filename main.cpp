#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include "include/ArrayCode.h"
#include "include/StringCode.h"
#include "include/TreeCode.h"
#include "include/DPCode.h"
using namespace std;



int main()
{
    string s1 = "a";
    string s2 = "";
    string s3 = "a";
               // 012345678
    vector<vector<int> > v(2, vector<int> (2,1));
    cout << endl << isInterleave(s1,s2,s3);
    cout.width(7);
    cout.setf(ios::showpoint);
    cout << 1.0;

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
