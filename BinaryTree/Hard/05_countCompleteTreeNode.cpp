/**
 * Problem: Count Complete Tree Nodes (Brute Force DFS)
 *
 * Description:
 * Given the root of a binary tree, return the total number of nodes present
 * in the tree. This solution performs a simple Depth First Search (DFS)
 * traversal and counts every node.
 *
 * Approaches:
 * 1. Recursive DFS Traversal (Implemented Below)
 *    - Visit each node once and increment the count.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(H) (Recursion Stack)
 *
 * 2. Iterative DFS/BFS
 *    - Use a stack or queue to traverse all nodes.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(N)
 *
 * 3. Complete Binary Tree Optimization
 *    - Compare left and right subtree heights.
 *    - Time Complexity: O((log N)^2)
 *    - Space Complexity: O(log N)
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right)
 *         : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    void solve(TreeNode* root, int& count) {
        if (!root) {
            return;
        }

        count++;

        solve(root->left, count);
        solve(root->right, count);
    }

    int countNodes(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int count = 0;
        solve(root, count);

        return count;
    }
};


/**
 * Problem: Count Complete Tree Nodes
 *
 * Description:
 * Given the root of a complete binary tree, return the number of nodes.
 *
 * Approaches:
 * 1. DFS Traversal
 *    - Traverse every node and count.
 *    - Time Complexity: O(N)
 *    - Space Complexity: O(H)
 *
 * 2. Complete Binary Tree Optimization (Implemented Below)
 *    - Compute leftmost and rightmost heights.
 *    - If both heights are equal, the tree is perfect:
 *          Nodes = 2^h - 1
 *    - Otherwise, recursively count nodes in left and right subtrees.
 *    - Time Complexity: O((log N)^2)
 *    - Space Complexity: O(log N)
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right)
 *         : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    int leftHeight(TreeNode* root) {
        int h = 0;

        while (root) {
            h++;
            root = root->left;
        }

        return h;
    }

    int rightHeight(TreeNode* root) {
        int h = 0;

        while (root) {
            h++;
            root = root->right;
        }

        return h;
    }

    int countNodes(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int lh = leftHeight(root);
        int rh = rightHeight(root);

        if (lh == rh) {
            return (1 << lh) - 1;
        }

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};