/**
 * Delete all occurrences of a given value X from a doubly linked list.
 *
 * 🔹 Intuition:
 * We traverse the list and remove nodes whose value == x.
 * Since it's a DOUBLY linked list, we must carefully update:
 *   - prev pointer of next node
 *   - next pointer of previous node
 *
 * 🔹 Key Idea:
 * - Always store next node BEFORE deleting current node
 * - Handle HEAD node separately (since it has no prev)
 *
 * ---------------------------------------------------------
 * 🔹 Step-by-Step Approach:
 *
 * 1. Start from head using a temp pointer.
 *
 * 2. For each node:
 *    → Store next node (important to continue traversal after deletion)
 *
 *    → If temp->data == x:
 *
 *        CASE 1: Node is HEAD
 *        --------------------------------
 *        temp->prev == NULL
 *        - Move head forward
 *        - Update new head's prev to NULL
 *
 *        CASE 2: Node is MIDDLE or LAST
 *        --------------------------------
 *        - Link previous node to next node
 *        - If next exists → update its prev pointer
 *
 *    → Delete current node
 *
 * 3. Move to nextNode
 *
 * ---------------------------------------------------------
 * 🔹 Time Complexity:  O(n)
 * 🔹 Space Complexity: O(1)
 *
 * ---------------------------------------------------------
 * 🔹 Edge Cases:
 * - Empty list
 * - All nodes contain x
 * - Only one node
 * - Head needs deletion multiple times
 *
 * ---------------------------------------------------------
 * 🔹 Interview Tip:
 * Always say:
 * "I store next pointer before deletion to avoid losing traversal."
 */

class Solution {
public:
    void deleteAllOccurOfX(struct Node** head_ref, int x) {
        
        // Edge case: empty list
        if (*head_ref == NULL) return;

        Node* temp = *head_ref;

        while (temp != NULL) {

            // Save next node BEFORE deletion
            Node* nextNode = temp->next;

            if (temp->data == x) {

                // CASE 1: Node is head
                if (temp->prev == NULL) {
                    *head_ref = temp->next;

                    if (*head_ref != NULL) {
                        (*head_ref)->prev = NULL;
                    }
                }
                // CASE 2: Node is middle or last
                else {
                    temp->prev->next = temp->next;

                    if (temp->next != NULL) {
                        temp->next->prev = temp->prev;
                    }
                }

                // Free memory
                delete temp;
            }

            // Move forward
            temp = nextNode;
        }
    }
};