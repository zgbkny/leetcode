#ifndef ARRAYCODE_H_INCLUDED
#define ARRAYCODE_H_INCLUDED
#include <string>
#include <algorithm>
#include <stack>
using namespace std;
class ArrasyCode
{
public:
    void findInLow(vector<int> &data, int n, int product, int k)
    {
        int tmp = k, quotient = 0, i = 0;
        for ( ; n > 0; n--)
            if (k >= product) break;
            else product /= n;

        if (product != 1)
            tmp = k - product;
        else tmp = 1;
        if (tmp > 2) {
            quotient = tmp / product - 1;
            sort(data.end() - n, data.end());
            if (tmp % product) quotient++;
            swap(data[data.size() - n - 1], data[data.size() - n + quotient]);
            sort(data.end() - n, data.end());
            if (tmp % product)
                findInLow(data, n, product, tmp % product);
            else
                reverse(data.end() - n, data.end());

        } else if (tmp > 0) {
            if (n > 1 && data.size() >= n + 1)
                swap(data[data.size() - n - 1], data[data.size() - n]);

            if (tmp == 2)
                reverse(data.end() - 2, data.end());
            else if (data.size() > 1)
                sort(data.end() - 2, data.end());
        } else
            reverse(data.end() - n, data.end());

    }
    string getPermutation(int n, int k)
    {
        vector<int> data;
        string ret(n, 0);
        int i = 0, product = 1, tmp = 0;
        // init
        for ( ; i < n; i++) {
            data.push_back(i + 1);
            product *= (i + 1);
        }
        // calculate
        findInLow(data, n, product, k);

        // to string
        for (int i = 0; i < n; i++)
            ret[i] = data[i] + 48;
        return ret;
    }

    int trap(int A[], int n)
    {
        int *max_left = new int[n]();
        int *max_right = new int[n]();
        for (int i = 1; i < n; i++) {
            max_left[i] = max(max_left[i - 1], A[i - 1]);
            max_right[n - 1 - i] = max(max_right[n - i], A[n - i]);
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int height = min(max_left[i], max_right[i]);
            if (height > A[i]) {
                sum += height - A[i];
            }
        }
        delete[] max_left;
        delete[] max_right;
        return sum;
    }
    int trap1(int A[], int n)
    {
        stack<pair<int, int> > s;
        int water = 0;
        for (int i = 0; i < n; ++i) {
            int height = 0;
            while (!s.empty()) { // 将栈里比当前元素矮或等高的元素全部处理掉
                int bar = s.top().first;
                int pos = s.top().second;
                // bar, height, a[i] 三者夹成的凹陷
                water += (min(bar, A[i]) - height) * (i - pos - 1);
                height = bar;
                if (A[i] < bar) // 碰到了比当前元素高的，跳出循环
                    break;
                else
                    s.pop(); // 弹出栈顶，因为该元素处理完了，不再需要了
            }
            s.push(make_pair(A[i], i));
        }
        return water;
    }

    void rotate(vector<vector<int> > &matrix)
    {
        int n = matrix.size();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n - i; j++)
                swap(matrix[i][j], matrix[n - j - 1][n - i - 1]);

        for (int i = 0; i < n / 2; i++)
            for (int j = 0; j < n; j++)
                swap(matrix[i][j], matrix[n - i - 1][j]);
    }

    vector<int> plusOne(vector<int> &digits)
    {
        vector<int> ret;
        int idx = 0;
        digits[digits.size() - 1]++;
        for (int i = digits.size() - 1; i >0; i--) {
            if (digits[i] > 9) {
                digits[i] -= 10;
                digits[i - 1]++;
            }
        }
        if (digits[0] > 9) {
            digits[0] -= 10;
            ret.resize(digits.size() + 1);
            idx++;
            ret[0] = 1;
        } else {
            ret.resize(digits.size());
        }
        memcpy(&ret[idx], &digits[0], sizeof(int) * digits.size());
        return ret;
    }
    void step(int n, int *count)
    {

        if (n - 2 >= 0) {
            (*count)++;
            step(n - 2, count);
        }
        if (n - 1 >= 0) {
            (*count)++;
            step(n - 1, count);
        }
    }
    int climbStairs(int n)
    {
        //const double s = sqrt(5);
        //return floor((pow((1+s)/2, n+1) + pow((1-s)/2, n+1))/s + 0.5);
        int prev = 0;
        int cur = 1;
        for(int i = 1; i <= n ; ++i) {
            int tmp = cur;
            cur += prev;
            prev = tmp;
        }
        return cur;
    }
    vector<int> grayCode(int n)
    {
        vector<int> ret;
        ret.resize(2 * n + 1);
        unsigned int v = 1 << n;
        v--;
        cout << v;

        ret[n] = (int)v;
        for (int i = n; i > 0; i--) {
            v = v >> 1;
            ret[n - 1] = (int)v;
        }
        v = 1 << n - 1;
        for (int i = 0; i < n; i++) {
            v = v << 1;
            ret[n + i + 1] = (int)v;
        }
        return ret;
    }

    void setZeroes(vector<vector<int> > &matrix)
    {
        vector<int> row, column;
        int size = 0;
        for (int i = 0; i < matrix.size(); i++) {
            vector<int> tmp = matrix[i];
            size = tmp.size();
            for (int j = 0; j < tmp.size(); j++) {
                if (tmp[j] == 0) {
                    row.push_back(i);
                    column.push_back(j);
                }
            }
        }
        for (int i = 0; i < row.size(); i++) {
            for (int j = 0; j < size; j++) {
                matrix[row[i]][j] = 0;
                cout << j << matrix[row[i]][j] << endl;
            }
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < matrix.size(); j++) {
                matrix[j][column[i]] = 0;
            }
        }
    }

    int largestRectangleArea(vector<int> &height)
    {
        return 1;
    }

};


#endif // ARRAYCODE_H_INCLUDED
