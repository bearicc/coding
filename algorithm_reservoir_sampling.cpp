#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "common.h"

using namespace std;

// ------------------------------------------------------------
int reservoir_sampling(vector<int>& nums) {
    int i = 1, j = 1, n = 0;
    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    for (const int& num: nums) {
        j = 1 + gen() % i++;
        if (j == 1) {
            n = num;
        }
    }
    return n;
}
// ------------------------------------------------------------

int main() {
    vector<int> nums;
    for (int i = 1; i <= 10; ++i) {
        nums.push_back(i);
    }
    cout << nums << endl;
    for (int i = 0; i < 100; ++i) {
        cout << reservoir_sampling(nums) << ' ';
    }
    cout << endl;
    return 0;
}
