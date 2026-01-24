#include <bits/stdc++.h>
using namespace std;

// BFS from v to the nearest leaf, tracking path max
int minMaxPathToLeaf(int start, map<int, vector<int> >& adj) {
    queue<pair<int,int> > q;   // {node, maxValueSoFar}
    set<int> visited;          // visited nodes

    q.push(make_pair(start, start));
    visited.insert(start);

    int minPathWeight = INT_MAX;

    while (!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();

        int u = p.first;
        int pathMax = p.second;

        // Check if leaf (degree == 1 and not the start)
        if (u != start && adj[u].size() == 1) {
            if (pathMax < minPathWeight) {
                minPathWeight = pathMax;
            }
        }

        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                q.push(make_pair(v, max(pathMax, v)));
            }
        }
    }

    if (minPathWeight == INT_MAX) return -1; // no leaf reachable
    return minPathWeight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    map<int, vector<int> > adj;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int v_target;
    cin >> v_target;

    int ans = minMaxPathToLeaf(v_target, adj);
    cout << ans << "\n";

    return 0;
}
