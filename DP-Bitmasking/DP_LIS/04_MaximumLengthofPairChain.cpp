/*
Problem:
Find the maximum number of pairs that can be chained so that each pair ends before the next pair starts.

Approach:
Sort the pairs by their first element, then use dynamic programming.
For each pair i, try all earlier pairs j and extend the chain if pairs[j][1] < pairs[i][0].

Intuition:
After sorting, every valid chain is just a sequence of non-overlapping intervals. The DP checks how many pairs can be placed before the current pair.

Example:
pairs = [[1,2], [2,3], [3,4]]
The best chain has length 2: [[1,2], [3,4]].
*/
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end());
        int n=pairs.size();
        vector<int> len(n,1);

        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(pairs[j][1]<pairs[i][0]){
                    len[i]=max(len[i],len[j]+1);
                }
            }
        }
        return *max_element(len.begin(),len.end());
    }
};