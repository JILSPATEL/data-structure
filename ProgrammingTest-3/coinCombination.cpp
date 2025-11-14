#include <bits/stdc++.h>
using namespace std;

/**
 * Problem:
 * Count the number of unordered ways to form:
 *     2a + 3b = N   (a, b >= 0)
 * Order of coins does NOT matter.
 *
 * Logic:
 *   (N - 3b) must be even → b % 2 == N % 2
 *   Valid b range: 0 to floor(N/3)
 *   Count arithmetic progression of valid b's.
 *
 * TC: O(T)   (each query O(1))
 * SC: O(1)
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long N;
        cin >> N;

        long long max_b = N / 3;
        long long par = N % 2;

        if (par > max_b) {
            cout << 0 << "\n";
            continue;
        }

        long long first_b = par;
        long long ans = (max_b - first_b) / 2 + 1;

        cout << ans << "\n";
    }

    return 0;
}
