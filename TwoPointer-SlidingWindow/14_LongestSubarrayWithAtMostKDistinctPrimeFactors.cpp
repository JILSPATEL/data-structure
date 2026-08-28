/**
 * Problem: Longest Subarray With At Most K Distinct Prime Factors
 * ---------------------------------------------------------------
 * Find the longest contiguous subarray whose elements contain at most k
 * different prime factors in total. Repeated occurrences of the same prime
 * count only once.
 *
 * Intuition:
 * Each number can be represented by its distinct prime factors. For example,
 * 60 = 2 x 2 x 3 x 5, so its distinct prime factors are {2, 3, 5}.
 * While expanding a window, maintain the frequency of every prime appearing
 * in the window. If the number of distinct primes becomes greater than k,
 * move the left pointer forward until the window is valid again.
 *
 * How prime factors are derived:
 * 1. Try every possible divisor p starting from 2 while p x p <= x.
 * 2. If x is divisible by p, add p once because we need distinct factors.
 * 3. Divide x by p repeatedly to remove all copies of that factor.
 * 4. After the loop, if x > 1, the remaining x is prime and must be added.
 *
 * The final step is necessary because a leftover value greater than 1 cannot
 * have two factors greater than 1; otherwise one of them would have been at
 * most the square root of the value and found during the loop.
 *
 * Approach:
 * 1. Factor every array element and store its distinct prime factors.
 * 2. Expand the right side of a sliding window and update prime frequencies.
 * 3. When distinct > k, remove all factors of nums[left] and advance left.
 * 4. Record the maximum valid window length.
 *
 * Example:
 * nums = [2, 6, 15, 7], k = 3
 *
 * Factors: 2 -> {2}, 6 -> {2, 3}, 15 -> {3, 5}, 7 -> {7}
 * Window [2, 6, 15] contains {2, 3, 5}, so its length is 3 and it is valid.
 * Adding 7 gives {2, 3, 5, 7}, which has 4 distinct primes. Remove elements
 * from the left until the window is valid again. The answer is 3.
 *
 * Time Complexity: O(n * sqrt(max(nums)))
 * Space Complexity: O(n + max(nums))
 */

class Solution {
public:
    int longestSubarray(vector<int>& nums, int k) {
        int n=nums.size();
        vector<vector<int>> factors(n);
        for(int i=0;i<n;i++){
            int x=nums[i];

            for(int p=2;p*p<=x;p++){
                if(x%p==0){
                    factors[i].push_back(p);
                    while(x%p==0){
                        x/=p;
                    }
                }
            }
            if(x>1){
                factors[i].push_back(x);
            }
        }
        vector<int> freq(100001,0);

        int left=0;
        int distinct=0;
        int ans=0;

        for(int right=0;right<n;right++){
            for(int p:factors[right]){
                if(freq[p]==0){
                    distinct++;
                }
                freq[p]++;
            }
            while(distinct>k){
                for(int p:factors[left]){
                    freq[p]--;
                    if(freq[p]==0){
                        distinct--;
                    }
                }
                left++;
            }
            ans=max(ans,(right-left+1));
        }
        return ans;
    }
};