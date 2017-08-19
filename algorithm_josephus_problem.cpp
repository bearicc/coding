// f(n,k) = ( josephus(n-1,k) + k-1 ) % n + 1
// f(n,k) = ( josephus(n-1,k) - k ) % n + 1
 
#include "common.h"

using namespace std;

int f_bf(int n, int k) {
    // brute-force
    vector<int> flag(n, true);
    int i = k-1, remain = n;
    flag[i] = false;
    --remain;
    while (remain > 0) {
        int step = k;
        while (step > 0) {
            i = (i + 1) % n;
            if (flag[i]) --step;
        }
        flag[i] = false;
        --remain;
    }
    return i;
}

int f(int n, int k) {
    if (n == 1) return 1;
    return (f(n-1, k) + k-1) % n + 1;
}

int f1_bf(int n, int k) {
    // brute-force
    vector<int> flag(n, true);
    int i = 0, remain = n;
    flag[i] = false;
    --remain;
    while (remain > 0) {
        int step = k;
        while (step > 0) {
            i = (i + 1) % n;
            if (flag[i]) --step;
        }
        flag[i] = false;
        --remain;
    }
    return i;
}

int f1(int n, int k, int begin=1) {
    if (n == 1) return 1;
    return (f(n-1, k) + begin - 1) % n + 1;
}

int main() {
    int n = 10, k = 2;
    for (int i = 1; i <= n; ++i) {
        cout << f_bf(i, k) % i + 1 << ' ';
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << f(i, k) << ' ';
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << f1(i, k, k) << ' ';
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << f1_bf(i, k)%i + 1 << ' ';
    }
    cout << endl;
    return 0;
}
