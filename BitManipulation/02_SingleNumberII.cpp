/*
Problem Description:
Given an array in which every value appears exactly three times except one value that
appears once, find the value that appears only once.

Intuition:
Look at each bit position separately. Every number that appears three times contributes
that bit either zero times or three times, so its contribution disappears when the bit
count is taken modulo 3. The unique number contributes one extra occurrence for each
of its set bits. Those are the bits that remain in the answer.

Approach:
1. Visit all 32 bit positions of an integer.
2. Count how many numbers have a set bit at the current position.
3. If the count modulo 3 is 1, set that bit in the answer.
4. Return the reconstructed value.

Example:
For nums = [2, 2, 3, 2], the binary values are:
2 = 010, 2 = 010, 3 = 011, 2 = 010
At the rightmost bit, the set-count is 1, so that bit belongs to the answer. At the
next bit, the set-count is 4, and 4 % 3 = 1, so that bit also belongs to the answer.
The reconstructed result is 011, which is 3.

Time Complexity: O(32n), which is O(n)
Space Complexity: O(1)
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans=0;
        for(int i=0;i<32;i++){
            int cntZ=0;
            int cntO=0;
            for(int num:nums){
                if((num & (1<<i))==0){
                    cntZ++;
                }else{
                    cntO++;
                }
            }
            if(cntO%3==1){
                ans=(ans | (1<<i));
            }
        }
        return ans;
    }
};