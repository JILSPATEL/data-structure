class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        long mod=(long)(pow(10,9)+7);
        long A=a,B=b;
        long left=min(a,b);
        long right=(long)n*min(a,b);

        while(B>0){
            long temp=A;
            A=B;
            B=temp%B;
        }

        long lcm=(a*b)/A;

        while(left<right){
            long mid=(left+right)/2;
            if((mid/a)+(mid/b)-(mid/lcm)<n) left=mid+1;
            else right=mid;
        }
        return (int)(left%mod);
    }
};
