#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int backPackIV(vector<int>& nums, int target) {
        vector<int> DP(target+1, 0); 
        DP[0] = 1;
        sort(nums.begin(), nums.end());
        for (const int& num: nums) {
            for (int i = 1; i <= target; ++i) {
                if (i >= num) {
                    DP[i] += DP[i - num];
                }
            }
        } 
        return DP[target];
    }
    int backPackIV2(vector<int>& nums, int target) {
        vector<int> DP(target+1, 0); 
        DP[0] = 1;
        sort(nums.begin(), nums.end());
        for (const int& num: nums) {
            for (int i = target; i >= num; --i) {
                DP[i] += DP[i - num];
            }
        } 
        return DP[target];
    }
};

int main() {
    Solution test;
    vector<int> nums{2, 3, 6, 7};
    int target = 7;
    cout << "target = " << target << endl;
    for (const int& num: nums) {
        cout << num << ' ';
    }
    cout << endl;
    cout << test.backPackIV(nums, target) << endl;
    cout << test.backPackIV2(nums, target) << endl;
    return 0;
}
