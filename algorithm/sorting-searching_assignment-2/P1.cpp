class Solution {
public:
    int findFirst(vector<int>& arr,int n,int x){
        int low=0;
        int high=n-1;
        int first=-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]==x){
                first=mid;
                high=mid-1;
            }
            else if(arr[mid]<x){
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
        return first;
    }
    int findLast(vector<int>& arr,int n,int x){
        int low=0;
        int high=n-1;
        int last=-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]==x){
                last=mid;
                low=mid+1;
            }
            else if(arr[mid]>x){
                high=mid-1;
            }
            else{
                low=mid+1;;
            }
        }
        return last;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int n=nums.size();
        int first=findFirst(nums,n,target);
        int last=findLast(nums,n,target);
        return {first,last};
    }
};
