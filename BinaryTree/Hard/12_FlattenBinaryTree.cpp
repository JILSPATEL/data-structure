/**
 * Flatten Binary Tree to Linked List
 *
 * Approach:
 * 1. Store preorder traversal in a queue.
 * 2. Reconnect nodes sequentially.
 *
 * Time Complexity : O(N)
 * Space Complexity: O(N)
 */

class Solution {
public:
    queue<TreeNode*> preorderNodes;

    void preorder(TreeNode* root) {
        if (!root) {
            return;
        }

        preorderNodes.push(root);

        preorder(root->left);
        preorder(root->right);
    }

    void flatten(TreeNode* root) {

        if (!root) {
            return;
        }

        preorder(root);

        TreeNode* current = preorderNodes.front();
        preorderNodes.pop();

        while (!preorderNodes.empty()) {

            current->left = nullptr;
            current->right = preorderNodes.front();

            preorderNodes.pop();
            current = current->right;
        }

        current->left = nullptr;
        current->right = nullptr;
    }
};