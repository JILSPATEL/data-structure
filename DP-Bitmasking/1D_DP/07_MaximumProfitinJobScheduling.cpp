/*
Problem Description:
Given a list of jobs with start time, end time, and profit, select non-overlapping jobs
to maximize the total profit. A job ending at time t can be followed by a job starting
at time t.

Intuition:
After sorting the jobs by start time, at every index there are only two choices:
skip the current job or take it. If the job is taken, the next choice must be the first
job whose start time is at least the current job's end time. Because jobs are sorted,
that next compatible job can be found with binary search. Memoization avoids solving
the same suffix of jobs more than once.

Approach:
1. Store each job as {start, end, profit} and sort the jobs by start time.
2. Define solve(idx) as the maximum profit obtainable from jobs[idx] onward.
3. Find the first compatible job using binary search on start times.
4. Compute max(skip current job, current profit + solve(next compatible job)) and cache it.

Example:
Jobs = {(1, 3, 50), (2, 4, 10), (3, 5, 40), (5, 6, 70)}
Taking (1, 3, 50) allows (3, 5, 40), which allows (5, 6, 70).
Their total profit is 50 + 40 + 70 = 160, which is better than the alternatives.

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

class Solution {
public:
    vector<int> dp;
    int solve(int idx,vector<vector<int>> &job){
        if(idx==job.size()) return 0;
        if(dp[idx]!=-1)return dp[idx];
        int skip=solve(idx+1,job);
        int low = idx + 1;
        int high = job.size() - 1;
        int next = job.size();
        while(low<=high){
            int mid=(low+high)/2;
            if(job[mid][0]>=job[idx][1]){
                next=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        int take=job[idx][2]+solve(next,job);
        return dp[idx]=max(take,skip);
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n=startTime.size();
        vector<vector<int>> job;
        for(int i=0;i<n;i++){
            job.push_back({startTime[i],endTime[i],profit[i]});
        }
        dp.assign(n,-1);
        sort(job.begin(),job.end());
        return solve(0,job);
    }
};