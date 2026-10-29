/**
 * Approach:
 * 1. Root is the current preorder element.
 * 2. Find its index in inorder using a hashmap.
 * 3. Recursively build left and right subtrees.
 *
 * Time Complexity : O(n)
 * Space Complexity: O(n)
 */
class Solution {
public:
    TreeNode* build(int& preIdx, int left, int right,
                    vector<int>& preorder,
                    unordered_map<int, int>& inPos) {

        if (left > right || preIdx >= preorder.size()) {
            return nullptr;
        }

        int val = preorder[preIdx++];
        int mid = inPos[val];

        TreeNode* root = new TreeNode(val);

        root->left = build(preIdx, left, mid - 1, preorder, inPos);
        root->right = build(preIdx, mid + 1, right, preorder, inPos);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inPos;

        for (int i = 0; i < inorder.size(); i++) {
            inPos[inorder[i]] = i;
        }

        int preIdx = 0;
        return build(preIdx, 0, inorder.size() - 1, preorder, inPos);
    }
};