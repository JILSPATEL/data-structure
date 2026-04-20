/**
 * Problem: Valid Parenthesis String
 * ---------------------------------
 * Given a string s containing '(', ')' and '*', return true if it is valid.
 * '*' can act as '(', ')' or an empty string.
 *
 * Approach:
 * ----------
 * We use a greedy range approach:
 *
 * - minOpen → minimum possible open brackets
 * - maxOpen → maximum possible open brackets
 *
 * For each character:
 *   '('  → min++, max++
 *   ')'  → min--, max--
 *   '*'  → min-- (treat as ')'), max++ (treat as '(')
 *
 * Key Observations:
 * - If maxOpen < 0 → too many ')' → invalid
 * - If minOpen < 0 → reset to 0 (cannot go negative)
 *
 * Final check:
 * - If minOpen == 0 → valid
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * Other Approaches:
 * -----------------
 * 1. Recursion (Exponential) → Try all possibilities of '*'
 * 2. DP (O(n^2)) → Store validity of substrings
 * 3. Stack-based → Track positions of '(' and '*'
 * 4. Greedy (Current Optimal Solution)
 */

class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();
        int minOpen = 0;
        int maxOpen = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                minOpen++;
                maxOpen++;
            } 
            else if (s[i] == ')') {
                minOpen--;
                maxOpen--;
            } 
            else { // '*'
                minOpen--;   // treat as ')'
                maxOpen++;   // treat as '('
            }

            if (maxOpen < 0) return false;

            if (minOpen < 0) minOpen = 0;
        }

        return (minOpen == 0);
    }
};