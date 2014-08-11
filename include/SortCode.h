#ifndef SORTCODE_H_INCLUDED
#define SORTCODE_H_INCLUDED

void merge(int A[], int m, int B[], int n) {
        int i = m - 1, j = n - 1;
        while (i > -1 && j > -1) {
            if (A[i] > B[j]) {
                A[i + j + 1] = A[i];
                i--;
            } else {
                A[i + j + 1] = B[j];
                j--;
            }
        }
        while (j > -1) {
            A[j] = B[j];
            j--;
        }
}

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {

    ListNode *node = new ListNode(0);
    ListNode *head = node;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            node->next = l1;
            node = node->next;
            l1 = l1->next;
        } else {
            node->next = l2;
            node = node->next;
            l2 = l2->next;
        }
    }
    if (l1) {
        node->next = l1;
    }
    if (l2) {
        node->next = l2;
    }
    return head->next;
}

ListNode *mergeKLists(vector<ListNode *> &lists) {
    ListNode head(0);
    ListNode *node = &head;
    for (int i = 0; i < lists.size(); ) {
        if (lists[i] == NULL) {
            lists.erase(lists.begin() + i);
        } else {
            i++;
        }
    }
    while (lists.size() > 0) {
        mergeKLists(node, lists);
        node = node->next;
    }
    return head.next;
}

void mergeKLists(ListNode *node, vector<ListNode *> &lists) {
    int min = INT_MAX, min_index = -1;
    for (int i =  0; i < lists.size(); i++) {
        if (lists[i]->val < min) {
            min = lists[i]->val;
            min_index = i;
        }
    }
    node->next = lists[min_index];
    lists[min_index] = lists[min_index]->next;
    if (lists[min_index] == NULL) {
        lists.erase(lists.begin() + min_index);
    }
}

int firstMissingPositive(int A[], int n) {
    for (int i = 0; i < n; i++) {
        int tmp = A[i], index = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < tmp) {
                tmp = A[j];
                index = j;
            }
        }
        A[index] = A[i];
        A[i] = tmp;
    }
    int k = 1;
    for (int i  = 0; i < n; i++) {
        if (A[i] > 0) {
            if (A[i] != k) break;
            if (i < n - 1) {
                if (A[i] != A[i+1]) k++;
            } else {
                k++;
            }
        }
    }
    return k;
}

void sortColors(int A[], int n) {
    int red = 0, white = 0, blue = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] == 0) red++;
        if (A[i] == 1) white++;
        if (A[i] == 2) blue++;
    }
    for (int i = 0; i < n; i++) {
        if (i < red) A[i] = 0;
        if (i < red + white &&  i >= red) A[i] = 1;
        if (i < red + white + blue && i >= red + white) A[i] = 2;
    }
}




#endif // SORTCODE_H_INCLUDED
