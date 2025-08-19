/*
Problem: Reverse Pairs

Given an array `arr[]` of integers, find the number of reverse pairs.
A reverse pair is defined as a pair of indices (i, j) such that:

    0 <= i < j < n  and  arr[i] > 2 * arr[j]
------------------------------------------------
Input:
- First line contains an integer n (size of the array).
- Second line contains n space-separated integers representing the array.

Output:
- Print the total number of reverse pairs.

------------------------------------------------
Example 1:
Input:
5
2 4 3 5 1
Output:
3

Explanation:
The reverse pairs are: (2,5), (3,5), (4,5) → values (4,1), (3,1), (5,1).
*/

#include <bits/stdc++.h>
using namespace std;

int merge(vector<int> &arr, int low, int mid, int high)
{
    int cnt = 0;

    int j = mid + 1;
    for (int i = low; i <= mid; i++)
    {
        while (j <= high && (long long)arr[i] > 2LL * arr[j])
        {
            j++;
        }
        cnt += (j - (mid + 1));
    }
    vector<int> temp;
    int left = low, right = mid + 1;

    while (left <= mid && right <= high)
    {
        if (arr[left] <= arr[right])
        {
            temp.push_back(arr[left++]);
        }
        else
        {
            temp.push_back(arr[right++]);
        }
    }
    while (left <= mid)
        temp.push_back(arr[left++]);
    while (right <= high)
        temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++)
    {
        arr[i] = temp[i - low];
    }

    return cnt;
}

int mergeSort(vector<int> &arr, int low, int high)
{
    int cnt = 0;
    if (low >= high)
        return cnt;
    int mid = (low + high) / 2;
    cnt += mergeSort(arr, low, mid);
    cnt += mergeSort(arr, mid + 1, high);
    cnt += merge(arr, low, mid, high);
    return cnt;
}

int countRevPairs(vector<int> &arr)
{
    return mergeSort(arr, 0, arr.size() - 1);
}

int main()
{
    int n;
    cout << "Enter how many numbers you want to insert:";
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << countRevPairs(arr) << endl;
    return 0;
}