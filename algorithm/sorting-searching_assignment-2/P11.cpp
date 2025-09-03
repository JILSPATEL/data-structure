class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n=intervals.size();
        if(n == 0) return {};
        
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for(int i=1;i<n;i++){
            vector<int>& prev_end=res.back();
            if(prev_end[1]>=intervals[i][0]){
                prev_end[1]=max(prev_end[1],intervals[i][1]);
            }
            else{
                res.push_back(intervals[i]);
            }
        }
        return res;
    }
};
