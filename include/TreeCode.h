#ifndef TREECODE_H_INCLUDED
#define TREECODE_H_INCLUDED

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
};

#endif // TREECODE_H_INCLUDED
