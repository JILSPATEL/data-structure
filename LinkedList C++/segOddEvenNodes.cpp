#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x){
        val=x;
        next=nullptr;
    }
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return head;

        ListNode *odd = head;
        ListNode *even = head->next;
        ListNode *even_start = head->next;

        while (odd->next && even->next) {
            odd->next = even->next;         // connect all odd nodes
            even->next = odd->next->next;   // connect all even nodes
            odd = odd->next;
            even = even->next;
        }

        odd->next = even_start; // connect last odd to start of even list
        return head;
    }
};

// Utility function to print linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    cout << "Enter elements to add to the linked list (-1 to stop):\n";
    int val;
    while (cin >> val && val != -1) {
        ListNode* newNode = new ListNode(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    Solution sol;
    ListNode* result = sol.oddEvenList(head);

    cout << "Linked list after rearranging odd-even:\n";
    printList(result);

    return 0;
}
