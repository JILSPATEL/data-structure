/*
Problem:
Given an array of integers and an integer k, find the maximum sum of any k consecutive elements in the array.
If k is greater than the size of the array, output an error message.

Example:
Input:
n = 6
k = 3
array = [1, 4, 2, 10, 23, 3]

Output:
Maximum sum of 3 consecutive elements: 36

Complexity:
Time Complexity: O(n) – We traverse the array once using the sliding window approach.
Space Complexity: O(n) for storing the array, O(1) auxiliary space.

*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cout << "Enter size of k: ";
    cin >> k;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> a(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n < k) {
        cout << "Window size k is larger than array size!" << endl;
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += a[i];
    }
    int maxSum = sum;

    for (int end = k; end < n; end++) {
        sum += a[end] - a[end - k];  
        maxSum = max(maxSum, sum);
    }

    cout << "Maximum sum of " << k << " consecutive elements: " << maxSum << endl;
    return 0;
}
