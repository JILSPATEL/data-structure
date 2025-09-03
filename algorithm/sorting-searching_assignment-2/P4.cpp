class Solution {
public:
    long long sumOfFirst(long long k) {
        return k * (k + 1) / 2;
    }
    
    long long calc(int n,int index,int x){
        long long total=x;
        int leftCount=index;
        if(x-1>=leftCount){
            total+=sumOfFirst(x-1)-sumOfFirst(x-1-leftCount);
        }
        else{
            total+=sumOfFirst(x-1)+(leftCount-(x-1));
        }

        int rightCount = n - index - 1;
        if (x - 1 >= rightCount) {
            total += sumOfFirst(x - 1) - sumOfFirst(x - 1 - rightCount);
        } else {
            total += sumOfFirst(x - 1) + (rightCount - (x - 1));
        }

        return total;
    }
    int maxValue(int n, int index, int maxSum) {
        int low = 1, high = maxSum, ans = 1;

        while(low<=high){
            int mid=low+(high-low)/2;
            if(calc(n,index,mid)<=maxSum){
                ans=mid;
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
        return ans;
    }
};
