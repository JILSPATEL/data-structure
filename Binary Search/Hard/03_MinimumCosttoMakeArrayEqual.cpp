/*
Problem Explanation:
We need to make all elements of the array equal by choosing a target value,
while minimizing the total cost. For each element nums[i], if we change it to
some target value x, the cost is abs(nums[i] - x) * cost[i].

Intuition:
The total cost function is convex, so it decreases up to a certain point and
then increases. That means the minimum cost is found near the point where the
cost changes direction. We can use binary search to find that optimal target.

Approach:
For a guessed target mid, compute the total cost for making all elements equal
to mid and for mid + 1. Compare the two costs. If cost(mid) is smaller, move
left; otherwise move right. This narrows down to the minimum-cost value.

Example:
nums = [1, 3, 5, 2]
cost = [2, 3, 1, 4]
If we choose target 2:
- cost = |1-2|*2 + |3-2|*3 + |5-2|*1 + |2-2|*4 = 2 + 3 + 3 + 0 = 8
If we choose target 3:
- cost = |1-3|*2 + |3-3|*3 + |5-3|*1 + |2-3|*4 = 4 + 0 + 2 + 4 = 10
So 2 gives a smaller cost, and the optimal value is around 2.
*/

class Solution {
public:
    typedef long long ll;
    ll findCost(vector<int> &nums,vector<int> &cost,int tar){
        ll sum=0;

        for(int  i=0;i<nums.size();i++){
            sum+=(ll)abs(nums[i]-tar)*cost[i];
        }
        return sum;
    }
    long long minCost(vector<int>& nums, vector<int>& cost) {
        int n = nums.size();
        int low = *min_element(nums.begin(), nums.end());
        int high = *max_element(nums.begin(), nums.end());
        ll ans = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            ll cost1 = findCost(nums, cost, mid);
            ll cost2 = findCost(nums, cost, mid + 1);

            ans = min(cost1, cost2);

            if (cost1 < cost2) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};