/*
Problem Description:
Given a matrix and an integer k, count the number of ways to make valid cuts so that
all resulting parts satisfy the required positive-sum condition. We can move from the
current position to the next row or next column, and only those transitions that keep
an acceptable submatrix are considered.

Example:
For a small matrix like [[1, 2], [3, 4]] and k = 2, one valid cut can be made after
one row or one column, creating two valid parts. The DP counts all such valid ways.
*/

//Memoization
/*
Approach 1: Memoization
We use DFS with memoization where dp[r][c][cuts] represents the number of ways to solve
from cell (r, c) with cuts remaining. From each state, we try moving downward and
rightward to the next possible position and only keep transitions that still form a
positive-sum submatrix.

Intuition:
The same state can be reached through different paths, so memoization avoids recomputing
it. This makes the search efficient while preserving the recursive structure of the problem.
*/
class Solution {
	public:
	const int MOD = 1000000007;
	int n, m;
	vector<vector<int>> suffix;
	vector<vector<vector<int>> > dp;
	
	int solve(int r, int c, int cuts) {
		if (suffix[r][c] == 0)
			return 0;
		if (cuts == 0)
			return 1;
		
		if (dp[r][c][cuts] != -1) {
			return dp[r][c][cuts];
		}
		
		long long ans = 0;
		
		for (int i = r + 1; i<n; i++) {
			if (suffix[r][c]-suffix[i][c]>0) {
				ans += solve(i, c, cuts - 1);
				ans %= MOD;
			}
		}
		
		for (int i = c + 1; i<m; i++) {
			if (suffix[r][c]-suffix[r][i]>0) {
				ans += solve(r, i, cuts - 1);
				ans %= MOD;
			}
		}
		return dp[r][c][cuts] = ans;
	}
	
	int findWays(vector<vector<int>> & matrix, int k) {
		n = matrix.size();
		m = matrix[0].size();
		suffix.assign(n + 1, vector<int>(m + 1, 0));
		
		for (int i = n - 1; i >= 0; i--) {
			for (int j = m - 1; j >= 0; j--) {
				suffix[i][j] = matrix[i][j]+suffix[i][j + 1]+suffix[i + 1][j]-suffix[i + 1][j + 1];
			}
		}
		dp.assign(n, vector<vector<int>> (m, vector<int>(k, -1)));
		return solve(0, 0, k - 1);
	}
};



//Tabulation
/*
Approach 2: Tabulation
We build the DP table bottom-up instead of using recursion. First, we compute suffix sums
for quick submatrix-sum checks, then fill dp[i][j][cuts] for increasing values of cuts.
Each state is built from the already solved states for fewer cuts.

Intuition:
This is the iterative version of the same idea. The base case is when no cuts remain,
and larger states are formed by extending valid transitions from the current cell.
*/

class Solution {
	public:
	const int MOD=1e9+7;
	int findWays(vector<vector<int>> & matrix, int k) {
		int n = matrix.size();
		int m = matrix[0].size();
		vector<vector<int>> suffix(n + 1, vector<int>(m + 1, 0));
		vector<vector<vector<int>> > dp(n, vector<vector<int>> (m, vector<int>(k, 0)));
		for (int i = n - 1; i >= 0; i--) {
			for (int j = m - 1; j >= 0; j--) {
				suffix[i][j] = matrix[i][j]+suffix[i][j + 1]+suffix[i + 1][j]-suffix[i + 1][j + 1];
			}
		}
		
		for (int i = 0; i<n; i++) {
			for (int j = 0; j<m; j++) {
				dp[i][j][0] = (suffix[i][j]>0);
			}
		}
		
		for (int cuts = 1; cuts<k; cuts++) {
			for (int r = n - 1; r >= 0; r--) {
				for (int c = m - 1; c >= 0; c--) {
					long long ways = 0;
					for (int i = r + 1; i<n; i++) {
						if (suffix[r][c]-suffix[i][c]>0) {
							ways += dp[i][c][cuts - 1];
							ways %= MOD;
						}
					}
					for (int i = c + 1; i<m; i++) {
						if (suffix[r][c]-suffix[r][i]>0) {
							ways += dp[r][i][cuts - 1];
							ways %= MOD;
						}
					}
					dp[r][c][cuts] = ways;
				}
			}
		}
		return dp[0][0][k - 1];
	}
};
