#ifndef STRINGCODE_H_INCLUDED
#define STRINGCODE_H_INCLUDED
#include <string>
#include <iostream>
using namespace std;
class StringCode
{
public:
    char change(char c) {
        if (c >= 'a' && c <= 'z') {
            return c;
        }
        if (c >= 'A' && c <= 'Z') {
            return c - ('A' - 'a');
        }
        if (c >= '0' && c <= '9') return c;
        return 0;
    }
    bool isPalindrome(string s) {
        if (!s.size()) return true;
        int i = 0, j = s.size() - 1;
        for ( ; i < j; ) {
            if (change(s[i]) && change(s[j])) {
                if (change(s[i]) == change(s[j])) {
                    i++; j--;
                } else {
                    return false;
                }
            }
            if (!change(s[i]) && change(s[j])) i++;
            if (change(s[i]) && !change(s[j])) j--;
            if (!change(s[i]) && !change(s[j])) {
                i++; j--;
            }
        }
        return true;
    }
    static int kmp(const char *text, const char *pattern) {
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
    static void compute_prefix(const char *pattern, int next[]) {
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
    char *strStr(char *haystack, char *needle) {
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
    void test_kmp(const char *pattern) {
        int m = strlen(pattern);
        int *next = (int*)malloc(sizeof(int) * m);
        compute_prefix(pattern, next);
        for (int i = 0; i < m; i++) {
            cout << next[i];
        }
    }

    int atoi(const char *str) {
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

    string addBinary(string a, string b) {
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

    string longestPalindrome(string s) {
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
    bool isMatch(const char *s, const char *p) {
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
};


#endif // STRINGCODE_H_INCLUDED
