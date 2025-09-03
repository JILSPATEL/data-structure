/*
Given an array of sorted integers and an integer X > 0 , design a linear
time algorithm to count the number of pair elements in the array such
that A[j] − A[i] > X
*/
#include <bits/stdc++.h>
using namespace std;
int check(vector<int> arr,int t){
    int n=arr.size();
    int j=0;
    int count=0;
    for (int i=0;i<n;i++){
        while(j<n && arr[j]-arr[i]<=t){
            j++;
        }
        if(j<n){
            count+=(n-j);
        }
    }
    return count;
    
}
int main(){
    int t,n;
    cin>>n;
    cin>>t;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int ans=check(arr,t);
    cout<<ans;
    return 0;
}