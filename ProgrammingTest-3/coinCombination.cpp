/**
 * ------------------ PROBLEM 2: Count Unordered Ways ------------------
 *
 * You have unlimited coins of:
 *    • 2 rupees
 *    • 3 rupees
 *
 * Count the number of unordered ways to make total sum N:
 *     2a + 3b = N
 *
 * Order does NOT matter.
 *
 * Constraints:
 *   1 ≤ T ≤ 100000
 *   1 ≤ N ≤ 1e18
 *
 * ---------------------------- Sample Input ----------------------------
 * 5
 * 1
 * 2
 * 3
 * 6
 * 7
 *
 * ---------------------------- Sample Output ---------------------------
 * 0
 * 1
 * 1
 * 2
 * 1
 *
 * ----------------------------------------------------------------------
 * ---------------------- Time & Space Complexity -----------------------
 * Time Complexity  : O(T)
 * Space Complexity : O(1)
 * ----------------------------------------------------------------------
 */

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--){
        long long N;
        cin >> N;

        long long max_b = N / 3;
        long long par = N % 2;

        if(par > max_b){
            cout << 0 << "\n";
            continue;
        }

        long long first_b = par;
        long long ans = (max_b - first_b) / 2 + 1;

        cout << ans << "\n";
    }
    return 0;
}
