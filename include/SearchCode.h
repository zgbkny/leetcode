#ifndef SEARCHCODE_H_INCLUDED
#define SEARCHCODE_H_INCLUDED

vector<int> searchRange(int A[], int n, int target) {
    int start = 0, end = n - 1;
    int index = (start + end) / 2;
    for ( ; start <= end; ) {
        if (target < A[index]) {
            end = index - 1;
        } else if (target > A[index]){
            start = index + 1;
        } else {
            int tmp = index;
            for ( ; tmp > -1; tmp--) {
                if (A[tmp] != target) break;
            }
            start = tmp + 1;
            for ( tmp = index; tmp < n; tmp++) {
                if (A[tmp] != target) break;
            }
            end = tmp - 1;
            break;
        }
        index = (start + end) / 2;
    }
    if (start <= end) {
        return vector<int> { start, end };
    } else {
        return vector<int> { -1, -1 };
    }
}
int searchInsert(int A[], int n, int target) {
    int i = 0;
    for ( ; i < n; i++) {
        if (A[i] >= target) break;
    }
    return i;
}
bool searchMatrix(vector<vector<int> > &matrix, int target) {
    bool exsit = false;
    int tmp = INT_MIN;
    for (int i = 0; i < matrix.size(); i++) {
        vector<int> vec = matrix[i];
        for (int j = 0; j < vec.size(); j++) {
            if (j == 0 && vec[j] <= tmp) return false;
            if (vec[j] == target) exsit = true;
            if (j < vec.size() - 1 && vec[j] > vec[j + 1]) return false;
            if (j == vec.size() - 1) tmp = vec[j];
        }
    }
    return exsit;
}



#endif // SEARCHCODE_H_INCLUDED
