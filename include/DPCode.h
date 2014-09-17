#ifndef DPCODE_H_INCLUDED
#define DPCODE_H_INCLUDED

#include <vector>
#include <iostream>
#include <string>

int minimumTotal(vector<vector<int> > &triangle) {
    int sum = 0;
    for (int i = triangle.size() - 2; i >= 0; i--) {
        for (int j = 0; j < triangle[i].size(); j++) {
            triangle[i][j] = min(triangle[i + 1][j], triangle[i + 1][j + 1]) + triangle[i][j];
        }
    }
    return triangle[0][0];
}

int maxSubArray(int A[], int n) {
    int sum = A[0];
    for (int i = 1; i < n; i++) {
        A[i] = max(A[i - 1] + A[i], A[i]);
        if (A[i] > sum) {
            sum = A[i];
        }
    }
    return max(sum, A[n - 1]);
}

int minCut(string s) {

}

int largestRectangleArea(int* height, int length) {
    stack<int> stk;
    int i = 0;
    int maxArea = 0;
    while(i < length){
        if(stk.empty() || height[stk.top()] <= height[i]){
            stk.push(i++);
        }else {
            int t = stk.top();
            stk.pop();
            int area = height[t] * (stk.empty() ? i : i - stk.top() - 1);
            maxArea = maxArea > area ? maxArea : area;
        }
    }
    return maxArea;
}

int maximalRectangle(vector<vector<char> > &matrix) {
    int m = matrix.size();
    if (m == 0) return 0;
    int n = matrix[0].size();
    if (n == 0) return 0;

    int **dp = new int*[m];
    for (int i = 0; i < m; i++) {
        dp[i] = new int[n + 1];
        memset(dp[i], 0, sizeof(int)*(n+1));
    }
    for(int j = 0; j < n; ++j)
        if(matrix[0][j] == '1')dp[0][j] = 1;
    for(int j = 0; j < n; ++j)
        for(int i = 1; i < m; ++i)
            if(matrix[i][j] == '1') dp[i][j] = dp[i-1][j] + 1;

    int maxarea = 0;
    for(int i = 0; i < m; ++i){
        int tmp = largestRectangleArea(dp[i],n+1);
        if(tmp > maxarea)
            maxarea = tmp;
    }

    for(int i = 0; i < m; ++i)
        delete[] dp[i];
    delete[] dp;

    return maxarea;
}

int maxProfit(vector<int> &prices) {
    int sum = 0, min_num = INT_MAX;
    stack<int> tmp;
    for (int i = 0; i < prices.size(); ) {
        if (tmp.empty() || tmp.top() < prices[i]) {
            if (tmp.empty())
                min_num = prices[i];
            tmp.push(prices[i]);
            i++;
        } else {
            if (tmp.size() == 1) {
                tmp.pop();
                tmp.push(prices[i]);
                min_num = prices[i];
                i++;
            } else {
                int tmp_profit = tmp.top() - min_num;
                sum = sum < tmp_profit ? tmp_profit : sum;
                tmp.pop();
            }
        }
    }
    if (!tmp.empty()) {
        int tmp_profit = tmp.top() - min_num;
        sum = sum < tmp_profit ? tmp_profit : sum;
    }
    return sum;
}

int maxProfit1(vector<int> &prices) {
    int sum = 0, min_num = INT_MAX, tmp = INT_MIN;
    prices.push_back(INT_MIN);
    if (prices.size() > 0) tmp = min_num = prices[0];
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > tmp) tmp = prices[i];
        else {
            sum += tmp - min_num;
            min_num = tmp = prices[i];
        }
    }
    return sum;
}
/*
bool wordBreak1(string s, unordered_set<string> &dict) {
    vector<bool> f(s.size() + 1, false);
    f[0] = true;
    for (int i = 1; i < s.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (f[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
					f[i] = true;
					break;
				}
			}
		}
	return f[s.size()];
}
void wordBreakDfs(string &s, int start, unordered_set<string> &dict, vector<string> &ret, string &tmp) {
    if (start >= s.size()) {
        tmp.replace(tmp.size() - 1, tmp.size(), "");
        ret.push_back(tmp);
    } else {
        for (int i = start + 1; i <= s.size(); i++) {
            if (dict.find(s.substr(start, i - start)) != dict.end()) {
                int ss = s.substr(start, i - start).size() + 1;
                tmp += s.substr(start, i - start);
                tmp += " ";
                wordBreakDfs(s, i, dict, ret, tmp);
                tmp.replace(tmp.size() - ss, tmp.size(), "");
            }
        }
    }
}


vector<string> wordBreak(string s, unordered_set<string> &dict) {
    vector<string> ret;
    string tmp = "";
    wordBreakDfs(s, 0, dict, ret, tmp);
    return ret;
}

void gen_path(const string &s, const vector<vector<bool> > &prev,
    int cur, vector<string> &path, vector<string> &result) {
    if (cur == 0) {
        string tmp;
        for (auto iter = path.crbegin(); iter != path.crend(); ++iter)
        tmp += *iter + " ";
        tmp.erase(tmp.end() - 1);
        result.push_back(tmp);
    }
    for (size_t i = 0; i < s.size(); ++i) {
        if (prev[cur][i]) {
            path.push_back(s.substr(i, cur - i));
            gen_path(s, prev, i, path, result);
            path.pop_back();
        }
    }
}



vector<string> wordBreak(string s, unordered_set<string> &dict) {
    // 长度为n 的字符串有n+1 个隔板
    vector<bool> f(s.length() + 1, false);
    // prev[i][j] 为true，表示s[j, i) 是一个合法单词，可以从j 处切开
    // 第一行未用
    vector<vector<bool> > prev(s.length() + 1, vector<bool>(s.length()));
    f[0] = true;
    for (size_t i = 1; i <= s.length(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (f[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
                f[i] = true;
                prev[i][j] = true;
            }
        }
    }
    vector<string> result;
    vector<string> path;
    gen_path(s, prev, s.length(), path, result);
    return result;
}

void gen_path(const string &s, const vector<vector<bool> > &prev,
    int cur, vector<string> &path, vector<string> &result) {
    if (cur == 0) {
        string tmp;
        for (auto iter = path.crbegin(); iter != path.crend(); ++iter)
        tmp += *iter + " ";
        tmp.erase(tmp.end() - 1);
        result.push_back(tmp);
    }
    for (size_t i = 0; i < cur; ++i) {
        if (prev[i][cur]) {
            path.push_back(s.substr(i, i - cur));
            gen_path(s, prev, i, path, result);
            path.pop_back();
        }
    }
}



vector<string> wordBreak(string s, unordered_set<string> &dict) {
    // 长度为n 的字符串有n+1 个隔板
    vector<bool> f(s.length() + 1, false);
    // prev[i][j] 为true，表示s[j, i) 是一个合法单词，可以从j 处切开
    // 第一行未用
    vector<vector<bool> > prev(s.length(), vector<bool>(s.length() + 1));
    f[0] = true;
    for (int i = 1; i <= s.size(); i++) {
        for (int j = i - 1; j >=0; j--) {
            if (f[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
                f[i] = true;
                prev[j][i] = true;
            }
        }
    }
    vector<string> result;
    vector<string> path;
    gen_path(s, prev, s.size(), path, result);
    return result;
}*/

int numDistinct(string S, string T) {
    if (S.size() < T.size()) return 0;
    vector<vector<int> > dp(S.size() + 1, vector<int>(T.size() + 1, 0));
    for (int i = 0; i < S.size(); i++) {
        for (int j = 0; j < T.size() && j <= i; j++) {
            if (S[i] == T[j]) {
                dp[i + 1][j + 1] = dp[i][j + 1] + dp[i][j];
                // handle edge
                if (j == 0) dp[i + 1][j + 1] += 1;
            } else {
                dp[i + 1][j + 1] = dp[i][j + 1];
            }
        }
    }
    return dp[S.size()][T.size()];
}

int decodeStr(string s) {
    int tmp = 0;
    for (int i = 0; i < s.size(); i++) {
        tmp = tmp * 10 + s[i] - 30;
    }
    return tmp;
}

void dfsDecode(string s, int cur, vector<vector<bool> > &dp, int *sum) {
    cout << "dfsDecode" << endl;
    if (cur == 0) {
        (*sum)++;
    }
    for (int i = cur - 1; i >= 0 && i >= cur - 2; i--) {
        if (dp[i][cur]) dfsDecode(s, i, dp, sum);
    }
}

int numDecodings1(string s) {
    if (s.size() == 0) return 0;
    vector<bool> f(s.size() + 1, false);
    vector<vector<bool> > dp(s.size() + 1, vector<bool> (s.size() + 1, false));
    f[0] = true;
    for (int i = 1; i <= s.size(); i++) {
        for (int j = i - 1; j >= 0 && j >= i - 2; j--) {
            int tmp = decodeStr(s.substr(j, i - j));
            if (f[j] && i - j < 3 && tmp > 0 && tmp < 27) {
                f[i] = true;
                dp[j][i] = true;
            }
        }
    }
    int sum = 0;
    cout << dp[0][1] << endl;
    dfsDecode(s, s.size(), dp, &sum);
    return sum;
}

int numDecodings(const string &s) {
    if (s.empty() || s[0] == '0') return 0;
    int prev = 0;
    int cur = 1;
    // 长度为n 的字符串，有n+1 个阶梯
    cout << "i:" << 0 << "prev:" << prev << "cur:" << cur << endl;

    for (size_t i = 1; i <= s.size(); ++i) {
        if (s[i-1] == '0') cur = 0;
        if (i < 2 || !(s[i - 2] == '1' ||
                (s[i - 2] == '2' && s[i - 1] <= '6')))
            prev = 0;
        cout << "i:" << i << "prev:" << prev << "cur:" << cur << endl;
        int tmp = cur;
        cur = prev + cur;
        prev = tmp;
        cout << "i:" << i << "prev:" << prev << "cur:" << cur << endl;
    }
    return cur;
}

int minDistance(const string &word1, const string &word2) {
    const size_t n = word1.size();
    const size_t m = word2.size();
    // 长度为n 的字符串，有n+1 个隔板
    int f[n + 1][m + 1];
    for (size_t i = 0; i <= n; i++)
        f[i][0] = i;
    for (size_t j = 0; j <= m; j++)
        f[0][j] = j;
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            if (word1[i - 1] == word2[j - 1])
                f[i][j] = f[i - 1][j - 1];
            else {
                int mn = min(f[i - 1][j], f[i][j - 1]);
                f[i][j] = 1 + min(f[i - 1][j - 1], mn);
            }
        }
    }
    return f[n][m];
}

int minPathSum(vector<vector<int> > &grid) {
    int m = grid.size();
    if (m == 0) return 0;
    int n = grid[0].size();
    if (n == 0) return 0;
    vector<vector<int> > f(m + 1, vector<int> (n + 1, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                f[i + 1][j + 1] = f[i][j + 1] + grid[i][j];
                continue;
            }
            if (i == 0) {
                f[i + 1][j + 1] = f[i + 1][j] + grid[i][j];
                continue;
            }
            f[i + 1][j + 1] = min(f[i][j + 1], f[i + 1][j]) + grid[i][j];
        }
    }
    return f[m][n];
}
int maxProfit12(vector<int> &prices) {
    if (prices.size() < 2) return 0;
    vector<int> f(prices.size(), 0);
    vector<int> g(prices.size(), 0);
    for (int i = 1, valley = prices[0]; i < prices.size(); ++i) {
        valley = min(valley, prices[i]);
        f[i] = max(f[i - 1], prices[i] - valley);
    }
    for (int i = prices.size() - 2, peak = prices[prices.size() - 1]; i >= 0; --i) {
        peak = max(peak, prices[i]);
        g[i] = max(g[i], peak - prices[i]);
    }
    int max_profit = 0;
    for (int i = 0; i < prices.size(); ++i)
        max_profit = max(max_profit, f[i] + g[i]);
    return max_profit;
}

bool isInterleave(string s1, string s2, string s3) {
    int i = 0, j = 0, z = 0;
    for (i = 0, j = 0, z = 0; z < s3.size() && j <= s2.size() && i <= s1.size(); z++) {
        bool ret = s1[i] == s3[z];
        if (i < s1.size() && s1[i] == s3[z]) {
            i++;
        } else if (j < s2.size() && s2[j] == s3[z]) {
            j++;
        } else
            break;
    }
    return (z == s3.size() && j == s2.size() && i == s1.size());
}
bool isInterleave(string s1, string s2, string s3) {
    if (s3.length() != s1.length() + s2.length())
        return false;
    vector<vector<bool>> f(s1.length() + 1,
    vector<bool>(s2.length() + 1, true));
    for (size_t i = 1; i <= s1.length(); ++i)
        f[i][0] = f[i - 1][0] && s1[i - 1] == s3[i - 1];
    for (size_t i = 1; i <= s2.length(); ++i)
        f[0][i] = f[0][i - 1] && s2[i - 1] == s3[i - 1];
    for (size_t i = 1; i <= s1.length(); ++i)
        for (size_t j = 1; j <= s2.length(); ++j)
            f[i][j] = (s1[i - 1] == s3[i + j - 1] && f[i - 1][j])
            || (s2[j - 1] == s3[i + j - 1] && f[i][j - 1]);
    return f[s1.length()][s2.length()];
}

bool isScramble(string s1, string s2) {
    const int N = s1.size();
    if (s1.size() != s2.size()) return false;

    bool f[N + 1][N][N];
    fill_n(&f[0][0][0], (N + 1) * N * N, false);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            f[1][i][j] = s1[i] == s2[j];

    for (int n = 2; n <= N; n++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 1; k < n; k++) {
                    if ((f[k][i][j] && f[n - k][i + k][j + k]) ||
                                (f[k][i][j + n - k] && f[n - k][i + k][j])) {
                        f[n][i][j] = true;
                        break;
                    }
                }
            }
        }
    }
    return f[N][0][0];
}


#endif // DPCODE_H_INCLUDED
