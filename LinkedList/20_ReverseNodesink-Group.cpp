/**
 * Problem: Reverse Nodes in k-Group
 *
 * Description:
 * Given a linked list, reverse nodes in groups of size k.
 * If remaining nodes are less than k, leave them unchanged.
 *
 * ------------------------------------------------------------
 * INTUITION (STEP-BY-STEP):
 *
 * We process the linked list in chunks of size k:
 *
 * 1. Start from current node (temp)
 * 2. Find kth node from temp
 *    - If not found → remaining nodes < k → stop
 *
 * 3. Store next group:
 *      nextNode = kthNode->next
 *
 * 4. Break the group:
 *      kthNode->next = NULL
 *
 *    Now current group is isolated
 *
 * 5. Reverse the group:
 *      reverse(temp)
 *
 *    After reverse:
 *      kthNode becomes new head of this group
 *      temp becomes last node
 *
 * 6. Connect with previous group:
 *    - If first group → update head
 *    - Else → prevLast->next = kthNode
 *
 * 7. Update prevLast:
 *      prevLast = temp
 *
 * 8. Move to next group:
 *      temp = nextNode
 *
 * Repeat until list ends.
 *
 * ------------------------------------------------------------
 * POINTER FLOW:
 *
 * Before:
 * prevLast → temp → ... → kthNode → nextNode
 *
 * After reverse:
 * prevLast → kthNode → ... → temp → nextNode
 *
 * ------------------------------------------------------------
 * TIME: O(N)
 * SPACE: O(1)
 *
 * ------------------------------------------------------------
 */

class Solution {
public:

    /**
     * Reverse a linked list
     *
     * Example:
     * 1 → 2 → 3 → NULL
     * becomes
     * 3 → 2 → 1 → NULL
     */
    ListNode* reverse(ListNode* head){
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while(curr){
            ListNode* nextNode = curr->next; // store next node
            curr->next = prev;               // reverse pointer
            prev = curr;                     // move prev
            curr = nextNode;                 // move curr
        }
        return prev;
    }

    /**
     * Find kth node from current node
     *
     * If nodes < k → return NULL
     */
    ListNode* findKthnode(ListNode* temp, int k){
        k -= 1;

        while(temp != nullptr && k > 0){
            temp = temp->next;
            k--;
        }
        return temp;
    }

    /**
     * Main Function: Reverse nodes in k-group
     */
    ListNode* reverseKGroup(ListNode* head, int k) {

        ListNode* temp = head;        // start of current group
        ListNode* prevLast = nullptr; // last node of previous group

        while(temp){

            // Step 1: Find kth node
            ListNode* kthNode = findKthnode(temp, k);

            // Step 2: If less than k nodes → stop
            if(!kthNode){
                if(prevLast){
                    prevLast->next = temp;
                }
                break;
            }

            // Step 3: Store next group
            ListNode* nextNode = kthNode->next;

            // Step 4: Break the list
            kthNode->next = nullptr;

            // Step 5: Reverse current group
            reverse(temp);

            // Step 6: Connect with previous group
            if(temp == head){
                head = kthNode; // first group
            } else {
                prevLast->next = kthNode;
            }

            // Step 7: Update prevLast
            prevLast = temp;

            // Step 8: Move to next group
            temp = nextNode;
        }

        return head;
    }
};