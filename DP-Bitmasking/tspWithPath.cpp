//Time	O(n² × 2ⁿ)
//Space	O(n × 2ⁿ) 


#include <bits/stdc++.h>
using namespace std;
const long long INF = 9e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<vector<long long>> a(n, vector<long long>(n));
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            cin >> a[i][j];

    int START = 0;
    int FULL = (1<<n);
    vector<vector<long long>> dp(FULL, vector<long long>(n, INF));
    vector<vector<int>> parent(FULL, vector<int>(n, -1));

    dp[1<<START][START] = 0;

    for (int mask = 0; mask < FULL; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (!(mask & (1<<last))) continue;
            long long cur = dp[mask][last];
            if (cur == INF) continue;
            // try extend to nxt
            for (int nxt = 0; nxt < n; ++nxt) {
                if (mask & (1<<nxt)) continue;
                int nmask = mask | (1<<nxt);
                long long cand = cur + a[last][nxt];
                if (cand < dp[nmask][nxt]) {
                    dp[nmask][nxt] = cand;
                    parent[nmask][nxt] = last;
                }
            }
        }
    }

    // complete tour: return to START
    long long best = INF;
    int last_best = -1;
    int all = FULL - 1;
    for (int v = 0; v < n; ++v) {
        if (v == START) continue;
        long long cost = dp[all][v] + a[v][START];
        if (cost < best) {
            best = cost;
            last_best = v;
        }
    }

    if (n == 1) {
        cout << 0 << "\n" << 0 << "\n";
        return 0;
    }

    // reconstruct path (reverse)
    vector<int> path;
    int mask = all;
    int cur = last_best;
    if (last_best == -1) {
        cout << "No Hamiltonian cycle found\n";
        return 0;
    }
    while (cur != -1) {
        path.push_back(cur);
        int p = parent[mask][cur];
        mask ^= (1<<cur);
        cur = p;
    }
    // path currently: last -> ... -> START
    reverse(path.begin(), path.end());
    // add return to START explicitly
    path.push_back(START);

    cout << best << "\n";
    for (size_t i=0;i<path.size();++i) {
        cout << path[i] << (i+1==path.size() ? '\n' : ' ');
    }
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
0 1 3 2 0
*/