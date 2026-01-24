#include <bits/stdc++.h>
using namespace std;

/**
 * Problem:
 * You have unlimited 2-rupee and 3-rupee coins.
 * Find the MINIMUM number of coins required to make exactly N rupees.
 *
 * Logic:
 *  - Prefer 3-rupee coins (fewer coins).
 *  - If N % 3 == 1, replace one 3-coin with two 2-coins (because 1 cannot be formed).
 *
 * Examples:
 *   Input: 7  → Output: 3   (3 + 2 + 2)
 *   Input: 10 → Output: 4   (3 + 3 + 2 + 2)
 *
 * Time Complexity (TC):
 *     O(1) per query  — direct formula, no loops.
 *
 * Space Complexity (SC):
 *     O(1) — uses only a few variables.
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    cin >> N;

    long long ans = 0;

    if (N % 3 == 0) {
        ans = N / 3;
    }
    else if (N % 3 == 1) {
        // replace one 3 with two 2's → subtract 4
        ans = (N - 4) / 3 + 2;
    }
    else { // N % 3 == 2
        ans = N / 3 + 1;
    }

    cout << ans;
    return 0;
}
