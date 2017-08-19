#ifndef _COMMON_H_
#define _COMMON_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <ctime>
#include <cstring>

#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <utility>
#include <tuple>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono; 

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val):val(val), left(nullptr), right(nullptr) {}
};

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    int i;
    for (i = 0; i + 1 < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    if (i < v.size()) {
        cout << v[i];
    }
    return os;
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>&& v) {
    return operator<<(os, v);
}

vector<int> random_array(int n, int begin, int end);
string addStrings(string& num1, string& num2);
string addStrings(string&& num1, string&& num2);
string tree_serialize(TreeNode* root);
TreeNode* tree_deserialize(string s);

#endif
