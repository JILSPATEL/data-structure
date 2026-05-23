/**
 * Problem: Alien Dictionary (Find character order from sorted words)
 *
 * Description:
 * Given a sorted dictionary of an alien language, determine the order
 * of characters in that language using Topological Sort (Kahn's Algorithm).
 *
 * Approach 1: Kahn's Algorithm (BFS Topological Sort) [Used]
 * 1. Collect all unique characters.
 * 2. Compare adjacent words:
 *      - Find first differing character.
 *      - Create directed edge:
 *            s1[i] -> s2[i]
 *      - Increase indegree of s2[i].
 * 3. Handle invalid case:
 *      - If s1 is longer and s2 is its prefix,
 *        return "".
 * 4. Push all nodes with indegree = 0 into queue.
 * 5. Perform BFS topological sorting.
 * 6. If result length != total unique characters,
 *    cycle exists → return "".
 *
 * Time Complexity:
 * O(N*L + K + E)
 * N = number of words
 * L = average word length
 * K = unique characters
 * E = edges
 *
 * Space Complexity:
 * O(K + E)
 */

class Solution {
public:
    string findOrder(vector<string>& words) {
        int n = words.size();

        // Store unique characters
        unordered_set<char> st;
        for (auto &w : words) {
            for (char c : w) {
                st.insert(c);
            }
        }

        int k = st.size();

        vector<vector<int>> graph(26);
        vector<int> inDeg(26, 0);

        // Build graph
        for (int i = 0; i < n - 1; i++) {
            string s1 = words[i];
            string s2 = words[i + 1];

            int len = min(s1.size(), s2.size());
            bool found = false; // Must reset for every pair

            for (int j = 0; j < len; j++) {
                if (s1[j] != s2[j]) {

                    // Avoid duplicate edge
                    bool exists = false;

                    for (int x : graph[s1[j] - 'a']) {
                        if (x == s2[j] - 'a') {
                            exists = true;
                            break;
                        }
                    }

                    if (!exists) {
                        graph[s1[j] - 'a'].push_back(s2[j] - 'a');
                        inDeg[s2[j] - 'a']++;
                    }

                    found = true;
                    break;
                }
            }

            // Invalid case:
            // ["abcd","ab"]
            if (!found && s1.size() > s2.size()) {
                return "";
            }
        }

        // Kahn's Algorithm
        queue<int> q;

        for (char c : st) {
            if (inDeg[c - 'a'] == 0) {
                q.push(c - 'a');
            }
        }

        string ans = "";

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            ans += char(node + 'a');

            for (auto neigh : graph[node]) {
                inDeg[neigh]--;

                if (inDeg[neigh] == 0) {
                    q.push(neigh);
                }
            }
        }

        // Cycle exists
        if (ans.size() != k) {
            return "";
        }

        return ans;
    }
};