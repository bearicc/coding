#include "common.h"

void morris_inorder_traversal(TreeNode* root) {
    TreeNode* cur = root, *prev = nullptr;
    while (cur) {
        if (!cur->left) {
            // No left, so process current
            cout << cur->val << ' ';
            cur = cur->right;
        } else {
            prev = cur->left;
            while (prev->right && prev->right != cur) {
                prev = prev->right;
            }
            if (prev->right == nullptr) {
                // Start to search left, so point pre node to current root
                prev->right = cur;
                cur = cur->left;
            } else {
                // Done with left, so restore it
                cout << cur->val << ' ';
                prev->right = NULL;
                cur = cur->right;
            }
        }
    }
    cout << endl;
}

void morris_preorder_traversal(TreeNode* root) {
    TreeNode* cur = root, *prev = nullptr;
    while (cur) {
        if (!cur->left) {
            // No left, so process current
            cout << cur->val << ' ';
            cur = cur->right;
        } else {
            prev = cur->left;
            while (prev->right && prev->right != cur) {
                prev = prev->right;
            }
            if (prev->right == nullptr) {
                // Start to search left, so point pre node to current root
                cout << cur->val << ' ';
                prev->right = cur;
                cur = cur->left;
            } else {
                // Done with left, so restore it
                prev->right = NULL;
                cur = cur->right;
            }
        }
    }
    cout << endl;
}

int main() {
    // string s = "1 2 4 # # 5 # # 3 6 # # 7 # #";
    string s = "1(2()(5))(3(6)(7))";
    TreeNode* root = tree_deserialize(s);
    cout << s << endl;
    morris_inorder_traversal(root);
    morris_preorder_traversal(root);
    return 0;
}
