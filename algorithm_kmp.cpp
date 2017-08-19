#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> kmp_table(const string& s) {
    vector<int> dict(s.size(), 0);
    int i = 0, j = 0;
    for (i = 1; i < s.size(); ++i) {
        while (j > 0 && s[i] != s[j]) {
            j = dict[j-1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        dict[i] = j;
    }
    return dict;
}

int kmp_search(string& source, string& target) {
    int i = 0, j = 0;
    vector<int> dict = kmp_table(target);
    while (i+j < source.size()) {
        if (source[i+j] == target[j]) {
            ++j;
            if (j == target.size()) {
                return i;
            }
        } else if (j == 0) {
            ++i;
        } else {
            i = i + j - dict[j-1];
            j = dict[j-1];
        }
    }
    return -1;
}

int main() {
    string source = "This is a test.", target = "test";
    cout << kmp_search(source, target) << endl;
    return 0;
}
