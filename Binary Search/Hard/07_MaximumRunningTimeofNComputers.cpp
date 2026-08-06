class Solution {
public:
    typedef long long ll;
    bool isValid(vector<int>& batteries,ll mid,int n){
        ll tar=mid*n;
        ll  sum=0;
        for(int i=0;i<batteries.size();i++){
            sum+=min((ll)batteries[i],mid);
            if(sum>=tar) return true;
        }
        return false;
    }
    long long maxRunTime(int n, vector<int>& batteries) {
        ll low=*min_element(batteries.begin(),batteries.end());
        ll totalMin=0;
        for(int i=0;i<batteries.size();i++){
            totalMin+=(ll)batteries[i];
        }
        ll high=totalMin/n;
        ll ans=-1;

        while(low<=high){
            ll mid=(low+high)/2;
            if(isValid(batteries,mid,n)){
                ans=mid;
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return ans;
    }
};