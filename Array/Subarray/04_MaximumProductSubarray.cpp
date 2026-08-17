/*
Problem: Maximum Product Subarray

Description:
Given an integer array, find the maximum product of any non-empty subarray.
The product can be large because numbers may be negative, so we must track both
maximum and minimum product ending at the current position.

Approach:
1. Maintain currMax and currMin for the product of the subarray ending at i.
2. For each element, compute:
   - arr[i]
   - arr[i] * currMax
   - arr[i] * currMin
3. Update currMax as the maximum of these values.
4. Update currMin as the minimum of these values.
5. Track the global maximum product seen so far.

Why this works:
If the current number is negative, the largest product may come from the minimum
product ending before it because a negative times a negative becomes positive.

Example:
arr = [2, 3, -2, 4]
- Start: currMax = 2, currMin = 2, maxProd = 2
- At 3: currMax = 6, currMin = 2, maxProd = 6
- At -2: currMax = 6, currMin = -12, maxProd = 6
- At 4: currMax = 24, currMin = -48, maxProd = 24
Answer = 24
*/

//Approach-1
class Solution {
public:
    int maxProduct(vector<int>& arr) {
        int n=arr.size();
        if(n==1) return arr[0];
        int pref=1;
        int suffix=1;
        int maxi=INT_MIN;

        for(int i=0;i<n;i++){
            if(pref==0) pref=1;
            if(suffix==0) suffix=1;

            pref*=arr[i];
            suffix*=arr[n-i-1];
            maxi=max(maxi,max(pref,suffix));
        }
        return maxi;
    }
};

//Approach-2
class Solution {
public:
    int maxProduct(vector<int>& arr) {
        int n=arr.size();
        if(n==1) return arr[0];
        int currMin=arr[0];
        int currMax=arr[0];
        int maxProd=arr[0];

        for(int i=1;i<n;i++){
            int temp=max({arr[i],arr[i]*currMax,arr[i]*currMin});
            currMin=min({arr[i],arr[i]*currMax,arr[i]*currMin});
            currMax=temp;
            maxProd=max(maxProd,currMax);
        }
        return maxProd;
    }
};