/**
 * Problem: Delete the Middle Node of a Linked List
 * ------------------------------------------------
 * Given the head of a linked list, delete the middle node
 * and return the head of the modified list.
 *
 * Note:
 * - If the list has even length, delete the second middle node.
 *
 * Example:
 * Input:  1 -> 2 -> 3 -> 4 -> 5
 * Output: 1 -> 2 -> 4 -> 5
 *
 * Approaches:
 * 1) Slow-Fast Pointer (Optimal)
 *    - Use two pointers: slow (1 step), fast (2 steps)
 *    - Maintain a prev pointer to track node before slow
 *    - When fast reaches end, slow is at middle
 *    - Delete middle node using prev pointer
 *
 * 2) Dummy Node Variant (Safer)
 *    - Use a dummy node before head
 *    - Avoid explicit prev pointer handling
 *    - Helps simplify edge cases
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if(!head || !head->next) return nullptr;

        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;

        while(fast && fast->next){
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // delete middle node
        prev->next = slow->next;

        return head;
    }
};