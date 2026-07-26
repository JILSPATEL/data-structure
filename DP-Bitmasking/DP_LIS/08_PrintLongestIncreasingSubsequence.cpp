//Tebulation
class Solution {
	public:
	vector<int> getLIS(vector<int>& a) {
		int n = a.size();
		vector<int> b = a;
		sort(b.begin(), b.end());
		b.erase(unique(b.begin(), b.end()), b.end());
		int m = b.size();
		vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (a[i - 1] == b[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1]+1;
				} else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		vector<int> ans;
		int i = n, j = m;
		while (i>0 && j>0)
			{
			if (a[i - 1] == b[j - 1])
				{
				ans.push_back(a[i - 1]);
				i--;
				j--;
			}
			else if (dp[i - 1][j] >= dp[i][j - 1])
				{
				i--;
			}
			else
				{
				j--;
			}
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
};
