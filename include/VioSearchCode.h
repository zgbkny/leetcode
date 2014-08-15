#ifndef VIOSEARCHCODE_H_INCLUDED
#define VIOSEARCHCODE_H_INCLUDED
#include <vector>
#include <algrithm>

void subsets(vector<int> &S, vector<vector<int> > &ret, vector<int> &val, int n) {
    if (n == S.size()) {
        ret.push_back(val);
        return;
    }
    int tmp = val.size();
    subsets(S, ret, val, n + 1);
    val.push_back(S[n]);
    subsets(S, ret, val, n + 1);
    val.pop_back();
}

vector<vector<int> > subsets1(vector<int> &S) {
    vector<vector<int> > ret;
    vector<int> val;
    sort(S.begin(), S.end());
    subsets(S, ret, val, 0);
    return ret;
}

void dfs(const vector<int> &S, vector<int>::iterator start,
        vector<int> &path, vector<vector<int> > &result) {
    result.push_back(path);
    for (auto i = start; i < S.end(); i++) {
        if (i != start && *i == *(i-1)) continue;
        path.push_back(*i);
        dfs(S, i + 1, path, result);
        path.pop_back();
    }
}
vector<vector<int> > subsetsWithDup(vector<int> &S) {
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
    sort(S.begin(), S.end()); // ±ÿ–Î≈≈–Ú
    vector<vector<int> > result;
    vector<int> path;
    dfs(S, S.begin(), path, result);
    return result;
}

#endif // VIOSEARCHCODE_H_INCLUDED
