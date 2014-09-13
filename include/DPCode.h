#ifndef DPCODE_H_INCLUDED
#define DPCODE_H_INCLUDED

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

int maxProfit(vector<int> &prices) {
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

bool wordBreak(string s, unordered_set<string> &dict) {
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

vector<string> wordBreak(string s, unordered_set<string> &dict) {
    v
}

int maxProfit(vector<int> &prices) {

}

#endif // DPCODE_H_INCLUDED
