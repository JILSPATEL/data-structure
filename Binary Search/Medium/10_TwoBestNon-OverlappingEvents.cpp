/*
Description:
Given events [startTime, endTime, value], select at most two non-overlapping
events so that their total value is maximum. Two events are compatible when
the second event starts strictly after the first event ends.

Intuition:
After sorting events by start time, for every event we have two choices:
1. Take it, then continue with the first event whose start time is greater
     than the current event's end time.
2. Skip it and consider the next event.

Approach:
- Sort events by start time.
- Use binary search to find the first compatible event after a chosen event.
- Use memoization with state (index, count), where count is the number of
    events already selected. Stop after selecting two events.
- Return the maximum of taking and skipping the current event.

Example:
events = [[1, 3, 4], [2, 4, 3], [5, 6, 5]]

Taking [1, 3, 4] allows [5, 6, 5], giving 4 + 5 = 9. The event [2, 4, 3]
overlaps with the first event, so the maximum answer is 9.

Complexity:
Sorting takes O(n log n). There are O(n) DP states and each state performs
one binary search, so the total time complexity is O(n log n), with O(n)
space for memoization.
*/
class Solution {
public:
    int n;
    vector<vector<int>> dp;
    int binarySearch(vector<vector<int>> &events,int endTime){
        int l=0;
        int r=n-1;
        int result=n;

        while(l<=r){
            int mid=l+(r-l)/2;
            if(events[mid][0]>endTime){
                result=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        return result;
    }
    int solve(vector<vector<int>> &events,int i,int count){
        if(count==2 || i>=n){
            return 0;
        }
        if(dp[i][count]!=-1) return dp[i][count];
        int nextValidIdx=binarySearch(events,events[i][1]);
        int take=events[i][2]+solve(events,nextValidIdx,count+1);
        int notTake=solve(events,i+1,count);
        return dp[i][count]=max(take,notTake);
    }
    int maxTwoEvents(vector<vector<int>>& events) {
        n = events.size();
        dp.assign(n+1,vector<int>(3,-1));
        sort(begin(events),end(events));
        int cnt=0;
        return solve(events,0,cnt);
    }
};