/**
 * Remove duplicates from a SORTED doubly linked list.
 *
 * 🔹 Key Idea:
 * Since the list is sorted, duplicates will be adjacent.
 * So we only need to compare current node with next node.
 *
 * 🔹 Approach:
 * 1. Traverse using temp pointer
 * 2. If temp->data == temp->next->data:
 *      - Remove temp->next node
 *      - Fix links:
 *          temp->next = dup->next
 *          if dup->next exists → update its prev
 * 3. Else move temp forward
 *
 * ---------------------------------------------------------
 * 🔹 Time Complexity: O(n)
 * 🔹 Space Complexity: O(1)
 *
 * ---------------------------------------------------------
 * 🔹 Edge Cases:
 * - Empty list
 * - Single node
 * - All nodes same
 */

class Solution {
public:
    Node *removeDuplicates(struct Node *head) {

        // Edge case
        if (!head || !head->next) {
            return head;
        }

        Node* temp = head;

        while (temp != NULL && temp->next != NULL) {

            // Duplicate found
            if (temp->data == temp->next->data) {

                Node* dup = temp->next;

                // Remove duplicate node
                temp->next = dup->next;

                // Fix prev pointer if exists
                if (dup->next != NULL) {
                    dup->next->prev = temp;
                }

                delete dup;
            }
            else {
                // Move forward only if no deletion
                temp = temp->next;
            }
        }

        return head;
    }
};