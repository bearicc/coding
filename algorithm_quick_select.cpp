// Similar to `nth_element`.
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// ------------------------------------------------------------
int quickselect(vector<int>& nums, int begin, int end, int k) {
    int i = begin, j = begin;
    while (i < end) {
        if (nums[i] < nums[end]) {
            swap(nums[i], nums[j++]);
        }
        ++i;
    }
    swap(nums[j], nums[end]);
    if (j == k) {
        return nums[j];
    } else if (k < j) {
        return quickselect(nums, begin, j - 1, k);
    } else {
        return quickselect(nums, j + 1, end, k);
    }
}

int quickselect(vector<int>& nums, int k) {
    return quickselect(nums, 0, (int)nums.size()-1, k);
}
// ------------------------------------------------------------

void shuffle(vector<int>& nums) {
    int N = nums.size();
    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    int i = 0, j = 0;
    for (i = N; i >= 1; --i) {
        swap(nums[gen() % i], nums[i-1]);
    }
}

ostream& operator<<(ostream& os, const vector<int>& nums) {
    int i = 0;
    for (i = 0; i + 1 < nums.size(); ++i) {
        cout << nums[i] << ' ';
    }
    if (i < nums.size()) {
        cout << nums[i];
    }
    return os;
}

int main() {
    vector<int> nums;
    for (int i = 1; i <= 100; ++i) {
        nums.push_back(i);
    }
    shuffle(nums);
    cout << nums << endl;

    int k = 30;
    cout << quickselect(nums, k - 1) << endl;
    // auto it = nums.begin() + k - 1;
    // nth_element(nums.begin(), it, nums.end());
    // cout << *it << endl;

    cout << nums << endl;
    return 0;
}
