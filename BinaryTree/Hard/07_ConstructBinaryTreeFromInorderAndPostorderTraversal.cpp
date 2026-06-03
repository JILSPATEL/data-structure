/**
 * LeetCode 106 - Construct Binary Tree from Inorder and Postorder Traversal
 *
 * Approach:
 * 1. The last element in postorder traversal is always the root node.
 * 2. Use a hashmap to store each value's index in inorder traversal.
 * 3. Find the root's position in inorder:
 *      - Elements on the left belong to the left subtree.
 *      - Elements on the right belong to the right subtree.
 * 4. Since we process postorder from the end:
 *
 *      Postorder : Left -> Right -> Root
 *      Reversed  : Root -> Right -> Left
 *
 *    Therefore, after creating the root, we must build the
 *    right subtree first and then the left subtree.
 * 5. Recursively construct the tree until the inorder range
 *    becomes invalid.
 *
 * Example:
 *
 *      inorder   = [9, 3, 15, 20, 7]
 *      postorder = [9, 15, 7, 20, 3]
 *
 *      Root = 3
 *
 *          3
 *         / \
 *        9   20
 *           /  \
 *          15   7
 *
 * Time Complexity : O(n)
 *      - Each node is processed exactly once.
 *      - HashMap lookup takes O(1).
 *
 * Space Complexity: O(n)
 *      - HashMap stores n entries.
 *      - Recursive stack can go up to O(n) in the worst case.
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
    TreeNode* build(
        int& postIdx,
        int start,
        int end,
        vector<int>& postorder,
        unordered_map<int, int>& inPos
    ) {
        // No nodes available in this inorder range
        if (start > end || postIdx < 0) {
            return nullptr;
        }

        // Current root from postorder
        int val = postorder[postIdx--];

        // Root position in inorder traversal
        int mid = inPos[val];

        TreeNode* root = new TreeNode(val);

        // Build right subtree first because
        // we are traversing postorder in reverse
        root->right = build(postIdx, mid + 1, end, postorder, inPos);

        // Build left subtree
        root->left = build(postIdx, start, mid - 1, postorder, inPos);

        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> inPos;

        // Store inorder value -> index mapping
        for (int i = 0; i < inorder.size(); i++) {
            inPos[inorder[i]] = i;
        }

        int postIdx = postorder.size() - 1;

        return build(postIdx, 0, inorder.size() - 1, postorder, inPos);
    }
};