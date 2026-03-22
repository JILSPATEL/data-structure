/**
 * Rotate Linked List (Left Rotation) using Circular Linked List Approach
 *
 * Problem:
 * Given a singly linked list, rotate it to the left by k nodes.
 *
 * Example:
 * Input:  10 → 20 → 30 → 40, k = 2
 * Output: 30 → 40 → 10 → 20
 *
 * ------------------------------------------------------------
 * APPROACHES:
 *
 * 1) Brute Force:
 *    - Rotate one node at a time, k times
 *    - Time: O(n * k) → inefficient
 *
 * 2) Better:
 *    - Find kth node, break and reconnect
 *    - Time: O(n)
 *
 * 3) Optimal (Used Here - Circular Linked List Trick):
 *    - Convert list into circular
 *    - Move to (k % len - 1) node
 *    - Break the circle
 *    - Time: O(n), Space: O(1)
 *
 * ------------------------------------------------------------
 */

class Solution {
public:
    Node* rotate(Node* head, int k) {

        // Edge case: empty list OR single node
        if (!head || !head->next)
            return head;

        // Step 1: Find length and last node
        int len = 1;
        Node* temp = head;

        while (temp->next) {
            temp = temp->next;
            len++;
        }

        // Step 2: Reduce k (important for large k)
        int r = k % len;

        // If no rotation needed
        if (r == 0)
            return head;

        // Step 3: Make list circular
        temp->next = head;

        // Step 4: Move to (r-1)th node
        temp = head;

        for (int i = 1; i < r; i++) {
            temp = temp->next;
        }

        // Step 5: Break the list
        head = temp->next;   // new head
        temp->next = nullptr; // break circular link

        return head;
    }
};