/*
Problem:
Given two strings `s1` and `s2` of equal length, transform `s1` into `s2`. In one operation,
choose any character from `s1` and move it to the front. Return the minimum number of operations,
or `-1` if the transformation is impossible.

Approach / Intuition:
- Moving a character to the front preserves the relative order of all characters that are not
    moved. Therefore, `s2` must contain a suffix that can be matched as a subsequence of `s1`.
- Before looking for that subsequence, check that both strings have the same length and character
    frequencies. If their lengths differ, or `s2` needs a character that `s1` does not contain,
    the transformation is impossible.
- Match the strings from right to left. For every character in `s2`, move left through `s1` until
    the same character is found. Every unmatched character skipped in `s1` must be moved to the
    front, so add it to the answer.
- Matching from the end keeps the longest possible suffix of `s1` in its original relative order.
    Consequently, the number of moved characters is minimized.

Why this works:
- The right-to-left scan chooses a valid occurrence for each character of `s2` while preserving
    their order. Characters skipped in `s1` are exactly the characters that must be moved to the
    front. Any valid transformation must move at least these characters, so the count is minimum.

Complexity: O(n) time and O(k) extra space, where `n` is the string length and `k` is the number
of distinct characters.
*/

class Solution {
  public:
    int transform(string &s1, string &s2) {
        int n1=s1.size();
        int n2=s2.size();
        
        if(n1!=n2) return -1;
        
        unordered_map<char,int> mp;
        for(char ch:s1){
            if(mp.count(ch)){
                mp[ch]++;
            }else{
                mp[ch]=1;
            }
        }
        
        for(char ch:s2){
            if(mp.count(ch)){
                mp[ch]--;
                if(mp[ch]==0){
                    mp.erase(ch);
                }
            }
        }
        if(mp.size()) return -1;
        
        int i=n1-1;
        int j=n2-1;
        int res=0;
        while(i>=0 && j>=0){
            while(i>=0 && s1[i]!=s2[j]){
                res++;
                i--;
            }
            i--;
            j--;
        }
        return res;
    }
};
