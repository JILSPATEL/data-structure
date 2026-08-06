/**
 * Problem: Book Allocation
 * --------------------------------
 * You are given an array `arr` where each element represents the number of pages
 * in a book. You are also given `k` students.
 *
 * Rules:
 * 1. Each student must be assigned at least one book.
 * 2. Each book must be allocated to exactly one student.
 * 3. Books must be allocated in a contiguous manner.
 *
 * Task:
 *   Allocate books such that the maximum number of pages assigned to any student
 *   is minimized.
 *
 * If allocation is not possible, return -1.
 *
 * ----------------------------------------------------
 * Approach: Binary Search on Answer
 * ----------------------------------------------------
 *
 * Key Insight:
 * - The answer lies between:
 *     • max(arr)   → minimum possible maximum pages
 *     • sum(arr)   → maximum possible maximum pages
 *
 * We binary search on this range.
 *
 * ----------------------------------------------------
 * Feasibility Check (Greedy)
 * ----------------------------------------------------
 *
 * For a given page limit `pageLimit`, we try to assign books in order:
 * - Keep adding books to the current student until the limit is exceeded.
 * - If exceeded, assign books to a new student.
 *
 * The function `solve()` returns how many students are required if no student
 * is allowed to have more than `pageLimit` pages.
 *
 * ----------------------------------------------------
 * Binary Search Logic
 * ----------------------------------------------------
 *
 * - If required students > k:
 *     → pageLimit is too small → increase `low`
 *
 * - Else:
 *     → allocation possible → try smaller page limit
 *
 * ----------------------------------------------------
 * Final Result
 * ----------------------------------------------------
 *
 * The smallest feasible page limit is the answer.
 *
 * Time Complexity:
 *   O(n log(sum - max))
 *
 * Space Complexity:
 *   O(1)
 */

class Solution {
public:
    // Returns number of students required if max pages per student = pageLimit
    int solve(vector<int> &arr, int pageLimit) {
        int student = 1;
        int pageCount = 0;

        for (int i = 0; i < arr.size(); i++) {
            if (pageCount + arr[i] <= pageLimit) {
                pageCount += arr[i];
            } else {
                student++;
                pageCount = arr[i];
            }
        }

        return student;
    }

    int findPages(vector<int> &arr, int k) {
        int n = arr.size();

        // Not enough books for students
        if (n < k) {
            return -1;
        }

        int low  = *max_element(arr.begin(), arr.end());
        int high = accumulate(arr.begin(), arr.end(), 0);

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (solve(arr, mid) > k) {
                low = mid + 1;   // Need more capacity
            } else {
                high = mid - 1;  // Try smaller max
            }
        }

        return low;
    }
};
