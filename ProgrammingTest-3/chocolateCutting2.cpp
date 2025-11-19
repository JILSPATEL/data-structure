/*
Problem: Chocolate Cutting

You are given one chocolate bar of size 2 × H.
A chocolate piece (rectangle) can be split in two ways:

1. Horizontal cut:
   W × H  →  W × H1   and   W × (H − H1)

2. Vertical cut:
   W × H  →  W1 × H   and   (W − W1) × H

All dimensions must remain positive integers.

You must perform exactly N − 1 splits to obtain N pieces with
given areas: S1, S2, …, SN.

Determine whether it is possible to obtain exactly these N areas.

Key Rules:
- Total area must match: S1 + S2 + ... + SN = 2H
- Odd areas must appear in pairs (only vertical cuts create odd areas)
- Any odd area S[i] must satisfy S[i] ≤ H

Final Conditions for YES:
1. sum(S) == 2H
2. count_odd(S) is even
3. All odd S[i] ≤ H

Time Complexity:  O(N)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long H;
    int N;

    cin >> H;   // FIRST: Height
    cin >> N;   // SECOND: number of pieces

    long long total = 0;
    int oddCount = 0;

    for (int i = 0; i < N; i++) {
        long long x;
        cin >> x;
        total += x;

        if (x & 1) {
            oddCount++;
            if (x > H) {
                cout << "NO";
                return 0;
            }
        }
    }

    if (total != 2LL * H) {
        cout << "NO";
        return 0;
    }

    if (oddCount % 2 == 0) cout << "YES";
    else cout << "NO";

    return 0;
}
