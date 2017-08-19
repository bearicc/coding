#include "../common.h"

using namespace std;

void dfs(vector<int>& nums, int begin, int cur, vector<int>& result) {
    for (int i = begin; i < nums.size(); ++i) {
        result.push_back(cur * nums[i]);
        dfs(nums, i+1, cur * nums[i], result);
    }
}

void combination(vector<int>& nums, vector<int>& result) {
    for (const int& num: nums) {
        const int N = result.size();
        result.push_back(num);
        for (int i = 0; i < N; ++i) {
            result.push_back(result[i] * num);
        }
    }
}

void bfs(vector<int>& nums, vector<int>& result) {
    typedef pair<int, int> P;
    priority_queue<P, vector<P>, greater<P>> Q;
    for (int i = 0; i < nums.size(); ++i) Q.push({nums[i], i});
    while (!Q.empty()) {
        auto cur = Q.top();
        Q.pop();
        result.push_back(cur.first);
        for (int j = cur.second + 1; j < nums.size(); ++j) {
            Q.push({cur.first * nums[j], j});
        }
    }
}

int main() {
    vector<int> nums{2, 3, 5, 7};
    vector<int> result;
    dfs(nums, 0, 1, result);
    cout << result << endl;
    result.clear();
    combination(nums, result);
    cout << result << endl;
    result.clear();
    bfs(nums, result);
    cout << result << endl;
    return 0;
}
