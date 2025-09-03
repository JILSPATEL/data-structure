class Solution {
public:

    vector<int> leftSmaller(vector<int> a){
        int n=a.size();
        
        stack<pair<int,int>> st;
        vector<int> smaller(n,-1);
        for(int i=0;i<n;i++){
            while(st.size()>0 && st.top().first >= a[i]) st.pop();
            
            if(st.size() > 0) smaller[i]=st.top().second;
            
            st.push({a[i],i});
        }
        
        return smaller;
    }
    
    vector<int> rightSmaller(vector<int> a){
        int n=a.size();
        
        stack<pair<int,int>> st;
        vector<int> smaller(n,n);
        for(int i=n-1;i>=0;i--){
            while(st.size()>0 && st.top().first >= a[i]) st.pop();
            
            if(st.size() > 0) smaller[i]=st.top().second;
            
            st.push({a[i],i});
        }
        
        return smaller;
    }
    
    long long maximumSumOfHeights(vector<int>& a) {
        int n=a.size();
        
        vector<int> left = leftSmaller(a);
        
        vector<long long int> leftSum(n,0);
        for(int i=0;i<n;i++){
            int prevSmaller = left[i];
            
            leftSum[i] = (i-prevSmaller)*(long long)a[i];
            if(prevSmaller != -1) leftSum[i] += leftSum[prevSmaller];
        }
        
        vector<int> right = rightSmaller(a);
        vector<long long int> rightSum(n,0);
        for(int i=n-1;i>=0;i--){
            int nextSmaller = right[i];
            
            rightSum[i] = (nextSmaller-i)*(long long)a[i];
            if(nextSmaller != n) rightSum[i] += rightSum[nextSmaller];
        }
        
        long long int ans=0;
        for(int i=0;i<n;i++){
            long long int sum = leftSum[i]+rightSum[i]-a[i];
            if(sum > ans) ans=sum;
        }
        
        return ans;
    }
};
