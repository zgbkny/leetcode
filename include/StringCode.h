#ifndef STRINGCODE_H_INCLUDED
#define STRINGCODE_H_INCLUDED
#include <string>
#include <iostream>
#include <map>
#include <stack>
using namespace std;
class StringCode
{
public:
    char change(char c)
    {
        if (c >= 'a' && c <= 'z') {
            return c;
        }
        if (c >= 'A' && c <= 'Z') {
            return c - ('A' - 'a');
        }
        if (c >= '0' && c <= '9') return c;
        return 0;
    }
    bool isPalindrome(string s)
    {
        if (!s.size()) return true;
        int i = 0, j = s.size() - 1;
        for ( ; i < j; ) {
            if (change(s[i]) && change(s[j])) {
                if (change(s[i]) == change(s[j])) {
                    i++;
                    j--;
                } else {
                    return false;
                }
            }
            if (!change(s[i]) && change(s[j])) i++;
            if (change(s[i]) && !change(s[j])) j--;
            if (!change(s[i]) && !change(s[j])) {
                i++;
                j--;
            }
        }
        return true;
    }
    static int kmp(const char *text, const char *pattern)
    {
        int i;
        int j = -1;
        const int n = strlen(text);
        const int m = strlen(pattern);
        if (n == 0 && m == 0) return 0; /* "","" */
        if (m == 0) return 0; /* "a","" */
        int *next = (int*)malloc(sizeof(int) * m);
        compute_prefix(pattern, next);
        for (i = 0; i < n; i++) {
            while (j > -1 && pattern[j + 1] != text[i]) j = next[j];
            if (text[i] == pattern[j + 1]) j++;
            if (j == m - 1) {
                free(next);
                return i-j;
            }
        }
        free(next);
        return -1;
    }
    static void compute_prefix(const char *pattern, int next[])
    {
        int i;
        int j = -1;
        const int m = strlen(pattern);
        next[0] = j;
        for (i = 1; i < m; i++) {
            while (j > -1 && pattern[j + 1] != pattern[i]) j = next[j];
            if (pattern[i] == pattern[j + 1]) j++;
            next[i] = j;
        }
    }
    char *strStr(char *haystack, char *needle)
    {
        int pos = kmp(haystack, needle);
        if (pos == -1) return NULL;
        else return (char*)haystack + pos;
    }

    static void computePrefix(const char *pattern, int next[])
    {
        int i = 0, j = -1;
        const int m = strlen(pattern);
        next[0] = 0;
        for (i = 1; i < m; i++) {
            while (j > -1 && pattern[j + 1] != pattern[i]) j = next[j];
            if (pattern[i] == pattern[j + 1]) j++;
            next[i] = j;
        }
    }
    void test_kmp(const char *pattern)
    {
        int m = strlen(pattern);
        int *next = (int*)malloc(sizeof(int) * m);
        compute_prefix(pattern, next);
        for (int i = 0; i < m; i++) {
            cout << next[i];
        }
    }

    int atoi(const char *str)
    {
        int ret = 0, i = 0, len = strlen(str), flag = 1, num = 0;
        long long tmp = 0;
        for (i = 0; i < len && str[i] == ' '; i++) ;
        if (i == len) return 0;
        if (str[i] == '-') flag = -1;
        if (str[i] == '-' || str[i] == '+') i++;
        for ( ; i < len && (str[i] >= '0' && str[i] <= '9'); i++) {
            num = str[i] - '0';
            tmp = tmp * 10 + num;
        }
        if (tmp >= 2147483647 && flag == 1)
            ret = 2147483647;
        else if (tmp > 2147483648 && flag == -1)
            ret = 2147483648;
        else
            ret = tmp;
        ret *= flag;
        return ret;
    }

    string addBinary(string a, string b)
    {
        int n = max(a.size(), b.size()),
            m = min(a.size(), b.size()),
            x, y, tmp = 0, i = 0;
        string ret;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        for (i = 0; i < n; i++) {
            if (i < m) {
                tmp = tmp + a[i] - '0' + b[i] - '0';
            } else {
                if (i >= a.size()) {
                    tmp = tmp + b[i] - '0';
                } else {
                    tmp = tmp + a[i] - '0';
                }
            }
            if (tmp == 2) {
                ret.insert(ret.end(), '0');
                tmp = 1;
            } else if (tmp == 3) {
                ret.insert(ret.end(), '1');
                tmp = 1;
            } else {
                ret.insert(ret.end(), tmp + '0');
                tmp = 0;
            }
        }
        if (tmp) {
            ret.insert(ret.end(), '1');
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    string longestPalindrome(string s)
    {
        string tmp, ret;
        vector<int> len;
        int i = 0, j = 0, k = 0, sum = 1, index = 0, right_border = 0;
        for (i = 0; i < s.size(); i++) {
            tmp.insert(tmp.end(), '#');
            tmp.insert(tmp.end(), s[i]);
        }
        tmp.insert(tmp.end(), '#');
        //cout << tmp << endl;
        len.push_back(1);
        for (i = 1; i < tmp.size(); i++) {
            right_border = index + len[index] - 1;
            if (right_border > i) {
                sum = min(len[2 * index - i], right_border - i);
            } else {
                sum = 1;
            }
            //cout << i << ":" << sum << endl;
            for (j = i - sum, k = i + sum; j > -1 && k < tmp.size(); j--, k++) {
                //cout << j << k << endl;
                if (tmp[k] == tmp[j]) sum++;
                else break;

            }
            len.push_back(sum);
            if (len[index] <= sum) {
                index = i;
            }
            //cout << index << len[index] << endl;
        }
        sum = len[index];
        //cout << len[index] << endl;
        for (i = index - sum + 1; i <= index + sum - 1; i++) {
            if (tmp[i] != '#') ret.insert(ret.end(), tmp[i]);
        }
        return ret;
    }
    bool isMatch(const char *s, const char *p)
    {
        if (*p == '\0') return *s == '\0';
        // next char is not '*', then must match current character
        if (*(p + 1) != '*') {
            if (*p == *s || (*p == '.' && *s != '\0'))
                return isMatch(s + 1, p + 1);
            else
                return false;
        } else { // next char is '*'
            while (*p == *s || (*p == '.' && *s != '\0')) {
                if (isMatch(s, p + 2)) {
                    return true;
                }
                s++;
            }
            return isMatch(s, p + 2);
        }
    }
    string longestCommonPrefix(vector<string> &strs)
    {
        string ret;
        char tmp;
        int i = 0, j = 0;
        while (strs.size() > 0 && i < strs[0].size()) {
            tmp = strs[0][i];
            for (j = 1; j < strs.size(); j++) {
                if (tmp != strs[j][i]) break;
            }
            if (j == strs.size()) {
                ret.insert(ret.end(), tmp);
            } else {
                break;
            }
            i++;
        }
        return ret;
    }
    string intToRoman(int num)
    {
        const int radix[] = {1000, 900, 500, 400, 100, 90,
                             50, 40, 10, 9, 5, 4, 1
                            };
        const string symbol[] = {"M", "CM", "D", "CD", "C", "XC",
                                 "L", "XL", "X", "IX", "V", "IV", "I"
                                };
        string ret("");
        int a, b = num, div = 1000, i = 0, j = 0, tmp = 0;
        for ( ; div; div /= 10) {
            if (a = b / div) {
                a *=div;
                for (i = 0; i < 13; i++) {
                    if (radix[i] <= a) {
                        tmp = a - radix[i];
                        tmp /= div;
                        ret += symbol[i];
                        while (tmp--) {
                            switch(div) {
                            case 1:
                                ret += "I";
                                break;
                            case 10:
                                ret += "X";
                                break;
                            case 100:
                                ret += "C";
                                break;
                            case 1000:
                                ret += "M";
                                break;
                            }
                        }
                        break;
                    }
                }
                b -= a;
            }
        }
        return ret;
    }
    int romanToInt(string s)
    {
        const int radix[] = {1000, 900, 500, 400, 100, 90,
                             50, 40, 10, 9, 5, 4, 1
                            };
        const int add[] = {1000, 100, 100, 100, 100, 10,
                           10, 10, 10, 1, 1, 1, 1
                          };
        const string symbol[] = {"M", "CM", "D", "CD", "C", "XC",
                                 "L", "XL", "X", "IX", "V", "IV", "I"
                                };
        const string pend[] = {"M", "C", "C", "C", "C", "X",
                               "X", "X", "X", "I", "I", "I", "I"
                              };
        int ret = 0, i = 0, j = 0, k = 0;
        string tmp(s);
        for (i = 0; i < 13; i++) {
            if (tmp.substr(j, symbol[i].size()) == symbol[i]) {
                ret += radix[i];
                j += symbol[i].size();
                while (tmp.substr(j, 1) == pend[i]) {

                    ret += add[i];
                    j++;
                }
            }
        }
        return ret;
    }
    string countAndSay(int n)
    {
        int i = 0, j = 0, num = 0, freq = 0;
        string init("1"), ret("");
        char tmp;
        for (i = 1; i < n; i++) {
            tmp = init[0];
            freq = 1;
            for (j = 1; j < init.size(); j++) {
                if (tmp == init[j]) freq++;
                else {
                    ret.insert(ret.end(), freq + '0');
                    ret.insert(ret.end(), tmp);
                    tmp = init[j];
                    freq = 1;
                }
            }
            ret.insert(ret.end(), freq + '0');
            ret.insert(ret.end(), tmp);
            init = ret;
            ret = "";
        }
        return init;
    }
    /*vector<string> anagrams(vector<string> &strs) {
        unordered_map<string, vector<string> > group;
        for (const auto &s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            group[key].push_back(s);
        }
        vector<string> result;
        for (auto it = group.cbegin(); it != group.cend(); it++) {
            if (it->second.size() > 1)
                result.insert(result.end(), it->second.begin(), it->second.end());
        }
        return result;
    }*/
    void getNext(string &path, int *start, int *end)
    {
        for ( ; *start < path.size(); (*start)++) {
            if (path[*start] != '/') break;
        }
        for ( ; *end < path.size(); (*end)++) {
            if (path[*end] == '/') break;
        }
    }
    string simplifyPath(string path)
    {
        vector<string> strs;
        string ret("");
        int sindex = 0, eindex = 1;
        getNext(path, &sindex, &eindex);
        eindex = sindex;
        for (getNext(path, &sindex, &eindex) ; sindex < eindex; getNext(path, &sindex, &eindex)) {
            if (path.substr(sindex, eindex - sindex) == string(".")) {

            } else if (path.substr(sindex, eindex - sindex) == string("..")) {
                if (strs.size() > 0)
                    strs.erase(strs.end() - 1);
            } else
                strs.push_back(path.substr(sindex, eindex - sindex));
            sindex = eindex;
            getNext(path, &sindex, &eindex);
            eindex = sindex;
        }
        for (int i = 0; i < strs.size(); i++) {
            ret += "/";
            ret += strs[i];
        }
        if (ret.size() == 0) ret += "/";
        return ret;
    }
    int lengthOfLastWord(const char *s)
    {
        int size = strlen(s), i = 0, j = 1;
        for ( ; j < size; j++) {
            if (s[size - j] != ' ') break;
        }
        for ( ; i + j <= size; i++) {
            if (s[size - i - j] == ' ') break;
        }
        return i;
    }
    bool isValid(string s)
    {
        int i = 0;
        stack<char> stk;
        for (i = 0; i < s.size(); i++) {
            if (s[i] == ']' || s[i] == ')' || s[i] == '}') {
                if (!stk.empty())
                    switch(s[i]) {
                    case ']':
                        if (stk.top() == '[') {
                            stk.pop();
                        } else return false;
                        break;
                    case ')':
                        if (stk.top() == '(') {
                            stk.pop();
                        } else return false;
                        break;
                    case '}':
                        if (stk.top() == '{') {
                            stk.pop();
                        } else return false;
                        break;
                    }
                else return false;
            } else {
                stk.push(s[i]);
            }
        }
        if (stk.empty()) return true;
        else return false;
    }

    int longestValidParentheses(string s)
    {
        vector<int> count(s.size(), 0);
        int i = 0, match = 0, ret = 0;
        for (i = 1; i < s.size(); i++) {
            match = i - count[i - 1] - 1;
            if (match >= 0 && s[match] == '(' && s[i] == ')') {
                count[i] = count[i - 1] + 2;
                if (match > 0) count[i] += count[match - 1];
            }
            ret = max(ret, count[i]);
        }
        return ret;
    }
    int largestRectangleArea(vector<int> &height)
    {
        stack<int> s;
        height.push_back(0);
        int result = 0;
        for (int i = 0; i < height.size(); ) {
            if (s.empty() || height[i] > height[s.top()])
                s.push(i++);
            else {
                int tmp = s.top();
                s.pop();
                result = max(result,
                             height[tmp] * (s.empty() ? i : i - s.top() - 1));
            }
        }
        return result;
    }
};


#endif // STRINGCODE_H_INCLUDED
