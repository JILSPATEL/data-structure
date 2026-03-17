/**
 * Problem: Matrix Chain Multiplication (MCM)
 * ------------------------------------------
 * We are given an array `arr` of size N where the dimension of the
 * i-th matrix is:
 *
 *      Matrix i = arr[i-1] x arr[i]
 *
 * Our task is to find the minimum number of scalar multiplications
 * required to multiply the chain of matrices.
 *
 * Example:
 * arr = {10, 20, 30, 40}
 *
 * Matrices:
 * A1 = 10 x 20
 * A2 = 20 x 30
 * A3 = 30 x 40
 *
 * Different parenthesizations give different multiplication costs.
 * We must choose the minimum cost.
 *
 * Key Idea:
 * ----------
 * If we place a partition at position k:
 *
 *      (Ai ... Ak) and (A(k+1) ... Aj)
 *
 * Then the cost becomes:
 *
 *      cost(i,k) + cost(k+1,j) + arr[i-1] * arr[k] * arr[j]
 *
 * Approaches:
 * ------------
 * 1) Memoization (Top Down DP)
 * 2) Tabulation (Bottom Up DP)
 */


 class Solution {
public:

    int solve(int i, int j, vector<int> &arr, vector<vector<int>> &dp){

        if(i == j) return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        int mini = 1e9;

        for(int k = i; k < j; k++){

            int steps =
                arr[i-1] * arr[k] * arr[j] +
                solve(i, k, arr, dp) +
                solve(k+1, j, arr, dp);

            mini = min(mini, steps);
        }

        return dp[i][j] = mini;
    }

    int matrixMultiplication(vector<int> &arr) {

        int n = arr.size();

        vector<vector<int>> dp(n, vector<int>(n, -1));

        return solve(1, n-1, arr, dp);
    }
};



//Tebulation

class Solution {
public:
    int matrixMultiplication(vector<int> &arr) {

        int n = arr.size();
        int dp[n][n];

        for(int i = 1; i < n; i++)
            dp[i][i] = 0;

        for(int i = n-1; i >= 1; i--){

            for(int j = i+1; j < n; j++){

                int mini = 1e9;

                for(int k = i; k < j; k++){

                    int steps =
                        arr[i-1] * arr[k] * arr[j]
                        + dp[i][k]
                        + dp[k+1][j];

                    mini = min(mini, steps);
                }

                dp[i][j] = mini;
            }
        }

        return dp[1][n-1];
    }
};