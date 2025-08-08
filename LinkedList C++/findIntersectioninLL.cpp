#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int c1 = 0, c2 = 0;
        ListNode *ptr1 = headA;
        ListNode *ptr2 = headB;

        // Count length of list A
        while (ptr1 != nullptr) {
            c1++;
            ptr1 = ptr1->next;
        }

        // Count length of list B
        while (ptr2 != nullptr) {
            c2++;
            ptr2 = ptr2->next;
        }

        ptr1 = headA;
        ptr2 = headB;
        int diff = (c1 > c2) ? (c1 - c2) : (c2 - c1); // avoid abs()

        // Move the pointer of longer list ahead by diff
        if (c1 > c2) {
            for (int i = 0; i < diff; i++)
                ptr1 = ptr1->next;
        } else if (c1 < c2) {
            for (int i = 0; i < diff; i++)
                ptr2 = ptr2->next;
        }

        // Traverse together until intersection found
        while (ptr1 != nullptr && ptr2 != nullptr) {
            if (ptr1 == ptr2)
                return ptr1;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        return nullptr;
    }
};

// Helper to create and link nodes
ListNode* createNode(int val) {
    return new ListNode(val);
}

int main() {
    // Example: Creating two intersecting linked lists
    // List A: 1 -> 2 \
    //                  8 -> 9
    // List B:    3 -> 4 /
    
    ListNode* intersect = createNode(8);
    intersect->next = createNode(9);

    ListNode* headA = createNode(1);
    headA->next = createNode(2);
    headA->next->next = intersect;

    ListNode* headB = createNode(3);
    headB->next = createNode(4);
    headB->next->next = intersect;

    Solution s;
    ListNode* result = s.getIntersectionNode(headA, headB);

    if (result)
        cout << "Intersection Node value: " << result->val << endl;
    else
        cout << "No intersection found" << endl;

    return 0;
}
