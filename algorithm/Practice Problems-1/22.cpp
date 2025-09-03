/*
Given n, radius of a circle with (0, 0) as center, write a linear time
algorithm to compute the number of lattice (integer) points inside the
circle.a
*/
#include <bits/stdc++.h>
using namespace std;

int checkPoints(int n){
    long long r=1LL*n*n;
    int count=0;
    for (int x = 0; x <= n; x++)
    {
        int y=floor(sqrt(r-1LL*x*x));
        count+=(2*y+1);
    }
    return 2*count-(2*n+1);
}

int main(){
    int n;
    cout<<"Enter the radius: ";
    cin>>n;
    int ans = checkPoints(n);
    cout<<"Total lattice Points: "<<ans;
    return 0;
}