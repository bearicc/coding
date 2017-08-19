#include "common.h"

vector<int> random_array(int n, int begin, int end) {
    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    uniform_int_distribution<int> dist(begin, end);
    vector<int> ret;
    for (int i = 0; i < n; ++i) {
        ret.push_back(dist(gen));
    }
    return ret;
}


string addStrings(string& num1, string& num2) {
    const int N1 = num1.size(), N2 = num2.size();
    int i = N1 - 1, j = N2 - 1, k = max(N1, N2), n = 0;
    string ret(k + 1, 0);
    while (i >= 0 || j >= 0 || n) {
        if (i >= 0) {
            n += num1[i--] - '0';
        }
        if (j >= 0) {
            n += num2[j--] - '0';
        }
        ret[k--] = n % 10 + '0';
        n /= 10;
    }
    if (ret[0] == 0) {
        ret.erase(0, 1);
    }
    return ret;
}

string addStrings(string&& num1, string&& num2) {
    return addStrings(num1, num2);
}

/*
string tree_serialize(TreeNode* root) {
    if (!root) {
        return "#";
    } else {
        return to_string(root->val) + " " + tree_serialize(root->left) + " " + tree_serialize(root->right);
    }
}

TreeNode* tree_deserialize(const string& s, istringstream& is) {
    string t;
    is >> t;
    if (t == "#") {
        return NULL;
    }
    TreeNode* root = new TreeNode(stoi(t));
    root->left = tree_deserialize(s, is);
    root->right = tree_deserialize(s, is);
    return root;
}

TreeNode* tree_deserialize(string s) {
    istringstream is(s);
    return tree_deserialize(s, is);
}
*/

string tree_serialize(TreeNode* root) {
    if (!root) {
        return "";
    }
    string s = to_string(root->val);
    if (root->right) {
        s += "(" + tree_serialize(root->left) + ")(" + tree_serialize(root->right) + ")";
    } else if (root->left) {
        s += "(" + tree_serialize(root->left) + ")";
    }
    return s;
}

TreeNode* tree_deserialize(const string& s, int& i) {
    const int N = s.size();
    if (i >= N || s[i] == ')') {
        return NULL;
    }
    int val = 0, sign = 1;
    if (s[i] == '-') {
        sign = -1;
        ++i;
    }
    while (i < N && isdigit(s[i])) {
        val = 10 * val + s[i++] - '0';
    }
    TreeNode* root = new TreeNode(val * sign);
    if (i >= N || s[i] == ')') {
        return root;
    }
    ++i; // skip '('
    root->left = tree_deserialize(s, i);
    ++i; // skip ')'
    if (i < N && s[i] == '(') {
        ++i; // skip '('
        root->right = tree_deserialize(s, i);
        ++i; // skip ')'
    }
    return root;
}

TreeNode* tree_deserialize(string s) {
    int i = 0;
    return tree_deserialize(s, i);
}
