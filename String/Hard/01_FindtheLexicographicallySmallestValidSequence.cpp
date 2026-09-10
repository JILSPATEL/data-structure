/*
Problem:
Given two strings `word1` (length n) and `word2` (length m), select a strictly increasing sequence
of indices i0 < i1 < ... < i(m-1) from `word1` (0-based) of length m such that for each position t:
- either `word1[it] == word2[t]`, or
- at most one position t may differ (one allowed substitution).

Return the lexicographically smallest such index sequence (as a vector of indices). If no valid
sequence exists, return an empty vector.

Approach / Intuition:
- Compute `firstPos[j]` by scanning `word1` from right to left and greedily matching the suffix
    `word2[j..m-1]`. `firstPos[j]` is the rightmost index in `word1` that can be used to match
    `word2[j]` while still matching the rest of the suffix. This tells us whether it's safe to place
    an index at position `i` for `word2[j]` and still be able to match the remaining characters.
- Then scan `word1` from left to right building the answer greedily to obtain the lexicographically
    smallest index sequence: take the earliest index `i` that either matches the needed character
    `word2[j]`, or — if we haven't used our single allowed substitution — take a mismatching index
    `i` only when it's safe (i.e. either this is the last character or `firstPos[j+1] > i`).
- Track a `canChange` flag to allow at most one mismatch.

Why this yields the smallest sequence:
- We always pick the earliest possible index for each next character. Allowing exactly one strategic
    mismatch only when future matches remain ensures we don't block matching later characters.

Example:
- `word1 = "bac"`, `word2 = "abc"` (n=3, m=3)
    - Exact matching sequence doesn't exist because `word2[0]='a'` first appears at index 1, and then
        there is no later `'b'` after index 1. By allowing one substitution at the first position we can
        choose indices `[0,1,2]`: at t=0 we accept `word1[0]='b'` (mismatch with 'a'), at t=1 `word1[1]='a'`
        (matches 'b'), and at t=2 `word1[2]='c'` (matches 'c'). This is valid and lexicographically
        smallest.

Complexity: O(n + m) time and O(m) extra space for `firstPos`.
*/

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n=word1.size();
        int m=word2.size();

        vector<int> firstPos(m,-1);
        int j=m-1;
        for(int i=n-1;i>=0;i--){
            if(word1[i]==word2[j]){
                firstPos[j]=i;
                j--;
                if(j<0) break;
            }
        }

        j=0;
        vector<int> res;
        bool canChange=true;
        for(int i=0;i<n;i++){
            if(j==m) break;
            if(word1[i]==word2[j]){
                res.push_back(i);
                j++;
            }else if(canChange && (j==m-1 || firstPos[j+1]>i)){
                res.push_back(i);
                canChange=false;
                j++;
            }
        }
        if(res.size()!=m) return {};
        return res;
    }
};