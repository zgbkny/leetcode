#ifndef DFSCODE_H_INCLUDED
#define DFSCODE_H_INCLUDED
#include <vector>
#include <string>
#include <iostream>

using namespace std;
bool check(string &str) {
    int i = 0, j = str.length() - 1;
    for ( ; i < j; i++, j--) {
        if (str[i] != str[j]) return false;
    }
    return true;
}

void dfs_patition(string s, int start, vector<vector<string> >&ret, vector<string> item) {
    if (start == s.length()) {
        ret.push_back(item);
    }
    for (int i = start + 1; i <= s.length(); i++) {
        string subs = s.substr(start, i - start);
        if (check(subs)) {
            item.push_back(subs);
            dfs_patition(s, i, ret, item);
            item.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string> > ret;
    vector<string> item;
    dfs_patition(s, 0, ret, item);
    return ret;
}

void dfs_patition(string s, int start, int *ret, vector<string> item) {
    if (start == s.length()) {
        if (item.size() < *ret) {
            *ret = item.size();
        }
    }
    for (int i = start + 1; i <= s.length(); i++) {
        string subs = s.substr(start, i - start);
        if (check(subs)) {
            item.push_back(subs);
            dfs_patition(s, i, ret, item);
            item.pop_back();
        }
    }
}





#endif // DFSCODE_H_INCLUDED
