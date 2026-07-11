/*
Problem Statement:
Given an undirected graph with V vertices and a list of edges, determine whether the graph contains a cycle.

Example:
Input: V = 4, edges = [[0,1], [1,2], [2,3], [3,1]]
Output: true
Explanation: The edge 3-1 creates a cycle 1-2-3-1.

Intuition:
In an undirected graph, if we try to connect two vertices that are already in the same connected component,
then adding that edge forms a cycle. DSU helps us track connected components efficiently.

Approach:
1. Create a DSU structure for all vertices.
2. For each edge (u, v), check whether u and v already belong to the same set.
3. If they do, a cycle is found.
4. Otherwise, union them and continue.
5. If no edge creates a cycle, return false.
*/

class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int node) {
        if (parent[node] == node)
            return node;
        return parent[node] = find(parent[node]);
    }

    void unionSet(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv)
            return;

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

class Solution {
public:
    bool isCycle(int V, vector<vector<int>>& edges) {
        DSU dsu(V);

        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];

            if (dsu.find(u) == dsu.find(v))
                return true;

            dsu.unionSet(u, v);
        }

        return false;
    }
};