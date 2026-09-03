/**
 * Problem: Remove K Consecutive Identical Characters
 *
 * Description:
 * Given a string `s` and an integer `k`, repeatedly remove every group of
 * exactly `k` consecutive identical characters. Continue removing groups until
 * no more such groups exist, then return the resulting string.
 *
 * Intuition:
 * While scanning from left to right, only the most recent group can be
 * extended by the current character. A stack can store each active group as a
 * character and its count. When the count reaches `k`, remove that group
 * immediately. This naturally handles new groups formed after a removal.
 *
 * Approach:
 * 1. Traverse the string character by character.
 * 2. If the current character matches the stack top, increment its count;
 *    otherwise, push a new group with count 1.
 * 3. Remove the top group whenever its count reaches `k`.
 * 4. Reconstruct the answer from the remaining groups in the stack.
 *
 * Example:
 * Input: s = "abbba", k = 3
 *
 * The group "bbb" is removed, leaving "aa". No group of three identical
 * characters remains, so the output is "aa".
 *
 * Time Complexity: O(n), where n is the length of the string
 * Space Complexity: O(n)
 */

class Solution {
public:
    string reducedString(int k, string &s) {
        if (k == 1) return "";

        stack<pair<char, int>> st;

        for (char ch : s) {
            if (st.empty()) {
                st.push({ch, 1});
            }
            else {
                if (ch == st.top().first) {
                    pair<char, int> p = st.top();
                    st.pop();

                    p.second++;

                    if (p.second < k) {
                        st.push(p);
                    }
                }
                else {
                    st.push({ch, 1});
                }
            }
        }

        string str;

        while (!st.empty()) {
            int count = st.top().second;

            while (count--) {
                str.push_back(st.top().first);
            }

            st.pop();
        }

        reverse(str.begin(), str.end());

        return str;
    }
};