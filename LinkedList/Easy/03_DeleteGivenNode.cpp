/**
 * Problem: Delete Node in a Linked List (LeetCode 237)
 *
 * Description:
 * You are given a pointer to a node in a singly linked list.
 * The node is NOT the tail node, and you don't have access to the head.
 * Delete this node from the linked list.
 *
 * Intuition:
 * Since we don't have access to the previous node,
 * we cannot remove the current node in the usual way.
 *
 * So instead:
 * - Copy the value of the next node into the current node
 * - Bypass (skip) the next node
 *
 * Approach:
 * 1. Assign node->val = node->next->val
 * 2. Update node->next = node->next->next
 *
 * Why it works:
 * The current node now holds the next node’s value,
 * and the original next node is removed from the chain.
 *
 * Edge Case:
 * - This will NOT work if the given node is the last node
 *   (because node->next will be NULL)
 *
 * Possible Approaches:
 * 1. Optimal (Used here) → Copy next node data and skip it
 * 2. Traditional deletion → Not possible (no access to previous node)
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};