class Solution {
public:
    int backPackV(vector<int>& nums, int target) {
        vector<int> DP(target+1, 0);
        DP[0] = 1;
        for (const int& num: nums) {
            for (int i = target; i >= num; --i) {
                DP[i] += DP[i - num];
            }
        }
        return DP[target];
    }
};
