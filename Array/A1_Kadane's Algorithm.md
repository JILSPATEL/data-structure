# Kadane’s Algorithm (Maximum Subarray Sum)

Kadane’s Algorithm is used to find the **maximum sum of a contiguous subarray**
in an array of integers.

---

## Problem Statement
Given an integer array `nums`, find the contiguous subarray (containing at least
one number) which has the **largest sum** and return its sum.

---

## Intuition
- At each index, decide:
  - Extend the previous subarray, or
  - Start a new subarray from current element
- If the current sum becomes negative, discard it
- The maximum sum seen so far is the answer

---

## Algorithm
1. Initialize:
   - `current_sum = nums[0]`
   - `max_sum = nums[0]`
2. Traverse the array from index `1`:
   - `current_sum = max(nums[i], current_sum + nums[i])`
   - `max_sum = max(max_sum, current_sum)`
3. Return `max_sum`

---

## Python Implementation
```python
class Solution(object):
    def maxSubArray(self, nums):
        current_sum = nums[0]
        max_sum = nums[0]

        for i in range(1, len(nums)):
            current_sum = max(nums[i], current_sum + nums[i])
            max_sum = max(max_sum, current_sum)

        return max_sum
