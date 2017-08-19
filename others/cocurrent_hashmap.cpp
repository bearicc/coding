#include <unordered_map>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
mutex r;
mutex w;

class HashMap {
public:
    HashMap():data(size, vector<int>()) {}
    int read(int key) {
        int ret = 0;
        begin_read();
        ret = dict[key];
        end_read();
        return ret;
    }
    void write(int key, int value) {
        begin_write();
        dict[key] = value;
        end_write();
    }
private:
    void begin_read() {
        r.lock();
        ++counter;
        if (counter == 1) w.lock();
        r.unlock();
    }
    void end_read() {
        r.lock();
        --counter;
        if (counter == 0) w.unlock();
        r.unlock();
    }
    void begin_write() {
        w.lock();
    }
    void end_write() {
        w.unlock();
    }
    int size = 1e6;
    vector<vector<int>> data;
    int counter = 0;
    int val = 0;
    unordered_map<int, int> dict;
};

void f(HashMap* map) {
    cout << map->read(1) << endl;
    map->write(1, 1);
    cout << map->read(1) << endl;
    map->write(2, 2);
    cout << map->read(2) << endl;
    map->write(3, 3);
    cout << map->read(3) << endl;
}

int main() {
    HashMap map;
    thread t1(f, &map);
    thread t2(f, &map);
    t1.join();
    t2.join();
    return 0;
}
