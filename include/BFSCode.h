#ifndef BFSCODE_H_INCLUDED
#define BFSCODE_H_INCLUDED

void solve(vector<vector<char>> &board) {
    int m = board.size();
    if (m == 0) return;
    int n = board[0].size();
    if (n == 0) return;

    for (int i = 1; i < m - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            if (board[i][j] == 'O') {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    board[i][j] = 'X';
                } else {
                    if (board[i - 1][j] == 'X')
                }
            }
        }
    }
}

#endif // BFSCODE_H_INCLUDED
