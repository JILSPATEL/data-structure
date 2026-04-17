/**
 * Problem: Kth Largest Element in an Array
 * ----------------------------------------
 * Given an array, return the k-th largest element.
 *
 * Example:
 * Input: arr = [3, 2, 1, 5, 6, 4], k = 2
 * Output: 5
 *
 * --------------------------------------------------
 * Approaches:
 *
 * 1. Sorting Approach
 *    - Sort the array in descending order.
 *    - Return arr[k-1]
 *    - Time Complexity: O(n log n)
 *
 * 2. Min Heap Approach (Optimal for large n)
 *    - Maintain a min heap of size k.
 *    - First insert k elements.
 *    - For remaining elements:
 *         if current > heap.top(), replace top.
 *    - Final heap top = k-th largest.
 *    - Time Complexity: O(n log k)
 *    - Space Complexity: O(k)
 *
 * 3. Quickselect (Best Average Case)
 *    - Partition-based selection (like QuickSort).
 *    - Average: O(n), Worst: O(n^2)
 *
 * --------------------------------------------------
 * Chosen Approach: Min Heap
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int KthLargest(vector<int> &arr, int k) {
        int n = arr.size();

        // Min heap to store k largest elements
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Step 1: Insert first k elements
        for (int i = 0; i < k; i++) {
            minHeap.push(arr[i]);
        }

        // Step 2: Process remaining elements
        for (int i = k; i < n; i++) {
            if (arr[i] > minHeap.top()) {
                minHeap.pop();
                minHeap.push(arr[i]);
            }
        }

        // Step 3: Top of heap is kth largest
        return minHeap.top();
    }
};