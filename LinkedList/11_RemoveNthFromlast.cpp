/**
 * Problem: Remove N-th Node From End of Linked List
 * ------------------------------------------------
 * Given the head of a linked list, remove the n-th node from the end
 * and return its head.
 *
 * Example:
 * Input:  1 -> 2 -> 3 -> 4 -> 5, n = 2
 * Output: 1 -> 2 -> 3 -> 5
 *
 * Approaches:
 * 1) Length-Based (Two Pass)
 *    - First pass: calculate length of list
 *    - Find position from start: pos = len - n + 1
 *    - Traverse again to (pos-1) node and delete target
 *    - Handle head deletion separately
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head) return nullptr;

        int len = 0;
        ListNode* temp = head;

        // Step 1: find length
        while(temp){
            len++;
            temp = temp->next;
        }

        int pos = len - n + 1;

        // Step 2: delete head
        if(pos == 1){
            return head->next;
        }

        // Step 3: reach (pos-1)
        temp = head;
        for(int i = 1; i < pos - 1; i++){
            temp = temp->next;
        }

        // Step 4: delete node
        ListNode* delNode = temp->next;
        temp->next = delNode->next;

        return head;
    }
};



/**
 * Problem: Remove N-th Node From End of Linked List
 * ------------------------------------------------
 * Given the head of a linked list, remove the n-th node from the end
 * and return its head.
 *
 * Example:
 * Input:  1 -> 2 -> 3 -> 4 -> 5, n = 2
 * Output: 1 -> 2 -> 3 -> 5
 *
 * Approaches:
 * 1) Two-Pointer (Fast & Slow) - Optimal
 *    - Move fast pointer n steps ahead
 *    - Move both fast and slow until fast reaches end
 *    - Slow will be just before the node to delete
 *    - Handle head deletion when fast becomes NULL
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode* slow = head;

        // move fast n steps ahead
        for(int i = 0; i < n; i++){
            fast = fast->next;
        }

        // if fast is NULL → delete head
        if(!fast){
            return head->next;
        }

        // move both pointers
        while(fast->next){
            fast = fast->next;
            slow = slow->next;
        }

        // delete node
        slow->next = slow->next->next;

        return head;
    }
};