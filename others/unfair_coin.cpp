#include "common.h"

int seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);

int flip_unfair_coin() {
    // p(0) = 0.1
    if (gen() % 100 < 10) {
        return 0;
    } else {
        return 1;
    }
}

int flip_unfair_coin2() {
    int a = 0, b = 0;
    while (a == b) {
        a = flip_unfair_coin();
        b = flip_unfair_coin();
    }
    return a;
}

void test(int(*f)()) {
    int n, count = 0, total = 1e6;
    for (int i = 0; i < total; ++i) {
        n = f();
        if (n == 0) {
            ++count;
        }
    }
    cout << "total = " << total << " count(0) == " << count << 
        " ratio = " << double(count) / total << endl;
}

int main() {
    test(flip_unfair_coin);
    test(flip_unfair_coin2);
    return 0;
}
