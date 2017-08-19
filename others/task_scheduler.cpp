/*
Task Scheduler 所有题型包括:
1. Total time for executing all tasks in order with cool time;
2. Output the final task schedule in order with cool time;
3. Total time for executing all tasks without order with cool time (LC 621);
4. Output one of the final task schedule without order with cool time (Similar to LC 358);
5. 跟楼上说的topological sort 相似 (自给也没准备到这个变形)
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int task_scheduler(string& tasks, int n) {
    unordered_map<char, int> dict;
    int time = 0;
    cout << '"';
    for (const char& task: tasks) {
        ++time;
        // if (dict.find(task) != dict.end() && time - dict[task] <= n) time = dict[task] + n + 1;
        if (dict.find(task) != dict.end() && time - dict[task] <= n) {
            cout << string(dict[task] + n + 1 - time, '.');
            time = dict[task] + n + 1;
        }
        cout << task;
        dict[task] = time;
    }
    cout << '"' << endl;
    return time;
}

int main() {
    string tasks = "abacbbc";
    int n = 1;
    cout << task_scheduler(tasks, n) << endl;
    return 0;
}
