#include "common.h"

struct T {
    int val;
    string s;
    T(int val, string s):val(val), s(s) {}
    // used for unordered_set and unordered_map
    bool operator==(const T& t) const {
        return this->val == t.val;
    }
    // used for priority_queue, set and map
    bool operator<(const T& t) const {
        return this->val < t.val;
    }
    // used as comparator
    bool operator()(const T& a, const T& b) const {
        return a.val < b.val;
    }
    // needed for comparator
    T() = default;
};

struct Hash {
    size_t operator()(const T& t) const { size_t ret = 0;
        //ret ^= hash<int>()(t.val) + 0x9e3779b9 + (ret << 6) + (ret >> 2);
        //ret ^= hash<string>()(t.s) + 0x9e3779b9 + (ret << 6) + (ret >> 2);
        ret = hash<int>()(t.val) * 31 + hash<string>()(t.s);
        return ret;
    }
};

struct Compare {
    bool operator()(const T& l, const T& r) const {
        return l.val == r.val;
    }
};

// -----------------------------------------------------------------------------
// unordered_set
// unordered_set use Hash to calculate the bucket to store the element;
//   if two element collides, it then use compare to determine if put more elements
//   inside the same bucket.

int main() {
    auto cmp = [](const T& a, const T& b) {
        return a.val > b.val;
    };

    auto equal = [](const T& a, const T& b) {
        return a.val == b.val;
    };

    // -------------------------------------------------------------------------
    // unordered_set
    priority_queue<T, vector<T>, T> pq;
    priority_queue<T, vector<T>> pq1;
    priority_queue<T, vector<T>, Compare> pq2;
    priority_queue<T, vector<T>, decltype(cmp)> pq3(cmp);
    // -------------------------------------------------------------------------
    // unordered_set
    unordered_set<T, Hash> set1;
    unordered_set<T, Hash, decltype(equal)> set2(0, Hash(), equal);

    // ------------------------------------------------------------
    // unordered_map
    unordered_map<T, int, Hash, Compare> map1;
    unordered_map<T, int, Hash, T> map2;
    unordered_map<T, int, Hash, decltype(equal)> map3(0, Hash(), equal);
    
    // map
    map<T, int, decltype(cmp)> map4(cmp);
    return 0;
}
