class Solution {
public:
    typedef long long ll;
    bool isPos(vector<int> &ranks,ll mid,int cars){
        ll carFixed=0;
        for(int i=0;i<ranks.size();i++){
            carFixed+=sqrt(mid/ranks[i]);
        }
        return carFixed>=cars;
    }
    long long repairCars(vector<int>& ranks, int cars) {
        int n=ranks.size();
        ll l=0;
        int intR=*max_element(begin(ranks),end(ranks));
        ll r= 1LL*intR*cars*cars;
        ll res=-1;
        while(l<=r){
            ll mid=l+(r-l)/2;
            if(isPos(ranks,mid,cars)){
                res=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        return res;
    }
};