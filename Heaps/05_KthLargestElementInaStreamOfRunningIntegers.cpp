/**
 * Problem: Design a class to find the Kth largest element in a stream.
 * 
 * Approach 1 (Used - Min Heap):
 * - Maintain a min heap of size K
 * - Push every element into the heap
 * - If heap size exceeds K, remove the smallest element
 * - The top of the heap always represents the Kth largest element
 * 
 * Approach 2:
 * - Sort the array after each insertion (inefficient: O(n log n))
 * 
 * Time Complexity:
 * - Constructor: O(n log K)
 * - add(): O(log K)
 * 
 * Space Complexity:
 * - O(K)
 */

class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> pq;
    int K;

    // Constructor to initialize KthLargest object
    KthLargest(int k, vector<int>& nums) {
        K = k;

        // Build min heap with at most K largest elements
        for (int num : nums) {
            pq.push(num);
            if (pq.size() > K) {
                pq.pop();
            }
        }
    }
    
    // Add a new value and return the Kth largest element
    int add(int val) {
        pq.push(val);
        if (pq.size() > K) {
            pq.pop();
        }
        return pq.top();
    }
};