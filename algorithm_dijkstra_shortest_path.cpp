#include <climits>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct Node {
    int id;
    int dist;
    Node() {}
    Node(int id, int dist):id(id), dist(dist) {}
    bool operator()(const Node& a, const Node& b) const {
        return a.dist > b.dist;
    }
    // bool operator<(const Node& a) const {
    //     return this->dist > a.dist;
    // }
};

int dijkstra_shortest_path(unordered_map<int, vector<pair<int, int>>>& G,
                           int start, int end) {
    unordered_map<int, int> dist;
    unordered_map<int, int> prev;
    priority_queue<Node, vector<Node>, Node> Q;
    // priority_queue<Node> Q;

    for (auto it = G.begin(); it != G.end(); ++it) {
        dist[it->first] = INT_MAX;
        prev[it->first] = -1;
    }

    Q.push(Node(start, 0));
    dist[start] = 0;

    while (!Q.empty()) {
        Node cur = Q.top();
        Q.pop();
        int u = cur.id;

        if (u == end) {
            break;
        }

        for (const auto& next: G[u]) {
            int v = next.first;
            int w = next.second;
            int alt = dist[u] + w;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                Q.push(Node(v, alt));
            }
        }
    }

    int cur = end;
    while (cur != start) {
        cout << cur << " <- ";
        cur = prev[cur];
    }
    cout << start << endl;

    return dist[end];
}

int main() {
    unordered_map<int, vector<pair<int, int>>> G{
        {1, {{2, 7}, {3, 9}, {6, 14}}},
        {2, {{1, 7}, {3, 10}, {4, 15}}},
        {3, {{1, 9}, {2, 19}, {4, 11}, {6, 2}}},
        {4, {{2, 15}, {3, 11}, {5, 6}}},
        {5, {{4, 6}, {6, 9}}},
        {6, {{1, 14}, {3, 2}, {5, 9}}}
    };
    cout << dijkstra_shortest_path(G, 1, 4) << endl;
    return 0;
}
