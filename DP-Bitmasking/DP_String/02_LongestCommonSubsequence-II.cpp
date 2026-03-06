# Longest Common Subsequence (LCS)

The **Longest Common Subsequence (LCS)** problem is a classic **Dynamic Programming** problem.

Given two strings `s1` and `s2`, the goal is to find the **longest subsequence present in both strings**.

A **subsequence** is a sequence that appears in the same relative order but **not necessarily contiguous**.

Example:

s1 = "abcde"  
s2 = "ace"  

LCS = "ace"  
Length = 3

---

# Approach 1 — Recursion + Memoization (Top Down DP)

### Idea

For each character we have **two choices**

1. **Characters match**  
   Include the character in LCS

2. **Characters do not match**  
   Skip one character from either string

---

### Recurrence

If characters match:

```
s1[i] == s2[j]

LCS(i,j) = 1 + LCS(i-1,j-1)
```

If characters do not match:

```
LCS(i,j) = max(
    LCS(i-1,j),
    LCS(i,j-1)
)
```

---

### C++ Implementation

```cpp
/**
LCS using Memoization + Print LCS
*/

class Solution {
public:

    int solve(int i,int j,string &s1,string &s2,vector<vector<int>> &dp){

        if(i<0 || j<0)
        return 0;

        if(dp[i][j]!=-1)
        return dp[i][j];

        if(s1[i]==s2[j])
        return dp[i][j]=1+solve(i-1,j-1,s1,s2,dp);

        return dp[i][j]=max(
            solve(i-1,j,s1,s2,dp),
            solve(i,j-1,s1,s2,dp)
        );
    }

    string printLCS(string s1,string s2){

        int n=s1.size();
        int m=s2.size();

        vector<vector<int>> dp(n,vector<int>(m,-1));

        solve(n-1,m-1,s1,s2,dp);

        int i=n-1;
        int j=m-1;

        string ans="";

        while(i>=0 && j>=0){

            if(s1[i]==s2[j]){
                ans+=s1[i];
                i--;
                j--;
            }

            else if(i>0 && dp[i-1][j] >= dp[i][j-1]){
                i--;
            }

            else{
                j--;
            }
        }

        reverse(ans.begin(),ans.end());

        return ans;
    }
};
```

---

### Complexity

Time Complexity

```
O(n*m)
```

Space Complexity

```
O(n*m) + recursion stack
```

---

# Approach 2 — Tabulation + Print LCS

### Idea

We build a **DP table** where

```
dp[i][j] = LCS length of first i characters of s1
           and first j characters of s2
```

---

### Transition

If characters match:

```
dp[i][j] = 1 + dp[i-1][j-1]
```

If characters do not match:

```
dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

---

### C++ Implementation (Print LCS)

```cpp
/**
Longest Common Subsequence
Approach 2 : Tabulation + Print LCS
*/

class Solution {
public:

    string longestCommonSubsequence(string s1, string s2) {

        int n=s1.size();
        int m=s2.size();

        vector<vector<int>> dp(n+1,vector<int>(m+1,0));

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){

                if(s1[i-1]==s2[j-1])
                dp[i][j]=1+dp[i-1][j-1];

                else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }

        int i=n;
        int j=m;

        string ans="";

        while(i>0 && j>0){

            if(s1[i-1]==s2[j-1]){
                ans+=s1[i-1];
                i--;
                j--;
            }

            else if(dp[i-1][j]>dp[i][j-1]){
                i--;
            }

            else{
                j--;
            }
        }

        reverse(ans.begin(),ans.end());

        return ans;
    }
};
```

---

# Example

Input

```
s1 = "abcde"
s2 = "ace"
```

DP Table Result

```
LCS length = 3
```

Printed LCS

```
ace
```

---

# Complexity

Time Complexity

```
O(n*m)
```

Space Complexity

```
O(n*m)
```

---

# Key Interview Insight

Many important problems are based on **LCS pattern**

Examples:

1. Longest Palindromic Subsequence  
2. Shortest Common Supersequence  
3. Minimum Insertions to Make Palindrome  
4. Edit Distance  
5. Minimum Insert/Delete to Convert String  

These problems are very common in **GATE, FAANG, and coding interviews**.
