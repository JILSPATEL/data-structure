class Solution {
  public:
    long long solve(vector<int> &arr,int mid){
        long long total=0;
        for(int i=0;i<arr.size();i++){
            total+=(long long)ceil((double)arr[i]/mid);
        }
        return total;
    }
    int kokoEat(vector<int>& arr, int k) {
        int low=1;
        int high=*max_element(arr.begin(),arr.end());
        int ans=0;
        int totalHrs=0;
        while(low<=high){
            int mid=(low+high)/2;
            int totalHrs=solve(arr,mid);
            if(totalHrs<=k){
                ans=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return ans;
        
    }
};