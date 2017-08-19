#include "common.h"

void helper(TreeNode* parent, TreeNode* cur, unordered_set<int>& nodes, vector<TreeNode*>& result) {
    if (!cur) return;
    if (nodes.find(cur->val) != nodes.end()) {
        if (parent) {
            if (parent->left == cur) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        nodes.erase(cur->val);
        if (cur->left && nodes.find(cur->left->val) == nodes.end()) {
            result.push_back(cur->left);
        }
        if (cur->right && nodes.find(cur->right->val) == nodes.end()) {
            result.push_back(cur->right);
        }
        helper(nullptr, cur->left, nodes, result);
        helper(nullptr, cur->right, nodes, result);
    } else {
        helper(cur, cur->left, nodes, result);
        helper(cur, cur->right, nodes, result);
    }
}

vector<TreeNode*> erase(TreeNode* root, vector<int> nodes) {
    if (nodes.empty()) return {root};
    unordered_set<int> dict(nodes.begin(), nodes.end());
    vector<TreeNode*> result;
    if (dict.find(root->val) == dict.end()) result.push_back(root);
    helper(nullptr, root, dict, result);
    return result;
}

int main() {
    TreeNode* root = tree_deserialize("1(2(4)(5))(3(6)(7))");
    vector<TreeNode*> r = erase(root, {4, 3});
    for (auto cur: r) {
        cout << cur->val << ' ';
    }
    cout << endl;
    return 0;
}
