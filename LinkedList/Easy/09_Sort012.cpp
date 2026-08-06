/**
 * Problem: Sort a Linked List containing only 0s, 1s, and 2s
 *
 * Description:
 * Given a linked list where nodes contain only values 0, 1, or 2,
 * sort the list such that all 0s come first, then 1s, then 2s.
 *
 * Approaches:
 *
 * 1) Brute Force:
 *    - Count number of 0s, 1s, and 2s
 *    - Overwrite linked list values accordingly
 *    - Time: O(N), Space: O(1)
 *
 * 2) Better Approach (Used Here - Segregation using 3 lists):
 *    - Create three dummy lists for 0s, 1s, and 2s
 *    - Traverse original list and attach nodes accordingly
 *    - Merge three lists at the end
 *    - Time: O(N), Space: O(1) (no extra nodes, just pointers)
 *
 * Key Idea:
 *    Maintain three separate chains and then connect them.
 */
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
};

Node* sortList(Node *head) {
    if (!head || !head->next) return head;

    Node *zeroHead = new Node(-1), *zeroTail = zeroHead;
    Node *oneHead = new Node(-1), *oneTail = oneHead;
    Node *twoHead = new Node(-1), *twoTail = twoHead;

    Node* temp = head;
    while (temp) {
        if (temp->data == 0) {
            zeroTail->next = temp;
            zeroTail = temp;
        } else if (temp->data == 1) {
            oneTail->next = temp;
            oneTail = temp;
        } else {
            twoTail->next = temp;
            twoTail = temp;
        }
        temp = temp->next;
    }

    // Connect all parts
    zeroTail->next = (oneHead->next) ? oneHead->next : twoHead->next;
    oneTail->next = twoHead->next;
    twoTail->next = nullptr;

    Node* newHead = zeroHead->next;

    delete zeroHead;
    delete oneHead;
    delete twoHead;

    return newHead;
}

void printList(Node *head) {
    Node *temp = head;
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL";
}

int main() {
    Node *head = nullptr, *tail = nullptr;

    cout << "Enter elements to add to the linked list (-1 to stop):\n";
    int val;
    while (cin >> val && val != -1) {
        Node *newNode = new Node(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    cout << "List Before sort: ";
    printList(head);
    cout << endl;

    head = sortList(head);

    cout << "List After sort: ";
    printList(head);
    cout << endl;

    return 0;
}
