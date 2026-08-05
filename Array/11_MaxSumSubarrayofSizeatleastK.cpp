class Solution {
public:
    int maxSumWithK(vector<int>& arr, int k) {
        int n = arr.size();
        
        int currWinSum=0;
        for(int i=0;i<k;i++){
            currWinSum+=arr[i];
        }
        
        int maxi=currWinSum;
        int prevSubSum=0;
        
        for(int i=k;i<n;i++){
            currWinSum=currWinSum+arr[i]-arr[i-k];
            prevSubSum+=arr[i-k];
            if(prevSubSum<0){
                prevSubSum=0;
            }
            maxi=max(maxi,currWinSum+prevSubSum);
        }

        return maxi;
    }
};