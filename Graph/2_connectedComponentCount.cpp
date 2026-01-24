#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>> &adj, int u, vector<int> &vis) {
        vis[u] = 1;
        for (auto it : adj[u]) {
            if (!vis[it]) {
                dfs(adj, it, vis);
            }
        }
    }

    int countComponents(int V, vector<vector<int>> &edges) {
        vector<vector<int>> adj(V);
        vector<int> vis(V, 0);

        // Build adjacency list
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]); // undirected
        }

        int count = 0;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                count++;
                dfs(adj, i, vis);
            }
        }

        return count;
    }
};

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> edges(E, vector<int>(2));
    for (int i = 0; i < E; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }

    Solution obj;
    cout << obj.countComponents(V, edges) << endl;

    return 0;
}
