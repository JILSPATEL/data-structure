/**
 * Problem: Lexicographically Smallest String After Correcting k
 *
 * Given:
 * - A string s consisting of lowercase English letters.
 * - An integer k.
 *
 * Before removing characters, k must be corrected:
 * 1. If the length of the string is a power of 2:
 *      k = k / 2
 * 2. Otherwise:
 *      k = k * 2
 *
 * After correction, remove exactly k characters from the string such that
 * the resulting string is lexicographically smallest possible.
 *
 * Return:
 * - The smallest possible string after removing exactly k characters.
 * - "-1" if removing k characters is impossible or the resulting string becomes empty.
 *
 * ------------------------------------------------------------------
 * Approach: Monotonic Increasing Stack (Greedy)
 * ------------------------------------------------------------------
 *
 * Observation:
 * To obtain the lexicographically smallest string, smaller characters
 * should appear as early as possible.
 *
 * While traversing the string:
 * - If the current character is smaller than the top of the stack,
 *   removing the larger character from the stack will make the result
 *   lexicographically smaller.
 * - We keep removing such larger characters as long as we still have
 *   removals available.
 *
 * Example:
 * s = "cbacd", k = 2
 *
 * Stack Process:
 * c -> [c]
 * b -> remove c, push b      => [b]
 * a -> remove b, push a      => [a]
 * c -> [a,c]
 * d -> [a,c,d]
 *
 * Result = "acd"
 *
 * After processing all characters:
 * If removals are still left, remove characters from the end because
 * removing later characters affects lexicographical order the least.
 *
 * ------------------------------------------------------------------
 * Power of 2 Check
 * ------------------------------------------------------------------
 *
 * A number n is a power of 2 if:
 *
 *      n & (n - 1) == 0
 *
 * Examples:
 * 8  -> 1000
 * 7  -> 0111
 * ----------------
 *      0000
 *
 * Hence 8 is a power of 2.
 *
 * ------------------------------------------------------------------
 * Complexity Analysis
 * ------------------------------------------------------------------
 *
 * Let n = length of string.
 *
 * Time Complexity  : O(n)
 *   - Each character is pushed once and popped at most once.
 *
 * Space Complexity : O(n)
 *   - Stack stores at most n characters.
 */
class Solution {
public:
    string lexicographicallySmallest(string &s, int k) {
        int stringLength = s.size();

        // Correct k according to the problem statement.
        if ((stringLength & (stringLength - 1)) == 0)
            k /= 2;
        else
            k *= 2;

        // If removing k characters is impossible
        // or the resulting string becomes empty.
        if (k >= stringLength)
            return "-1";

        stack<char> st;

        // Build lexicographically smallest sequence.
        for (char ch : s) {

            while (!st.empty() &&
                   k > 0 &&
                   st.top() > ch) {

                st.pop();
                k--;
            }

            st.push(ch);
        }

        // If removals are still left,
        // remove characters from the end.
        while (k > 0 && !st.empty()) {
            st.pop();
            k--;
        }

        string answer;

        while (!st.empty()) {
            answer += st.top();
            st.pop();
        }

        reverse(answer.begin(), answer.end());

        return answer;
    }
};