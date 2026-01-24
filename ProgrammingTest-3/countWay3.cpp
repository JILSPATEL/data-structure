/**
 * Count Ways (Hard Version)
 * 
 * Problem: Count ordered sequences of 2 and 3 rupee coins that sum to exactly N rupees.
 * Order matters - different sequences are counted separately.
 * 
 * Constraints: 1 ≤ N ≤ 10^18, 1 ≤ T ≤ 1000
 * 
 * Sample Input:
 * 5
 * 1
 * 2
 * 3
 * 5
 * 10
 * 
 * Sample Output:
 * 0
 * 1
 * 1
 * 2
 * 7
 * 
 * Approach:
 * Recurrence: f(n) = f(n-2) + f(n-3)
 * This is a linear recurrence that can be solved using matrix exponentiation.
 * 
 * Base cases: 
 * f(0) = 1, f(1) = 0, f(2) = 1, f(3) = 1
 * 
 * We can represent the recurrence as:
 * [f(n)  ]   = [0 1 0]   [f(n-1)]
 * [f(n-1)]     [0 0 1]   [f(n-2)]
 * [f(n-2)]     [1 1 0]   [f(n-3)]
 */

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

// Matrix multiplication
vector<vector<long long>> matMul(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();
    
    vector<vector<long long>> C(n, vector<long long>(m, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    
    return C;
}

// Matrix exponentiation
vector<vector<long long>> matPow(vector<vector<long long>> A, long long power) {
    int n = A.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    
    // Initialize result as identity matrix
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    
    while (power > 0) {
        if (power & 1) {
            result = matMul(result, A);
        }
        A = matMul(A, A);
        power >>= 1;
    }
    
    return result;
}

long long solve(long long N) {
    if (N == 0) return 1;
    if (N == 1) return 0;
    if (N == 2) return 1;
    if (N == 3) return 1;
    
    // Transformation matrix for recurrence f(n) = f(n-2) + f(n-3)
    // We can write it as: f(n) = 0*f(n-1) + 1*f(n-2) + 1*f(n-3)
    vector<vector<long long>> T = {
        {0, 1, 1},
        {1, 0, 0},
        {0, 1, 0}
    };
    
    // Base vector [f(2), f(1), f(0)] = [1, 0, 1]
    vector<vector<long long>> base = {
        {1},
        {0}, 
        {1}
    };
    
    // We need to compute f(N) where N >= 4
    // T^(N-2) * base will give us [f(N), f(N-1), f(N-2)]^T
    auto T_pow = matPow(T, N - 2);
    auto result = matMul(T_pow, base);
    
    return result[0][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        long long N;
        cin >> N;
        cout << solve(N) << "\n";
    }
    
    return 0;
}