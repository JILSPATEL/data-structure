/*
Problem: Divide Intervals Into Minimum Number of Groups

Description:
We are given intervals and need to split them into the minimum number of groups
such that no two intervals in the same group overlap.

Approach:
1. Sort all interval start points and end points separately.
2. Maintain a running counter for the number of active groups.
3. If the next start is less than or equal to the current earliest end, a new
   active interval is added to the same group count.
4. Otherwise, one group ends and we move to the next finishing interval.
5. The maximum active count seen is the answer.

Example:
intervals = [[1, 3], [2, 4], [3, 5], [7, 9]]
- Group 1: [1,3], [2,4], [3,5] all overlap at some point
- We need at least 3 groups to keep non-overlapping intervals separate
Answer = 3
*/

class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        vector<int> start;
        vector<int> end;
        for(auto &vec:intervals){
            start.push_back(vec[0]);
            end.push_back(vec[1]);
        }

        sort(start.begin(),start.end());
        sort(end.begin(),end.end());

        int n=start.size();
        int i=0;
        int j=0,maxi=0;
        int cnt=0;
        while(i<n){
            if(start[i]<=end[j]){
                i++;
                cnt++;
                maxi=max(maxi,cnt);
            }else{
                cnt--;
                j++;
            }
        }
        return maxi;
    }
};