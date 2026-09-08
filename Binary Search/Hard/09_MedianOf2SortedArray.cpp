//Better Approach
/*
Problem Description:
Given two sorted arrays, find the median of the values in their combined sorted order.
The median is the middle value when the total length is odd. When the total length is
even, it is the average of the two middle values.

Better Approach - Intuition:
Move values that are out of order between the two arrays, then sort both arrays again.
After that, the combined order can be viewed as nums1 followed by nums2 because every
value in nums1 is no greater than every value in nums2. The median indices can then be
located directly in these two arrays.

Example:
nums1 = [1, 4], nums2 = [2, 3]
After exchanging the misplaced boundary values and sorting, the arrays become
nums1 = [1, 2], nums2 = [3, 4]. The combined order is [1, 2, 3, 4], so the median is
(2 + 3) / 2 = 2.5.
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        int m=nums2.size();
        int i=n-1;
        int j=0;
        while(i>=0 && j<m){
            if(nums1[i]>nums2[j]){
                swap(nums1[i],nums2[j]);
                j++;
                i--;
            }else{
                i--;
            }
        }
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int total=n+m;
                if (total % 2 == 1) {
            int k = total / 2;

            if (k < n)
                return nums1[k];
            else
                return nums2[k - n];
        }
        int k1 = total / 2 - 1;
        int k2 = total / 2;

        int a, b;

        if (k1 < n)
            a = nums1[k1];
        else
            a = nums2[k1 - n];

        if (k2 < n)
            b = nums1[k2];
        else
            b = nums2[k2 - n];

        return (a + b) / 2.0;

    }
};


//Optimized Approach

/*
Optimized Approach - Intuition:
Imagine choosing a partition in each array so that the left parts together contain
half of all elements. The correct partition has every value on the left less than or
equal to every value on the right. We binary-search the partition in the smaller array;
the partition in the other array is determined by the required left-half size.

Approach:
1. Binary-search a partition px in nums1 and calculate py in nums2.
2. Let x1 and x2 be the largest values on the left, and x3 and x4 the smallest values
   on the right. Use INT_MIN and INT_MAX when a partition touches an array boundary.
3. If x1 <= x4 and x2 <= x3, the partition is correct. Return the largest left value
   for an odd total length, or the average of the largest left and smallest right values
   for an even total length.
4. If x1 > x4, move the nums1 partition left; otherwise move it right.

Example:
nums1 = [1, 3], nums2 = [2]
The total left-half size is 2. Choose px = 1 and py = 1:
left  = [1, 2], right = [3]. Since 1 <= 3 and 2 <= 3, the partition is valid.
The total length is odd, so the median is max(1, 2) = 2.

Time Complexity: O(log(min(n, m)))
Space Complexity: O(1)
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Always binary search on the smaller array
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int n = nums1.size();
        int m = nums2.size();

        int low = 0;
        int high = n;

        while (low <= high) {
            int px = low + (high - low) / 2;
            int py = (m + n + 1) / 2 - px;

            int x1 = (px == 0) ? INT_MIN : nums1[px - 1];
            int x3 = (px == n) ? INT_MAX : nums1[px];

            int x2 = (py == 0) ? INT_MIN : nums2[py - 1];
            int x4 = (py == m) ? INT_MAX : nums2[py];

            // Correct partition
            if (x1 <= x4 && x2 <= x3) {
                if ((m + n) % 2 == 0) {
                    return (max(x1, x2) + min(x3, x4)) / 2.0;
                }

                return max(x1, x2);
            }
            // Too many elements taken from nums1
            else if (x1 > x4) {
                high = px - 1;
            }
            // Too few elements taken from nums1
            else {
                low = px + 1;
            }
        }

        return -1;
    }
};