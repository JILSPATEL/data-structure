/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */

class Codec {
public:

    /**
     * Approach:
     * ---------
     * Use Level Order Traversal (BFS).
     *
     * For every node:
     * - Store its value.
     * - Store "N" for nullptr nodes.
     *
     * Example:
     *
     *         1
     *        / \
     *       2   3
     *          / \
     *         4   5
     *
     * Serialized:
     * "1,2,3,N,N,4,5,N,N,N,N,"
     *
     * Time Complexity : O(N)
     * Space Complexity: O(N)
     */

    string serialize(TreeNode* root) {

        if (!root) {
            return "";
        }

        string serializedData;

        queue<TreeNode*> bfsQueue;
        bfsQueue.push(root);

        while (!bfsQueue.empty()) {

            TreeNode* currentNode = bfsQueue.front();
            bfsQueue.pop();

            if (currentNode == nullptr) {
                serializedData += "N,";
                continue;
            }

            serializedData += to_string(currentNode->val) + ",";

            bfsQueue.push(currentNode->left);
            bfsQueue.push(currentNode->right);
        }

        return serializedData;
    }

    /**
     * Reconstruct tree from BFS sequence.
     *
     * Time Complexity : O(N)
     * Space Complexity: O(N)
     */
    TreeNode* deserialize(string data) {

        if (data.empty()) {
            return nullptr;
        }

        stringstream ss(data);
        string value;

        getline(ss, value, ',');

        TreeNode* root = new TreeNode(stoi(value));

        queue<TreeNode*> bfsQueue;
        bfsQueue.push(root);

        while (!bfsQueue.empty()) {

            TreeNode* currentNode = bfsQueue.front();
            bfsQueue.pop();

            // Left Child
            getline(ss, value, ',');

            if (value != "N") {
                currentNode->left = new TreeNode(stoi(value));
                bfsQueue.push(currentNode->left);
            }

            // Right Child
            getline(ss, value, ',');

            if (value != "N") {
                currentNode->right = new TreeNode(stoi(value));
                bfsQueue.push(currentNode->right);
            }
        }

        return root;
    }
};