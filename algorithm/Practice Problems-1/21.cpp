/*
Given an array of integers , design an efficient algorithm to decide if
there is i, j, k, l such that A[i] − 2A[j] = A[k] − 3A[l].
*/

/*
lets a[i]-a[k]=2a[j]-3a[l]
*/
#include <bits/stdc++.h>
using namespace std;
bool check(vector<int> arr)
{
    unordered_set<int> lhs;

    for (int i = 0; i < arr.size(); i++)
    {
        for (int k = 0; k < arr.size(); k++)
        {
            if (i != k)
            {
                lhs.insert(arr[i] - arr[k]);
            }
        }
    }
    for (int j = 0; j < arr.size(); j++)
    {
        for (int l = 0; l < arr.size(); l++)
        {
            if (j != l)
            {
               if(lhs.find(2*arr[j]-3*arr[l])!=lhs.end()){
                return true;
               }
            }
        }
    }
    return false;

}
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    bool ans = check(arr);
    cout<< ans;
    return 0;
}