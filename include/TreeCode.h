#ifndef TREECODE_H_INCLUDED
#define TREECODE_H_INCLUDED

#include <queue>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class TreeCode {
    void visitNode(TreeNode *node, vector<int> &vec) {
        if (node){
            visitNode(node->left, vec);
            vec.push_back(node->val);
            visitNode(node->right, vec);
        }
    }
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ret;
        if (root){
            visitNode(root->left, ret);
            ret.push_back(root->val);
            visitNode(root->right, ret);
        }
        return ret;
    }
    void visitNodePre(TreeNode *node, vector<int> &vec) {
        if (node){
            vec.push_back(node->val);
            visitNodePre(node->left, vec);
            visitNodePre(node->right, vec);
        }
    }
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> ret;
        if (root){
            ret.push_back(root->val);
            visitNodePre(root->left, ret);
            visitNodePre(root->right, ret);
        }
        return ret;
    }
    void visitNodePost(TreeNode *node, vector<int> &vec) {
        if (node){
            visitNodePost(node->left, vec);
            visitNodePost(node->right, vec);
            vec.push_back(node->val);
        }
    }
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ret;
        if (root){
            visitNodePost(root->left, ret);
            visitNodePost(root->right, ret);
            ret.push_back(root->val);
        }
        return ret;
    }
    vector<vector<int> > levelOrder(TreeNode *root) {
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

    vector<vector<int> > levelOrderBottom(TreeNode *root) {
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
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
    void visitAndRecoverNode(TreeNode *node, TreeNode **node1, TreeNode **node2) {
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
    void recoverTree1(TreeNode *root) {
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
    void detect(pair<TreeNode*, TreeNode*>& broken, TreeNode* prev,
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
    }
    bool preCheckNode(TreeNode *p, TreeNode *q) {
        if (p && q)
            if (p->val != q->val) return false;
            else return preCheckNode(p->left, q->left)
                        && preCheckNode(p->right, q->right);
        else if (p == NULL && q == NULL) return true;
        else return false;
    }
    bool isSameTree(TreeNode *p, TreeNode *q) {
        return preCheckNode(p, q);
    }

    bool preCheckNodeVal(TreeNode *p, TreeNode *q) {
        if (p && q) {
            if (p->val == q->val) {
                return preCheckNodeVal(p->left, q->right)
                        && preCheckNodeVal(p->right, q->left);
            } else return false;
        } else if (p == NULL && q == NULL) return true;
        else return false;
    }

    bool isSymmetric(TreeNode *root) {
        if (root) return preCheckNodeVal(root->left, root->right);
        else return true;
    }

    bool checkNode(TreeNode *node, int cur, int *deep) {

        if (node->left || node->right) {
            *deep += 1;
            if (node->left)
        } else {
            if (cur < deep - 1) return false;
            else return true;
        }
    }

    bool isBalanced(TreeNode *root) {
        int deep = 0;
        if (root) {
            return checkNode(root, 0, &deep)
        } else return true;
    }
};

#endif // TREECODE_H_INCLUDED
