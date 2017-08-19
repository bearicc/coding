/*
 * Climbing Stairs
 *
 * You are climbing a stair case. It takes n steps to reach to the top.
 * 
 * Each time you can climb any steps between 1 to m. In how many distinct ways can you climb to the top?
 * 
 * Note: Given n will be a positive integer.
*/

#include "common.h"

// If we could climb consecutive steps, then we could optimize the solution
//   from O(n*m) to O(n)
class Solution {
public:
    string climbStairs(int n, int m) {
        if (n == 0 || m == 0) {
            return "0";
        }
        vector<string> DP(n + 1, "0");
        DP[0] = "1";
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m && j <= i; ++j) {
                DP[i] = addStrings(DP[i], DP[i - j]);
            }
            // cout << i << ' ' << DP[i] << endl;
        }
        return DP[n];
    }

    int quickclimbStairs(int n, int m) {
        vector<int> DP(n+1, 0);
        DP[0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (i <= m) {
                DP[i] = int(pow(2, i-1) + 0.5);
            } else {
                DP[i] = 2*DP[i-1] - DP[i-m-1];
            }
            // cout << i << ' ' << DP[i] << endl;
        }
        return DP[n];
    }

    int climbStairs(int n) {
        // f(n) = f(n-2) + f(n-1)
        if (n == 1) {
            return 1;
        } else if (n == 2) {
            return 2;
        }
        int a = 1, b = 2, temp;
        for (int i = 3; i <= n; ++i) {
            temp = b;
            b = a+b;
            a = temp;
        }
        return b;
    }
};

int main() {
    Solution ans;
    int n = 10, m = 2;
    cout << ans.climbStairs(n, m) << endl;
    cout << ans.quickclimbStairs(n, m) << endl;
    return 0;
}
