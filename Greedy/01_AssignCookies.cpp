/**
 * Problem: Assign Cookies (Leetcode)
 * 
 * Description:
 * You are given two integer arrays:
 *  - g[i]: greed factor of each child
 *  - s[j]: size of each cookie
 * 
 * Each child can be assigned at most one cookie.
 * A child is satisfied if s[j] >= g[i].
 * 
 * Goal:
 * Maximize the number of satisfied children.
 * 
 * Approach:
 * 1. Sort both arrays (greed factors and cookie sizes).
 * 2. Use two pointers:
 *    - i for children (greed array)
 *    - j for cookies
 * 3. If current cookie satisfies current child → move to next child.
 * 4. Always move cookie pointer forward.
 * 5. Count how many children got satisfied.
 * 
 * Time Complexity: O(n log n + m log m)
 * Space Complexity: O(1)
 * 
 * Alternate Approaches:
 * - Brute Force: Try all assignments → O(n * m)
 * - Binary Search (less common): Not optimal compared to greedy
 * 
 * Optimal Strategy:
 * Greedy (sorting + two pointers)
 */

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // Sort greed factors and cookie sizes
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int n = g.size();
        int m = s.size();

        int i = 0; // pointer for children
        int j = 0; // pointer for cookies

        // Try to satisfy children using available cookies
        while (i < n && j < m) {
            if (g[i] <= s[j]) {
                // Current cookie satisfies current child
                i++;
            }
            // Move to next cookie
            j++;
        }

        // Number of satisfied children
        return i;
    }
};