class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        int n = n1 + n2;
        int i = 0, j = 0, cnt = 0;
        int ind1 = (n - 1) / 2;
        int ind2 = n / 2;
        int med1 = 0, med2 = 0;

        while (i < n1 || j < n2) {
            int val;
            if (i < n1 && (j >= n2 || nums1[i] <= nums2[j])) {
                val = nums1[i++];
            } else {
                val = nums2[j++];
            }

            if (cnt == ind1) med1 = val;
            if (cnt == ind2) {
                med2 = val;
                break;
            }

            cnt++;
        }

        if (n % 2 == 0)
            return (med1 + med2) / 2.0;
        else
            return med2;
    }
};

