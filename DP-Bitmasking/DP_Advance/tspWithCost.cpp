
//Time	O(n² × 2ⁿ)
//Space	O(n × 2ⁿ) 

#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e15;

// Optimized Held–Karp TSP
long long tsp(const vector<vector<long long>> &cost) {
    int n = cost.size();
    int FULL = 1 << n;
    vector<vector<long long>> dp(FULL, vector<long long>(n, INF));
    
    dp[1][0] = 0; // start from node 0

    // Iterate over all subsets (masks)
    for (int mask = 1; mask < FULL; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u))) continue; // u not in subset
            long long cur = dp[mask][u];
            if (cur == INF) continue;
            // try going to next node v
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue; // already visited
                int nmask = mask | (1 << v);
                dp[nmask][v] = min(dp[nmask][v], cur + cost[u][v]);
            }
        }
    }

    // final return to start (0)
    long long ans = INF;
    for (int i = 1; i < n; ++i)
        ans = min(ans, dp[FULL - 1][i] + cost[i][0]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<long long>> cost(n, vector<long long>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> cost[i][j];

    cout << tsp(cost) << "\n";
    return 0;
}

/*
input:
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

output:
80
*/