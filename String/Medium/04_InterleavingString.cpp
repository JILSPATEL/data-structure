/*
Description:
Given strings s1, s2, and s3, determine whether s3 can be formed by
interleaving s1 and s2 while preserving the left-to-right order of characters
from each original string.

Intuition:
At every position in s3, the next character must come from either s1 or s2.
If both strings have the required character, both choices are possible, so we
try them recursively. The same pair of positions in s1 and s2 can be reached
through different paths, therefore memoization avoids solving that state again.

Approach:
1. If the combined lengths of s1 and s2 do not equal the length of s3, return
    false immediately.
2. Use solve(start1, start2, start3) to represent the remaining choices.
3. If s1[start1] matches s3[start3], try taking that character from s1.
4. If s2[start2] matches s3[start3], try taking that character from s2.
5. Memoize the result for each pair (start1, start2). Since start3 equals
    start1 + start2, it does not need to be part of the memoization key.

Example:
s1 = "aab", s2 = "axy", s3 = "aaxaby"

One valid construction is:
s1: a   a   b
s2:   a x   y
s3: a a x a b y

The characters from each source remain in their original order, so s3 is an
interleaving of s1 and s2.
*/
class Solution {
public:
    vector<vector<int>> dp;
    bool solve(string &s1, string &s2, string &s3,int start1 ,int start2 ,int start3){
        if(start3==s3.size()){
            return start1 == s1.size() && start2 == s2.size();
        }
        if(dp[start1][start2]!=-1) return dp[start1][start2];
        bool take1=false;
        bool take2=false;
        if(start1<s1.size() && s1[start1]==s3[start3]){
            take1=solve(s1,s2,s3,start1+1,start2,start3+1);
        }
        if(start2<s2.size() && s2[start2]==s3[start3]){
            take2=solve(s1,s2,s3,start1,start2+1,start3+1);
        }
        return dp[start1][start2]=(take1||take2);
    }
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        dp.assign(s1.size()+1,vector<int>(s2.size()+1,-1));
        return solve(s1,s2,s3,0,0,0);
    }
};