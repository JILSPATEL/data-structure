/**
 * Problem: Find Median from Data Stream
 * ------------------------------------
 * Design a data structure that supports:
 * 1. addNum(int num)  -> adds a number
 * 2. findMedian()     -> returns median of current elements
 *
 * Approach 1: Two Heaps (Optimal) ✅
 * --------------------------------
 * - Max Heap (left): stores smaller half
 * - Min Heap (right): stores larger half
 *
 * Rules:
 * - Size difference should not exceed 1
 * - All elements in left <= elements in right
 *
 * Steps:
 * 1. Insert into appropriate heap
 * 2. Balance heaps
 * 3. Median:
 *    - If sizes equal → avg of tops
 *    - Else → top of left heap
 *
 * Time Complexity:
 * - addNum: O(log n)
 * - findMedian: O(1)
 *
 * Approach 2: Sorting (Brute Force)
 * --------------------------------
 * - Store all elements in array
 * - Sort every time → O(n log n)
 * - Inefficient for streaming
 */

#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
public:
    priority_queue<int> left; // Max Heap
    priority_queue<int, vector<int>, greater<int>> right; // Min Heap

    MedianFinder() {}

    void addNum(int num) {
        // Step 1: Insert into correct heap
        if (left.empty() || num <= left.top()) {
            left.push(num);
        } else {
            right.push(num);
        }

        // Step 2: Balance heaps
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        } else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian() {
        // Step 3: Return median
        if (left.size() == right.size()) {
            return (left.top() + right.top()) / 2.0;
        }
        return left.top();
    }
};

/**
 * Usage:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double median = obj->findMedian();
 */