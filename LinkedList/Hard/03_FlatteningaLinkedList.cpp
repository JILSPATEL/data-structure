/**
 * Problem: Flatten a Linked List (GFG)
 *
 * Each node has:
 * - next pointer → points to the next linked list
 * - bottom pointer → points to a sorted linked list
 *
 * Goal:
 * Flatten the entire structure into a single sorted linked list using ONLY bottom pointers.
 *
 * ------------------------------------------------------------
 * Approaches:
 *
 * 1. Recursive Merge (Current Approach)
 *    - Flatten the right side first
 *    - Merge current list with the flattened list
 *    - Similar to merging K sorted linked lists
 *
 * 2. Min Heap (Optimal Approach)
 *    - Insert heads of all lists into a min heap
 *    - Extract minimum and build result
 *    - Time: O(N log K)
 *
 * ------------------------------------------------------------
 * Key Observations:
 * - Always use 'bottom' pointer for final list
 * - Set 'next = NULL' after merging to avoid wrong links
 * - Works like merge sort on linked lists
 *
 * Time Complexity: O(N * K)
 * Space Complexity: O(K) (due to recursion stack)
 */

class Solution {
  public:
    Node* merge(Node* list1, Node* list2) {
        Node* dummy = new Node(-1);  // dummy node
        Node* res = dummy;
        while (list1 && list2) {
            if (list1->data < list2->data) {
                res->bottom = list1;
                res = list1;
                list1 = list1->bottom;
            } else {
                res->bottom = list2;
                res = list2;
                list2 = list2->bottom;
            }
            // Important: break next links
            res->next = nullptr;
        }
        // Attach remaining nodes
        if (list1) res->bottom = list1;
        else res->bottom = list2;

        return dummy->bottom;
    }

    Node *flatten(Node *root) {
        if (!root || !root->next) {
            return root;
        }
        Node* mergeHead = flatten(root->next);
        return merge(root, mergeHead);
    }
};