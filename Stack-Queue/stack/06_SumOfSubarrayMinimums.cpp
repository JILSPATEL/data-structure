class Solution {
public:
    vector<int> findNSE(vector<int> &nums){
        int n=nums.size();
        vector<int> nse(n,n);
        stack<int> st;
        for(int i=n-1;i>=0;i--){
            while(!st.empty() && nums[st.top()]>=nums[i]){
                st.pop();
            }
            if(!st.empty()){
                nse[i]=st.top();
            }
            st.push(i);
        }
        return nse;
    }
    vector<int> findPSE(vector<int> &nums){
        int n=nums.size();
        vector<int> pse(n,-1);
        stack<int>st;
        for(int i=0;i<n;i++){
            while(!st.empty() && nums[st.top()]>nums[i]){
                st.pop();
            }
            if(!st.empty()){
                pse[i]=st.top();
            }
            st.push(i);
        }
        return pse;
    }
    int sumSubarrayMins(vector<int>& arr) {
        vector<int> nse=findNSE(arr);
        vector<int> pse=findPSE(arr);
        int total=0;
        const int mod=1000000007;
        int n=arr.size();
        for(int i=0;i<n;i++){
            int left=i-pse[i];
            int right=nse[i]-i;
            total=(total+(right*left*1LL*arr[i])%mod)%mod;
        }
        return total;
    }
};