class Solution {
  public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        deque<int>dq;
        vector<int> res;
        int n=arr.size();
        for(int i=0;i<n;i++){
            if(!dq.empty() && dq[0]==i-k){
                dq.pop_front();
            }
            while(!dq.empty() && arr[dq.back()]<=arr[i]){
                dq.pop_back();
            }
            dq.push_back(i);
            if(i>=k-1){
                res.push_back(arr[dq.front()]);
            }
        }
        return res;
    }
};

   