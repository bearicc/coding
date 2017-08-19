/*
 
Combination problems

- loop over numbers                                                                 
- loop over target (pack size)                                                      
There are two loops here.                                                           
- If order doesn't matter and each number can be used any times,                    
  we need to `loop target` first and can `loop numbers` either bottom-up or         
  top-down;                                                                         
- If order matters, we need to `loop` nubmers first;                                
- If each number can only be used once, we need to `loop target` top-down. 

8/11/17

 */
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int combination_order_no_unique_no(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= target; ++i) {
        for (const int& num: nums) {
            if (i >= num) dp[i] += dp[i - num];
        }
    }
    return dp[target];
}

int combination_order_yes_unique_no(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    sort(nums.begin(), nums.end());
    for (const int& num: nums) {
        for (int i = 1; i <= target; ++i) {
            if (i >= num) dp[i] += dp[i - num];
        }
    }
    return dp[target];
}

int combination_order_yes_unique_yes(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (const int& num: nums) {
        for (int i = target; i >= num; --i) {
            dp[i] += dp[i - num];
        }
    }
    return dp[target];
}

int combination_order_no_unique_yes(vector<int>& nums, int target) {
    cout << "No solution yet." << endl;
    return -1;
}

int main() {
    vector<int> nums{1, 2, 3};
    int target = 4;
    cout << combination_order_no_unique_no(nums, target) << endl;
    cout << combination_order_yes_unique_no(nums, target) << endl;
    cout << combination_order_yes_unique_yes(nums, target) << endl;
    cout << combination_order_no_unique_yes(nums, target) << endl;
    return 0;
}
