class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int res=nums[0]+nums[1]+nums[2];
        int n=nums.size();
        for(int i=0;i<n-2;i++){
            int j=i+1;
            int k=n-1;
            while(j<k){
                int sum=nums[i]+nums[j]+nums[k];
                if(sum==target){
                    return sum;
                }
                if(abs(sum-target)<abs(res-target)){
                    res=sum;
                }
                if(sum<target){
                    j++;
                }
                else{
                    k--;
                }
            }
        }
        return res;
    }
};
               
