#include <iostream>
#include <string>
#include <random>
#include <chrono>
using namespace std;

string random_string(int len) {
    size_t seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    uniform_int_distribution<int> dist(1, 26 + 26 + 10);
    string ret; int n;
    for (int i = 0; i < len; ++i) {
        n = dist(gen);
        if (n >= 1 && n <= 26) {
            ret.push_back(n-1+'A');
        } else if (n > 26 && n <=52) {
            ret.push_back(n-27+'a');
        } else {
            ret.push_back(n-53+'0');
        }
    }
    return ret;
}

int main(int argc, char** argv) {
    int n = 20;
    if (argc > 1) {
        n = stoi(argv[1]);
    }
    cout << random_string(n) << endl;
    return 0;
}
