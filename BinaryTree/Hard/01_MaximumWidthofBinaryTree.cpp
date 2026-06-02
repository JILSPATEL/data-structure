/**
 * LeetCode 662 - Maximum Width of Binary Tree
 *
 * Approach:
 * 1. Use Level Order Traversal (BFS).
 * 2. Assign indices to nodes as if the tree were stored in an array:
 *      Left Child  = 2 * index + 1
 *      Right Child = 2 * index + 2
 * 3. For each level, normalize indices by subtracting the minimum index
 *    of that level to avoid overflow.
 * 4. Width of a level = last_index - first_index + 1.
 * 5. Track the maximum width across all levels.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) {
            return 0;
        }

        unsigned long long maxWidth = 0;

        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 0});

        while (!q.empty()) {
            int size = q.size();

            unsigned long long minIndex = q.front().second;
            unsigned long long first = 0;
            unsigned long long last = 0;

            for (int i = 0; i < size; i++) {
                auto [node, idx] = q.front();
                q.pop();

                unsigned long long currIndex = idx - minIndex;

                if (i == 0) {
                    first = currIndex;
                }

                if (i == size - 1) {
                    last = currIndex;
                }

                if (node->left) {
                    q.push({node->left, 2 * currIndex + 1});
                }

                if (node->right) {
                    q.push({node->right, 2 * currIndex + 2});
                }
            }

            maxWidth = max(maxWidth, last - first + 1);
        }

        return static_cast<int>(maxWidth);
    }
};