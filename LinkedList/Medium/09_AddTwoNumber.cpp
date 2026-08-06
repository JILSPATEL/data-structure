/**
 * Problem: Add Two Numbers (Linked List)
 *
 * Description:
 * Two non-empty linked lists represent two non-negative integers.
 * Digits are stored in reverse order.
 * Add the two numbers and return the sum as a linked list.
 *
 * Approaches:
 *
 * 1) Convert to number (Not recommended due to overflow)
 *
 * 2) Optimal (Used Here):
 *    - Traverse both lists
 *    - Add digits + carry
 *    - Create new node for each digit
 *    - Maintain tail pointer
 *    - Time: O(max(N, M)), Space: O(max(N, M))
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode* dummy = new ListNode(-1); // dummy node
        ListNode* tail = dummy;

        int carry = 0;

        while (l1 || l2 || carry) {
            int sum = carry;

            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;

            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }

        return dummy->next;
    }
};