class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
      vector<int>dup;

      for(int i=0;i<nums.size();i++){
        int idx=abs(nums[i])-1;
        if(nums[idx]<0){
            dup.push_back(abs(nums[i]));
        }
        else{
            nums[idx]=-nums[idx];
        }
      }  
      return dup;
    }
};
