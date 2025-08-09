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
