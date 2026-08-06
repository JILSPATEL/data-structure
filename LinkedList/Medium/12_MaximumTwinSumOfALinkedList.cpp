/**
 * LeetCode 2130 - Maximum Twin Sum of a Linked List
 *
 * Approach 1: Find Middle + Reverse First Half
 * ---------------------------------------------
 * 1. Find the middle node using slow and fast pointers.
 * 2. Split the list into two halves.
 * 3. Reverse the first half.
 * 4. Traverse both halves together and compute twin sums.
 * 5. Return the maximum twin sum.
 *
 * Time Complexity : O(n)
 * Space Complexity: O(1)
 *
 * Example:
 * Input : 1 -> 2 -> 3 -> 4
 *
 * Step 1: Middle = 2
 * First Half  : 1 -> 2
 * Second Half : 3 -> 4
 *
 * Step 2: Reverse First Half
 * 2 -> 1
 *
 * Step 3: Twin Sums
 * (2 + 3) = 5
 * (1 + 4) = 5
 *
 * Output: 5
 */

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        return prev;
    }

    int pairSum(ListNode* head) {
        ListNode* middle = middleNode(head);

        ListNode* second = middle->next;
        middle->next = nullptr;

        ListNode* first = reverse(head);

        int ans = 0;

        while (first && second) {
            ans = max(ans, first->val + second->val);

            first = first->next;
            second = second->next;
        }

        return ans;
    }
};