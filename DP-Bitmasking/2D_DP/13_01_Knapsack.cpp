/*
Problem: 0/1 Knapsack

Description:
Given a set of items, each with a value and a weight, choose items so that the
total weight does not exceed W and the total value is maximum. Each item can be
taken at most once.

Intuition:
For every item, there are only two choices: take it or skip it. If we know the
best answer for smaller subproblems, we can build the final answer from them.
This makes the problem a good fit for dynamic programming.

Approach:
1. Define dp[idx][w] as the maximum value possible using items from 0..idx with
    capacity w.
2. If we take item idx, we add its value and move to the previous item with the
    reduced capacity.
3. If we skip it, we keep the same capacity and move to the previous item.
4. The answer is the maximum of these two choices.

Example:
Values = [60, 100, 120], Weights = [10, 20, 30], W = 50
Best choice is items with weights 20 and 30, giving value 220.
*/

// Memoization
class Solution {
public:
    int n;
    vector<vector<int>> dp;

    int solve(int idx, int w, vector<int> &val, vector<int> &wt) {

        if (idx == 0) {
            if (wt[0] <= w)
                return val[0];
            return 0;
        }

        if (w == 0)
            return 0;

        if (dp[idx][w] != -1)
            return dp[idx][w];

        int take = 0, skip = 0;

        if (wt[idx] <= w)
            take = val[idx] + solve(idx - 1, w - wt[idx], val, wt);

        skip = solve(idx - 1, w, val, wt);

        return dp[idx][w] = max(take, skip);
    }

    int knapsack(int W, vector<int> &val, vector<int> &wt) {

        n = val.size();

        dp.assign(n, vector<int>(W + 1, -1));

        return solve(n - 1, W, val, wt);
    }
};


// Tabulation

class Solution {
	public:
	int n;
	vector<vector<int>> dp;
	
	int knapsack(int W, vector<int> &val, vector<int> &wt) {
		
		n = val.size();
		
		dp.assign(n, vector<int>(W + 1, 0));
		
		for (int w = wt[0]; w <= W; w++) {
			dp[0][w] = val[0];
		}
		for(int idx=1;idx<n;idx++){
		    for(int w=0;w<=W;w++){
		        int take=0;
		        if(wt[idx]<=w){
		            take=val[idx]+dp[idx-1][w-wt[idx]];
		        }
		        int skip=dp[idx-1][w];
		        dp[idx][w]=max(take,skip);
		    }
		}
		return dp[n-1][W];
	}
};


// Most Optimal

class Solution {
public:
    int knapsack(int W, vector<int> &val, vector<int> &wt) {

        int n = val.size();

        vector<int> prev(W + 1, 0);
        vector<int> curr(W + 1, 0);

        for (int w = wt[0]; w <= W; w++) {
            prev[w] = val[0];
        }

        for (int idx = 1; idx < n; idx++) {
            curr[0] = 0;

            for (int w = 1; w <= W; w++) {
                int take = 0;
                if (wt[idx] <= w)
                    take = val[idx] + prev[w - wt[idx]];

                int skip = prev[w];

                curr[w] = max(take, skip);
            }

            prev = curr;
        }

        return prev[W];
    }
};