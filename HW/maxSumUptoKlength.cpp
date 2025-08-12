/*
Problem:
Given an array of integers and an integer k, find the maximum sum of any subarray 
whose length is less than or equal to k. The subarray must be contiguous.

Example:
Input:
k = 3
n = 6
array = [1, 4, 2, 10, 23, 3]

Output:
Maximum sum of subarray with length <= 3 is: 36

Complexity:
Time Complexity: O(n) — each element is added and removed at most once.
Space Complexity: O(n) for storing the array, O(1) extra space.
*/

#include <iostream>
#include <vector>
#include <climits> // For INT_MIN
using namespace std;

int main()
{
    int n, k;
    cout << "Enter K: ";
    cin >> k;
    cout << "Enter Number of elements: ";
    cin >> n;

    // Store the array elements
    vector<int> a(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // Edge case: empty array
    if (n == 0)
    {
        cout << "Empty Array!" << endl;
        return 0;
    }

    int maxSum = INT_MIN; // Stores the maximum sum found so far
    int sum = 0;          // Current window sum
    int start = 0;        // Left boundary of the sliding window

    // Traverse the array with 'end' as the right boundary of the window
    for (int end = 0; end < n; end++)
    {
        sum += a[end]; // Add current element to window sum

        // If window size exceeds k, shrink it from the left
        while (end - start + 1 > k)
        {
            sum -= a[start]; // Remove the leftmost element from sum
            start++;         // Move the window start forward
        }

        // Update the maximum sum for all windows of size ≤ k
        maxSum = max(maxSum, sum);
    }

    cout << "Maximum sum of subarray with length <= " << k << " is: " << maxSum << endl;
    return 0;
}
