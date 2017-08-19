/*
 * Summary of cycle detection algorithms:
 * 
 * UndirectedGraph:
 *   Union Find
 *   Edges + Connected = Nodes
 *   DFS: Need parent node, three states: unvisited, visited, visiting
 *   BFS:
 *   
 * DirectedGraph:
 *   DFS: three states: unvisited, visited, visiting
 *   BFS:
 */
#include "common.h"

class UndirectedGraph {
public:
    bool has_cycle(vector<pair<int, int>>& edges) {
        // 0 unvisited; 1 visiting; 2 visited.
        unordered_map<int, int> visited;
        unordered_map<int, vector<int>> G = init_graph(edges);
        int count = 0;
        bool found = false;
        for (auto it = G.begin(); it != G.end(); ++it) {
            int cur = it->first;
            if (visited[cur] == 2) {
                continue;
            }
            ++count;
            found = found || has_cycle_dfs(G, -1, cur, visited);
        }
        cout << "Num of connected components: " << count << endl;
        return found;
    }
    bool has_cycle_bfs(vector<pair<int, int>>& edges) {
        queue<int> Q;
        unordered_map<int, int> visited;
        unordered_map<int, vector<int>> G = init_graph(edges);
        int count = 0;
        bool found = false;
        for (auto it = G.begin(); it != G.end(); ++it) {
            int cur = it->first;
            if (visited[cur] == 2) {
                continue;
            }
            ++count;
            Q.push(cur);
            visited[cur] = 1;
            while (!Q.empty()) {
                int cur = Q.front();
                Q.pop();
                for (const int& next: G[cur]) {
                    if (visited[next] == 2) {
                        continue;
                    } else if (visited[next] == 1) {
                        found = true;
                        continue;
                    } else {
                        Q.push(next);
                        visited[next] = 1;
                    }
                }
                visited[cur] = 2;
            }
        }
        cout << "Num of connected components: " << count << endl;
        return found;
    }
private:
    unordered_map<int, vector<int>> G;
    unordered_map<int, vector<int>> init_graph(vector<pair<int, int>>& edges) {
        for (const auto& edge: edges) {
            G[edge.first].push_back(edge.second);
            G[edge.second].push_back(edge.first);
        }
        return G;
    }
    bool has_cycle_dfs(unordered_map<int, vector<int>>& G,
                       int prev, int cur,
                       unordered_map<int, int>& visited) {
        bool found = false;
        for (const int& next: G[cur]) {
            if (prev == next || visited[next] == 2) {
                continue;
            } else if (visited[next] == 1) {
                cout << "Found cycle: " << prev << " --> " << cur << " --> " << next << endl;
                found = true;
            } else {
                visited[next] = 1;
                if (has_cycle_dfs(G, cur, next, visited)) {
                    found = true;
                }
            }
            visited[next] = 2;
        }
        return found;
    }
};

class DirectedGraph {
public:
    bool has_cycle(vector<pair<int, int>>& edges) {
        // 0 unvisited; 1 visiting; 2 visited.
        unordered_map<int, int> visited;
        unordered_map<int, vector<int>> G = init_graph(edges);
        int cur = G.begin()->first;
        visited[cur] = 1;
        return has_cycle_dfs(G, -1, cur, visited);
    }
private:
    unordered_map<int, vector<int>> G;
    unordered_map<int, vector<int>> init_graph(vector<pair<int, int>>& edges) {
        for (const auto& edge: edges) {
            G[edge.first].push_back(edge.second);
        }
        return G;
    }
    bool has_cycle_dfs(unordered_map<int, vector<int>>& G,
                       int prev, int cur,
                       unordered_map<int, int>& visited) {
        for (const int& next: G[cur]) {
            if (prev == next || visited[next] == 2) {
                continue;
            }
            if (visited[next] == 1) {
                cout << "Found cycle: " << prev << " --> " << cur << " --> " << next << endl;
                return true;
            }
            visited[next] = 1;
            if (has_cycle_dfs(G, cur, next, visited)) {
                return true;
            }
            visited[next] = 2;
        }
        return false;
    }
};

int main() {
    vector<pair<int, int>> edges{
        {1, 2},
        {2, 3},
        {1, 3},
        {4, 1},
        {4, 5},
        {5, 6},
        {6, 4},
        {7, 8}
    };
    UndirectedGraph graph;
    cout << "------------------------------------------------------------" << endl;
    cout << graph.has_cycle(edges) << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << graph.has_cycle_bfs(edges) << endl;
    DirectedGraph graph1;
    cout << "------------------------------------------------------------" << endl;
    cout << graph1.has_cycle(edges) << endl;
    return 0;
}
