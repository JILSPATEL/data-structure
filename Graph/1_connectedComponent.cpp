#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>> &adj, int u, vector<int> &vis, vector<int> &res) {
        vis[u] = 1;
        res.push_back(u);

        for (auto it : adj[u]) {
            if (!vis[it]) {
                dfs(adj, it, vis, res);
            }
        }
    }

    vector<vector<int>> getComponents(int V, vector<vector<int>> &edges) {
        vector<int> vis(V, 0);
        vector<vector<int>> adj(V);

        // Build adjacency list
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]); // undirected graph
        }

        vector<vector<int>> ans;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                vector<int> res;
                dfs(adj, i, vis, res);
                ans.push_back(res);
            }
        }

        return ans;
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
    vector<vector<int>> components = obj.getComponents(V, edges);

    // Print connected components
    for (auto &comp : components) {
        for (int node : comp) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
