#include <iostream>
#include <vector>
using namespace std;

int moore_voting_algorithm(vector<int> nums) {
    int n, count = 0;
    for (const int& num: nums) {
        if (count == 0) {
            n = num;
            count = 1;
        } else if (n == num) {
            ++count;
        } else {
            --count;
        }
    }
    return n;
}

int main() {
    vector<int> nums{1, 1, 2, 2, 2, 3};
    for (const int& num: nums) {
        cout << num << ' ';
    }
    cout << endl;
    cout << moore_voting_algorithm(nums) << endl;
    return 0;
}
