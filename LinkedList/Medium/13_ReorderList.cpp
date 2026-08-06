/*
Problem Description:
Given the head of a singly linked list, reorder it in-place so the node order becomes:
L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...

Intuition:
The list can be split into two halves. If we reverse the second half, then we can merge
the first half and the reversed second half by taking one node from each alternately.
That gives the required zig-zag order without using extra space.

Approach:
1. Find the middle of the list using slow and fast pointers.
2. Split the list into two parts and reverse the second half.
3. Merge the two halves by alternating nodes from each list.
4. Keep the operation in-place by only changing next pointers.

Example:
Input:  1 -> 2 -> 3 -> 4 -> 5
Middle split: 1 -> 2 -> 3  and  4 -> 5
Reverse second half: 5 -> 4
Merge alternately: 1 -> 5 -> 2 -> 4 -> 3
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head || !head->next) return;

        ListNode* slow=head;
        ListNode* fast=head;

        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode* secondHead=slow->next;
        slow->next=nullptr;

        ListNode* prev=nullptr;

        while(secondHead){
            ListNode* next=secondHead->next;
            secondHead->next=prev;
            prev=secondHead;
            secondHead=next;
        }

        secondHead=prev;
        ListNode* firstNode=head;

        while(secondHead){
            ListNode* temp1=firstNode->next;
            ListNode* temp2=secondHead->next;
            firstNode->next=secondHead;
            secondHead->next=temp1;
            firstNode=temp1;
            secondHead=temp2;
        }
    }
};