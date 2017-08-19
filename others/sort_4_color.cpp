#include "common.h"

void sort4(vector<int>& nums) {
    // 01  2  3
    int i = 0, j = 0, k = (int)nums.size()-1;
    while (j < k) {
        if (nums[j] == 2) {
            ++j;
        } else if (nums[j] < 2) {
            swap(nums[i++], nums[j++]);
        } else {
            swap(nums[k--], nums[j]);
        }
    }
    // sort 01 [0, i)
    k = j, j = 0, i = 0;
    while (i < k) {
        if (nums[i] == 0) {
            swap(nums[j++], nums[i]);
        }
        ++i;
    }
}

int main() {
    vector<int> nums;
    for (int i = 0; i < 10; ++i) {
        nums.push_back(0);
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
    }
    int seed = time(0);
    default_random_engine gen(seed);
    shuffle(nums.begin(), nums.end(), gen);
    cout << nums << endl;
    sort4(nums);
    cout << nums << endl;
    return 0;
}
