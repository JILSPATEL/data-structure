/*
Problem:
Count the number of attendance records of length n that are eligible for an
award. A record uses P (Present), A (Absent), and L (Late), and is valid when
it contains at most one A and never contains three consecutive L characters.
Return the answer modulo 1e9 + 7.

Intuition:
The validity of the next character depends only on two pieces of information:
how many absences are still available and how many consecutive late days end
the current record. This makes the number of remaining valid records a DP
state rather than requiring the complete record history.

Approach:
Use solve(days, absencesLeft, consecutiveLates), where:
- days is the number of positions still to fill.
- absencesLeft is either 0 or 1.
- consecutiveLates is between 0 and 2.

For every state, try:
1. P: consume one day and reset consecutiveLates to 0.
2. A: consume one available absence and reset consecutiveLates to 0.
3. L: consume one day and increase consecutiveLates, if it stays below 3.

When days becomes 0, one valid record has been formed. The file shows the
same recurrence with recursion, memoization, and bottom-up tabulation.

Example (n = 2):
The valid records are PP, PA, AP, PL, LP, and LL, so the answer is 6.
Records such as AA are invalid because they contain two absences; records such
as LL are valid because they contain fewer than three consecutive lates.
*/

//Recursive

class Solution {
public:
    static const int MOD = 1000000007;

    int solve(int n, int ab, int lt) {

        // No days left → one valid record
        if (n == 0)
            return 1;

        long long ans = 0;

        // 1. Present
        ans += solve(n - 1, ab, 0);

        // 2. Absent
        if (ab > 0)
            ans += solve(n - 1, ab - 1, 0);

        // 3. Late
        if (lt < 2)
            ans += solve(n - 1, ab, lt + 1);

        return ans % MOD;
    }

    int checkRecord(int n) {
        return solve(n, 1, 0);
    }
};

//Recursive + Memoization

class Solution {
public:
    static const int MOD = 1000000007;
    vector<vector<vector<int>>> dp;

    int solve(int n, int ab, int lt) {
        if (n == 0)
            return 1;

        if (dp[n][ab][lt] != -1)
            return dp[n][ab][lt];

        long long ans = 0;

        ans += solve(n - 1, ab, 0);

        if (ab > 0)
            ans += solve(n - 1, ab - 1, 0);

        if (lt < 2)
            ans += solve(n - 1, ab, lt + 1);

        return dp[n][ab][lt] = ans % MOD;
    }

    int checkRecord(int n) {
        dp.assign(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));
        return solve(n, 1, 0);
    }
};

//Tabulation

class Solution {
public:
    static const int MOD = 1000000007;

    int checkRecord(int n) {

        vector<vector<vector<long long>>> dp(
            n + 1, vector<vector<long long>>(2, vector<long long>(3, 0)));

        for (int ab = 0; ab <= 1; ab++) {
            for (int lt = 0; lt <= 2; lt++) {
                dp[0][ab][lt] = 1;
            }
        }
        for (int day = 1; day <= n; day++) {
            for (int ab = 0; ab <= 1; ab++) {
                for (int lt = 0; lt <= 2; lt++) {
                    long long ans = dp[day - 1][ab][0];
                    if (ab > 0) {
                        ans += dp[day - 1][ab - 1][0];
                    }
                    if (lt < 2) {
                        ans += dp[day - 1][ab][lt + 1];
                    }
                    dp[day][ab][lt] = ans % MOD;
                }
            }
        }
        return dp[n][1][0];
    }
};