/**
 * Detect Loop in Linked List (Floyd’s Cycle Detection)
 * ------------------------------------------------------
 * Given the head of a linked list, check whether a loop (cycle) exists.
 *
 * Approach: Floyd’s Cycle Detection (Tortoise & Hare)
 *
 * - Use two pointers:
 *    1. slow → moves 1 step
 *    2. fast → moves 2 steps
 *
 * - If there is NO loop:
 *      fast will reach NULL
 *
 * - If there IS a loop:
 *      slow and fast will meet at some point
 *
 * ------------------------------------------------------
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
public:
    bool detectLoop(Node* head) {

        Node* slow = head;
        Node* fast = head;

        while (fast && fast->next) {
            slow = slow->next;           // move 1 step
            fast = fast->next->next;     // move 2 steps

            // Meeting point → loop exists
            if (slow == fast) {
                return true;
            }
        }

        //  No loop
        return false;
    }
};