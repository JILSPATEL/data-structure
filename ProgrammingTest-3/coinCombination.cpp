/**
 * ---------------- PROBLEM 3: Count Ordered Ways (Hard) ----------------
 *
 * You must count the number of ordered sequences of:
 *    • 2-rupee coin
 *    • 3-rupee coin
 *
 * That sum to exactly N.
 * Order matters.
 *
 * Recurrence:
 *    dp[n] = dp[n-2] + dp[n-3]
 *
 * Constraints:
 *   1 ≤ T ≤ 1000
 *   1 ≤ N ≤ 1e18
 * 
 * ---------------------------- Sample Input ----------------------------
 * 5
 * 1
 * 2
 * 3
 * 5
 * 10
 *
 * ---------------------------- Sample Output ---------------------------
 * 0
 * 1
 * 1
 * 2
 * 7
 *
 * ----------------------------------------------------------------------
 * ---------------------- Time & Space Complexity -----------------------
 * Time Complexity  : O(log N) per test (matrix exponentiation)
 * Space Complexity : O(1)
 * ----------------------------------------------------------------------
 */

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9+7;

struct Mat {
    long long a[3][3];
    Mat(){ memset(a, 0, sizeof(a)); }
};

Mat multiply(Mat A, Mat B){
    Mat C;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
    return C;
}

Mat power(Mat M, long long n){
    Mat R;
    for(int i=0;i<3;i++) R.a[i][i] = 1;

    while(n){
        if(n & 1) R = multiply(R, M);
        M = multiply(M, M);
        n >>= 1;
    }
    return R;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--){
        long long N;
        cin >> N;

        if(N == 0) { cout << 1 << "\n"; continue; }
        if(N == 1) { cout << 0 << "\n"; continue; }
        if(N == 2) { cout << 1 << "\n"; continue; }
        if(N == 3) { cout << 1 << "\n"; continue; }

        Mat M;
        M.a[0][1] = 1;
        M.a[0][2] = 1;
        M.a[1][0] = 1;
        M.a[2][1] = 1;

        long long P = N - 3;
        Mat R = power(M, P);

        long long dp3 = 1, dp2 = 1, dp1 = 0;

        long long ans = (
            R.a[0][0] * dp3 +
            R.a[0][1] * dp2 +
            R.a[0][2] * dp1
        ) % MOD;

        cout << ans << "\n";
    }
    return 0;
}
/**
 * ---------------- PROBLEM 3: Count Ordered Ways (Hard) ----------------
 *
 * You must count the number of ordered sequences of:
 *    • 2-rupee coin
 *    • 3-rupee coin
 *
 * That sum to exactly N.
 * Order matters.
 *
 * Recurrence:
 *    dp[n] = dp[n-2] + dp[n-3]
 *
 * Constraints:
 *   1 ≤ T ≤ 1000
 *   1 ≤ N ≤ 1e18
 * 
 * ---------------------------- Sample Input ----------------------------
 * 5
 * 1
 * 2
 * 3
 * 5
 * 10
 *
 * ---------------------------- Sample Output ---------------------------
 * 0
 * 1
 * 1
 * 2
 * 7
 *
 * ----------------------------------------------------------------------
 * ---------------------- Time & Space Complexity -----------------------
 * Time Complexity  : O(log N) per test (matrix exponentiation)
 * Space Complexity : O(1)
 * ----------------------------------------------------------------------
 */

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9+7;

struct Mat {
    long long a[3][3];
    Mat(){ memset(a, 0, sizeof(a)); }
};

Mat multiply(Mat A, Mat B){
    Mat C;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
    return C;
}

Mat power(Mat M, long long n){
    Mat R;
    for(int i=0;i<3;i++) R.a[i][i] = 1;

    while(n){
        if(n & 1) R = multiply(R, M);
        M = multiply(M, M);
        n >>= 1;
    }
    return R;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--){
        long long N;
        cin >> N;

        if(N == 0) { cout << 1 << "\n"; continue; }
        if(N == 1) { cout << 0 << "\n"; continue; }
        if(N == 2) { cout << 1 << "\n"; continue; }
        if(N == 3) { cout << 1 << "\n"; continue; }

        Mat M;
        M.a[0][1] = 1;
        M.a[0][2] = 1;
        M.a[1][0] = 1;
        M.a[2][1] = 1;

        long long P = N - 3;
        Mat R = power(M, P);

        long long dp3 = 1, dp2 = 1, dp1 = 0;

        long long ans = (
            R.a[0][0] * dp3 +
            R.a[0][1] * dp2 +
            R.a[0][2] * dp1
        ) % MOD;

        cout << ans << "\n";
    }
    return 0;
}
