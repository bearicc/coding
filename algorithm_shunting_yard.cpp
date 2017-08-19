#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <cctype> // isdigit

using namespace std;

class Solution {
public:
    double calculate(string s) {
        queue<string> Q;
        stack<char> opers;
        int i = 0, j = 0;
        unordered_map<char, int> dict{
            {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'(', 2}, {')', -1}
        };
        // Convert to reverse polish notation, then eval.
        while (i < s.size()) {
            if (isdigit(s[i])) {
                j = i;
                while (i < s.size() && isdigit(s[i])) {
                    ++i;
                }
                Q.push(s.substr(j, i - j));
            } else if (s[i] == ' ') {
                ++i;
            } else {
                while (!opers.empty() && dict[s[i]] <= dict[opers.top()] && opers.top() != '(') {
                    Q.push(string(1, opers.top()));
                    opers.pop();
                }
                if (s[i] == ')') {
                    opers.pop();
                    ++i;
                } else {
                    opers.push(s[i++]);
                }
            }
        }
        while (!opers.empty()) {
            Q.push(string(1, opers.top()));
            opers.pop();
        }

        stack<double> nums;
        while (!Q.empty()) {
            string cur = Q.front();
            Q.pop();
            if (isdigit(cur[0])) {
                nums.push(stoi(cur));
            } else {
                char c = cur[0];
                double b = nums.top();
                nums.pop();
                double a = nums.top();
                nums.pop();
                if (c == '+') {
                    a += b;
                } else if (c == '-') {
                    a -= b;
                } else if (c == '*') {
                    a *= b;
                } else if (c == '/') {
                    a /= b;
                }
                nums.push(a);
            }
        }
        return nums.top();
    }
};

int main(int argc, char** argv) {
    Solution test;
    string expr = "10 - (2 * 3)";
    if (argc > 1) {
        expr = argv[1];
    }
    cout << expr << " = " << test.calculate(expr) << endl;
    return 0;
}
