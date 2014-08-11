#ifndef TREECODE_H_INCLUDED
#define TREECODE_H_INCLUDED

#include <queue>
#include <limits.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
};

class TreeCode
{
    void visitNode(TreeNode *node, vector<int> &vec)
    {
        if (node) {
            visitNode(node->left, vec);
            vec.push_back(node->val);
            visitNode(node->right, vec);
        }
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> ret;
        if (root) {
            visitNode(root->left, ret);
            ret.push_back(root->val);
            visitNode(root->right, ret);
        }
        return ret;
    }
    void visitNodePre(TreeNode *node, vector<int> &vec)
    {
        if (node) {
            vec.push_back(node->val);
            visitNodePre(node->left, vec);
            visitNodePre(node->right, vec);
        }
    }
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> ret;
        if (root) {
            ret.push_back(root->val);
            visitNodePre(root->left, ret);
            visitNodePre(root->right, ret);
        }
        return ret;
    }
    void visitNodePost(TreeNode *node, vector<int> &vec)
    {
        if (node) {
            visitNodePost(node->left, vec);
            visitNodePost(node->right, vec);
            vec.push_back(node->val);
        }
    }
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> ret;
        if (root) {
            visitNodePost(root->left, ret);
            visitNodePost(root->right, ret);
            ret.push_back(root->val);
        }
        return ret;
    }
    vector<vector<int> > levelOrder(TreeNode *root)
    {
        vector<vector<int> > ret;
        queue<TreeNode *> cur_level, son_level;
        if (root) cur_level.push(root);
        while (!cur_level.empty()) {
            vector<int> val;
            while (!cur_level.empty()) {
                TreeNode *node = cur_level.front();
                if (node->left) son_level.push(node->left);
                if (node->right) son_level.push(node->right);
                val.push_back(node->val);
                cur_level.pop();
            }
            ret.push_back(val);
            swap(cur_level, son_level);
        }
        return ret;
    }

    vector<vector<int> > levelOrderBottom(TreeNode *root)
    {
        vector<vector<int> > ret;
        queue<TreeNode *> cur_level, son_level;
        stack<vector<int> > tmp;
        if (root) cur_level.push(root);
        while (!cur_level.empty()) {
            vector<int> val;
            for ( ; !cur_level.empty(); ) {
                TreeNode *node = cur_level.front();
                if (node->left) son_level.push(node->left);
                if (node->right) son_level.push(node->right);
                val.push_back(node->val);
                cur_level.pop();
            }
            tmp.push(val);
            swap(cur_level, son_level);
        }
        while (!tmp.empty()) {
            ret.push_back(tmp.top());
            tmp.pop();
        }
        return ret;
    }
    vector<vector<int> > zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int> > ret;
        stack<TreeNode *> cur_level, son_level;
        bool flag = true;
        if (root) cur_level.push(root);
        for ( ; cur_level.size() > 0; ) {
            vector<int> val;
            while (!cur_level.empty()) {
                TreeNode *node = cur_level.top();
                if (flag) {
                    if (node->left) son_level.push(node->left);
                    if (node->right) son_level.push(node->right);
                } else {
                    if (node->right) son_level.push(node->right);
                    if (node->left) son_level.push(node->left);
                }
                val.push_back(node->val);
                cur_level.pop();
            }
            if (flag) flag = false;
            else flag = true;
            ret.push_back(val);
            swap(cur_level, son_level);
        }
        return ret;
    }
    void visitAndRecoverNode(TreeNode *node, TreeNode **node1, TreeNode **node2)
    {
        if (node->left->val > node->val
            || node->right->val < node->val) {
            if (!*node1) *node1 = node;
            else if (!*node2) *node2 = node;
        }
        if (node->left) {
            visitAndRecoverNode(node->left, node1, node2);
        }
        if (node->right) {
            visitAndRecoverNode(node->right, node1, node2);
        }
    }
    void recoverTree1(TreeNode *root)
    {
        TreeNode *node1 = 0, *node2 = 0;
        int tmp;
        if (root->left->val > root->val
            || root->right->val < root->val) node1 = root;
        if (root->left) {
            visitAndRecoverNode(root->left, &node1, &node2);
        }
        if (root->right) {
            visitAndRecoverNode(root->right, &node1, &node2);
        }
        if (node1 && node2) {
            tmp = node1->val;
            node1->val = node2->val;
            node2->val = tmp;
        }
    }
    /*    void detect(pair<TreeNode*, TreeNode*>& broken, TreeNode* prev,
                        TreeNode* current) {
            if (prev != nullptr && prev->val > current->val) {
                if (broken.first == nullptr) {
                    broken.first = prev;
                } //不能用 else，例如 {0,1}，会导致最后 swap 时 second 为 nullptr，
                //会 Runtime Error
                broken.second = current;
            }
        }
        void recoverTree(TreeNode* root) {
            pair<TreeNode*, TreeNode*> broken;
            TreeNode* prev = nullptr;
            TreeNode* cur = root;
            while (cur != nullptr) {
                if (cur->left == nullptr) {
                    detect(broken, prev, cur);
                    prev = cur;
                    cur = cur->right;
                } else {
                    auto node = cur->left;
                    while (node->right != nullptr && node->right != cur)
                        node = node->right;
                    if (node->right == nullptr) {
                        node->right = cur;
                        //prev = cur; 不能有这句！因为 cur 还没有被访问
                        cur = cur->left;
                    } else {
                        detect(broken, prev, cur);
                        node->right = nullptr;
                        prev = cur;
                        cur = cur->right;
                    }
                }
            }
            swap(broken.first->val, broken.second->val);
        }*/
    bool preCheckNode(TreeNode *p, TreeNode *q)
    {
        if (p && q)
            if (p->val != q->val) return false;
            else return preCheckNode(p->left, q->left)
                            && preCheckNode(p->right, q->right);
        else if (p == NULL && q == NULL) return true;
        else return false;
    }
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        return preCheckNode(p, q);
    }

    bool preCheckNodeVal(TreeNode *p, TreeNode *q)
    {
        if (p && q) {
            if (p->val == q->val) {
                return preCheckNodeVal(p->left, q->right)
                       && preCheckNodeVal(p->right, q->left);
            } else return false;
        } else if (p == NULL && q == NULL) return true;
        else return false;
    }

    bool isSymmetric(TreeNode *root)
    {
        if (root) return preCheckNodeVal(root->left, root->right);
        else return true;
    }

    int balancedHeight (TreeNode* root)
    {
        if (root == NULL) return 0; // 终止条件
        int left = balancedHeight (root->left);
        int right = balancedHeight (root->right);
        if (left < 0 || right < 0 || abs(left - right) > 1) return -1; // 剪枝
        return max(left, right) + 1; // 三方合并
    }

    bool isBalanced(TreeNode *root)
    {
        return balancedHeight (root) >= 0;
    }

    void flatten(TreeNode *root)
    {
        if (root == NULL) return;
        flatten(root->left);
        flatten(root->right);
        if (root->left == NULL) return;

        TreeNode *p = root->left;
        while (p->right) p = p->right;
        p->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }

    void connect(TreeLinkNode *root)
    {
        queue<TreeLinkNode *> cur_level, son_level;
        if (root) cur_level.push(root);
        while (!cur_level.empty()) {
            TreeLinkNode *preNode = NULL, *node = NULL;
            while (!cur_level.empty()) {
                node = cur_level.front();
                if (node->left) son_level.push(node->left);
                if (node->right) son_level.push(node->right);
                if (preNode) preNode->next = node;
                preNode = node;
                cur_level.pop();
            }
            node->next = NULL;
            swap(cur_level, son_level);
        }
    }
    TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder)
    {
        return buildTree(preorder.begin(), preorder.end(),
                         inorder.begin(), inorder.end());
    }
    TreeNode *buildTree1(vector<int>::iterator pre_first, vector<int>::iterator pre_last,
                         vector<int>::iterator in_first, vector<int>::iterator in_last)
    {
        if (pre_first == pre_last) return NULL;
        if (in_first == in_last) return NULL;
        TreeNode *root = new TreeNode(*pre_first);
        vector<int>::iterator inRootPos = find(in_first, in_last, *pre_first);
        int leftSize = distance(in_first, inRootPos);
        root->left = buildTree(pre_first + 1, pre_first + leftSize + 1,
                               in_first, in_first + leftSize);
        root->right = buildTree(pre_first + leftSize + 1, pre_last,
                                inRootPos + 1, in_last);
        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return buildTree(inorder.begin(), inorder.end(),
                         postorder.begin(), postorder.end());
    }
    TreeNode *buildTree(vector<int>::iterator in_first, vector<int>::iterator in_last,
                        vector<int>::iterator post_first, vector<int>::iterator post_last)
    {
        if (post_first == post_last) return NULL;
        if (in_first == in_last) return NULL;
        TreeNode *root = new TreeNode(*(post_last - 1));
        vector<int>::iterator inRootPos = find(in_first, in_last, *(post_last - 1));
        int leftSize = distance(in_first, inRootPos);
        root->left = buildTree(in_first, in_first + leftSize,
                               post_first, post_first + leftSize);
        root->right = buildTree(inRootPos + 1, in_last,
                                post_first + leftSize, post_last - 1);
        return root;
    }

    int numTrees(int n)
    {
        map<int, int> mp;
        mp[0] = mp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                mp[i] += mp[j] * mp[i - 1 - j];
            }
        }
        return mp[n];
    }
    vector<TreeNode *> generate(int start, int stop)
    {
        vector<TreeNode *> subTrees;
        if (start > stop) {
            subTrees.push_back(NULL);
            return subTrees;
        }
        for (int i = start; i <= stop; i++) {
            vector<TreeNode *> leftSubs = generate(start, i - 1);
            vector<TreeNode *> rightSubs = generate(i + 1, stop);
            for (int x = 0; x < leftSubs.size(); x++) {
                for (int y = 0; y < rightSubs.size(); y++) {
                    TreeNode *node = new TreeNode(i);
                    node->left = leftSubs[x];
                    node->right = rightSubs[y];
                    subTrees.push_back(node);
                }
            }
        }
        return subTrees;
    }

    vector<TreeNode *> generateTrees(int n)
    {
        if (n == 0) return generate(1, 0);
        return generate(1, n);
    }
    bool isValidBST(TreeNode *root, int low, int high)
    {
        if (!root) return true;
        return root->val > low && root->val < high
               && isValidBST(root->left, low, root->val)
               && isValidBST(root->right, root->val, high);
    }
    bool isValidBST(TreeNode *root)
    {
        return isValidBST(root, INT_MIN, INT_MAX);
    }

    TreeNode *sortedArrayToBST(vector<int>::iterator start,
                               vector<int>::iterator stop)
    {
        int i = distance(start, stop);
        if (i == 0) return NULL;
        vector<int>::iterator mid = start + i/2;
        TreeNode *node = new TreeNode(*mid);
        node->left = sortedArrayToBST(start, mid);
        node->right = sortedArrayToBST(mid + 1, stop);
        return node;
    }

    TreeNode *sortedArrayToBST(vector<int> &num)
    {
        return sortedArrayToBST(num.begin(), num.end());
    }


    TreeNode *sortedListToBST(ListNode *list, int start, int end)
    {
        if (start >= end) return nullptr;
        int mid = start + (end - start) / 2;
        TreeNode *leftChild = sortedListToBST(list, 0, mid);
        for (int i = 0; i < mid; i++) {
            list = list->next;
        }
        TreeNode *parent = new TreeNode(list->val);
        parent->left = leftChild;
        list = list->next;
        parent->right = sortedListToBST(list, 0, end - mid - 1);
        return parent;
    }

    TreeNode *sortedListToBST(ListNode *head)
    {
        int i = 0;
        ListNode *node  = head;
        while (node)  {
            i++;
            node = node->next;
        }
        return sortedListToBST(head, 0, i );
    }

    int minDepth(TreeNode *root) {
        if (!root) return 0;
        int left = 1, right = 1;
        if (root->left || root->right) {  //not a leaf
            left += minDepth(root->left);
            right += minDepth(root->right);
            if (left == 1) left = right;
            if (right == 1) right = left;
        }
        return min(left, right);
    }
    int maxDepth(TreeNode *root) {
        if (!root) return 0;
        int left = 1, right = 1;

        left += maxDepth(root->left);
        right += maxDepth(root->right);

        return max(left, right);
    }

    bool hasPathSum(TreeNode *root, int sum) {
        if (!root)  return false;
        else {
            sum -= root->val;
            if (root->left && root->right) return (hasPathSum(root->left, sum) || hasPathSum(root->right, sum));
            else if (root->left) return hasPathSum(root->left, sum) ;
            else if (root->right) return hasPathSum(root->right, sum);
            else if (sum == 0) return true;
        }
    }

    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int> > ret;
        vector<int> data;
        if (root) {
            sum -= root->val;
            data.push_back(root->val);
            if (!root->left && !root->right) {
                if (sum == 0) {
                    ret.push_back(data);
                }
            } else {
                pathSum(root->left, sum, ret, data);
                pathSum(root->right, sum, ret, data);
            }
        }
        return ret;
    }
    void pathSum(TreeNode *root, int sum, vector<vector<int> > &ret, vector<int> &data) {
        if (root) {
            sum -= root->val;
            data.push_back(root->val);
            if (!root->left && !root->right) {
                if (sum == 0) {
                    vector<int> newData = data;
                    ret.push_back(newData);
                }
            } else {
                pathSum(root->left, sum, ret, data);
                pathSum(root->right, sum, ret, data);
            }
            data.erase(data.end() - 1);
        }
    }
    int maxPathSum(TreeNode *root) {
        if (!root) return 0;
        int left = root->val, right = root->val;
        left += maxPathSum(root->left);
        right += maxPathSum(root->right);
        return max(left, right);
    }
    int max_sum;
    int maxPathSum(TreeNode *root) {
        max_sum = INT_MIN;
        dfs(root);
        return max_sum;
    }

    int dfs(const TreeNode *root) {
        if (root == nullptr) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        int sum = root->val;
        if (l > 0) sum += l;
        if (r > 0) sum += r;
        max_sum = max(max_sum, sum);
        return max(r, l) > 0 ? max(r, l) + root->val : root->val;
    }

    int sumNumbers(TreeNode *root) {
        vector<int> sums;
        dfs(root, 0, sums);
        int sum = 0;
        for (int i : sums) {
            sum += i;
        }
        return sum;
    }
    void dfs(TreeNode *root, int sum, vector<int> &sums) {
        if (!root) return;
        sum = sum * 10 + root->val;
        if (!root->left && !root->right) {
            sums.push_back(sum);
        } else {
            dfs(root->left, sum, sums);
            dfs(root->right, sum, sums);
        }
    }


    /*
        template<typename InputIterator>
        TreeNode* buildTree(InputIterator pre_first, InputIterator pre_last,
            InputIterator in_first, InputIterator in_last) {
            if (pre_first == pre_last) return nullptr;
            if (in_first == in_last) return nullptr;
            auto root = new TreeNode(*pre_first);
            auto inRootPos = find(in_first, in_last, *pre_first);
            auto leftSize = distance(in_first, inRootPos);
            root->left = buildTree(next(pre_first), next(pre_first,
                                leftSize + 1), in_first, next(in_first, leftSize));
            root->right = buildTree(next(pre_first, leftSize + 1), pre_last,
                                next(inRootPos), in_last);
            return root;
        }*/

};

#endif // TREECODE_H_INCLUDE
