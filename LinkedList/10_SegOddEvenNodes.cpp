/**
 * Problem: Rearrange Linked List (Odd-Even by Position)
 * ----------------------------------------------------
 * Given a singly linked list, group all nodes positioned at odd indices
 * together followed by nodes at even indices.
 * (1-based indexing: 1st node is odd, 2nd is even, etc.)
 *
 * Example:
 * Input:  1 -> 2 -> 3 -> 4 -> 5
 * Output: 1 -> 3 -> 5 -> 2 -> 4
 *
 * Approaches:
 * 1) In-place pointer manipulation (Optimal)
 *    - Maintain two pointers: odd and even
 *    - Keep track of even start
 *    - Rearrange links without extra space
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next) return head;

        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* even_start = even;

        while(odd->next && even->next){
            odd->next = even->next;
            odd = odd->next;

            even->next = odd->next;
            even = even->next;
        }

        odd->next = even_start;

        return head;
    }
};



/**
 * Problem: Divide Linked List into Even and Odd Values
 * ----------------------------------------------------
 * Given a linked list, rearrange it such that all even-valued nodes
 * come first, followed by all odd-valued nodes.
 *
 * Example:
 * Input:  1 -> 2 -> 3 -> 4 -> 5
 * Output: 2 -> 4 -> 1 -> 3 -> 5
 *
 * Approaches:
 * 1) Two separate lists (Optimal & Safe)
 *    - Maintain evenHead/evenTail and oddHead/oddTail
 *    - Traverse list and split nodes
 *    - Break original links to avoid cycles
 *    - Join even list with odd list
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

class Solution {
  public:
    Node* divide(Node* head) {
        if(!head || !head->next) return head;

        Node* oddHead = NULL;
        Node* oddTail = NULL;
        Node* evenHead = NULL;
        Node* evenTail = NULL;

        Node* curr = head;

        while(curr){
            Node* nextNode = curr->next;
            curr->next = NULL;  // break link

            if(curr->data % 2 == 0){
                if(!evenHead){
                    evenHead = evenTail = curr;
                } else {
                    evenTail->next = curr;
                    evenTail = curr;
                }
            } else {
                if(!oddHead){
                    oddHead = oddTail = curr;
                } else {
                    oddTail->next = curr;
                    oddTail = curr;
                }
            }

            curr = nextNode;
        }

        // connect even list to odd list
        if(evenTail) evenTail->next = oddHead;

        return evenHead ? evenHead : oddHead;
    }
};