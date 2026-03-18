/**
 * Problem: Delete a node at position X in a Doubly Linked List
 * 
 * Description:
 * Given the head of a doubly linked list, delete the node at position x (1-based index)
 * and return the updated head.
 * 
 * Approaches:
 * 1. Traverse Approach (Optimal)
 *    - Handle edge case when x == 1 (delete head)
 *    - Traverse to the x-th node
 *    - Update prev and next pointers
 *    - Delete the node
 * 
 * 2. Dummy Node Approach (Alternative)
 *    - Use a dummy node before head to simplify edge cases
 *    - Not necessary but useful in complex variations
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

class Solution {
public:
    Node* delPos(Node* head, int x) {

        // Edge case: empty list
        if (!head) return NULL;

        Node* temp = head;

        // Case 1: Delete first node
        if (x == 1) {
            head = head->next;

            if (head != NULL) {
                head->prev = NULL;
            }

            delete temp;
            return head;
        }

        int cnt = 1;

        // Traverse to x-th node
        while (temp != NULL && cnt < x) {
            temp = temp->next;
            cnt++;
        }

        // If position is invalid
        if (temp == NULL) return head;

        // Case 2: Middle node
        if (temp->next != NULL) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        // Case 3: Last node
        else {
            temp->prev->next = NULL;
        }

        delete temp;
        return head;
    }
};