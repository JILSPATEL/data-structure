class Solution {
public:
    int trap(vector<int>& arr) {
        int lm=0,rm=0;
        int l=0,r=arr.size()-1;
        int total=0;
        while(l<r){
            if(arr[l]<=arr[r]){
                if(lm>arr[l]){
                    total+=lm-arr[l];
                }
                else{
                    lm=arr[l];
                }
                l++;
            }
            else{
                if(rm>arr[r]){
                    total+=rm-arr[r];
                }
                else{
                    rm=arr[r];
                }
                r--;
            }
        }
        return total;

    }
};