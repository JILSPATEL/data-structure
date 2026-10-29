/*
Problem: Maximum Score Between Two Leaf Nodes

Description:
You are given a weighted tree with N nodes and N-1 edges.
Each edge has a weight.

A leaf is a node connected to exactly one other node.

For every pair of distinct leaf nodes A and B, calculate:

Score(A, B) = PathSum(A, B) + MaxEdge(A, B)

Where:
- PathSum(A, B) is the sum of all edge weights on the path
  between A and B.
- MaxEdge(A, B) is the maximum edge weight on that path.

Return the maximum score among all pairs of distinct leaf nodes.

Approach: Tree DP + Rerooting

1. Root the tree at node 1.

2. Calculate down[u]:
   The maximum distance from node u to any leaf in its
   subtree.

3. Calculate up[u]:
   The maximum distance from node u to any leaf outside
   its subtree.

4. For every parent-child edge (u, v) with weight w,
   calculate the maximum distance from u to a leaf outside
   the subtree of v.

5. Use the two sides of the edge to form a candidate score:

   candidate = outsideDistance + down[v] + 2 * w

   The extra w accounts for the additional contribution of
   the selected edge to the score.

6. Take the maximum candidate over all edges.

Complexity:
- Time: O(N)
- Space: O(N)

Key Observation:
Instead of checking every pair of leaves, process each edge
and combine the best leaf distances on its two sides.

This reduces the time complexity from O(N^2) to O(N).

Note:
The above candidate formula assumes the selected edge is the
maximum-weight edge on the resulting path. A correct general
solution must account for this condition when edge weights
are arbitrary.
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NEG_INF = LLONG_MIN / 4;

ll maxLeafScore(int n, const vector<array<ll, 3>>& edges) {
    if (n < 2) return 0;

    vector<vector<pair<int, ll>>> adj(n + 1);

    for (auto e : edges) {
        int u = e[0], v = e[1];
        ll w = e[2];

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> parent(n + 1, 0), order;
    vector<ll> down(n + 1, NEG_INF);
    vector<ll> up(n + 1, NEG_INF);

    stack<int> st;
    st.push(1);
    parent[1] = -1;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        order.push_back(u);

        for (auto [v, w] : adj[u]) {
            if (v == parent[u]) continue;

            parent[v] = u;
            st.push(v);
        }
    }

    // Calculate the maximum distance to a leaf in each subtree.
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];

        if (adj[u].size() == 1)
            down[u] = 0;

        for (auto [v, w] : adj[u]) {
            if (parent[v] == u && down[v] != NEG_INF)
                down[u] = max(down[u], w + down[v]);
        }
    }

    ll answer = NEG_INF;

    // Calculate distances to leaves outside each subtree.
    for (int u : order) {
        ll best1 = NEG_INF, best2 = NEG_INF;
        int bestChild = -1;

        for (auto [v, w] : adj[u]) {
            if (parent[v] != u || down[v] == NEG_INF)
                continue;

            ll d = w + down[v];

            if (d > best1) {
                best2 = best1;
                best1 = d;
                bestChild = v;
            } else if (d > best2) {
                best2 = d;
            }
        }

        for (auto [v, w] : adj[u]) {
            if (parent[v] != u)
                continue;

            ll siblingBest = (v == bestChild) ? best2 : best1;
            ll outsideU = up[u];

            if (adj[u].size() == 1)
                outsideU = max(outsideU, 0LL);

            outsideU = max(outsideU, siblingBest);

            if (outsideU != NEG_INF && down[v] != NEG_INF) {
                answer = max(answer, outsideU + down[v] + 2LL * w);
                up[v] = outsideU + w;
            }
        }
    }

    return (answer == NEG_INF) ? 0 : answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<array<ll, 3>> edges;

    for (int i = 0; i < n - 1; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    cout << maxLeafScore(n, edges) << '\n';

    return 0;
}