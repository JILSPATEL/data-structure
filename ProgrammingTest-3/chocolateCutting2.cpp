/**
 * --------------------- PROBLEM 1: Chocolate Splitting ---------------------
 *
 * You are given a chocolate bar of size 2 × H.
 * You want to split it into exactly N pieces such that the area of each piece is:
 *     S1, S2, ..., SN
 *
 * Rules:
 *  • You may split any piece vertically or horizontally.
 *  • Width/Height must always be positive integers.
 *  • Initially you have one piece of area = 2H.
 *
 * Determine if it is possible to obtain all required piece areas.
 *
 * IMPORTANT OBSERVATION:
 *  • Total area must match: sum(Si) = 2H
 *  • Only pieces of width 1 have odd area.
 *  • Maximum 2 odd-area pieces are possible.
 *      (because only two pieces can have width = 1 after vertical split)
 *
 * ---------------------------- Input Format ----------------------------
 * H
 * N
 * S1 S2 ... SN
 * ---------------------------- Sample Input ---------------------------
 * 3
 * 4
 * 1 2 1 2
 * ---------------------------- Sample Output --------------------------
 * YES
 * ----------------------------------------------------------------------
 * ---------------------- Time & Space Complexity -----------------------
 * Time Complexity  : O(N)
 * Space Complexity : O(1)
 * ----------------------------------------------------------------------
 */

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long H; 
    int N;
    cin >> H >> N;

    long long total = 0;
    int odd = 0;

    for(int i = 0; i < N; i++){
        long long x;
        cin >> x;
        total += x;
        if(x % 2) odd++;
    }

    if(total != 2LL * H){
        cout << "NO";
        return 0;
    }

    if(odd <= 2) cout << "YES";
    else cout << "NO";

    return 0;
}
