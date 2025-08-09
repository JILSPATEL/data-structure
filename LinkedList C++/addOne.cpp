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

Node* reverse(Node* &head){
    Node *prev = nullptr;
    Node *curr = head;
    while (curr)
    {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

Node* addOne(Node* &head){
    Node* temp = reverse(head);
    Node* newHead = temp;
    int carry = 1;

    while (temp) {
        int sum = temp->data + carry;
        carry = sum / 10;
        temp->data = sum % 10;

        if (carry == 0) break;

        // Move to next node
        if (!temp->next && carry) {
            temp->next = new Node(carry);
            carry = 0;
            break;
        }
        temp = temp->next;
    }

    head = reverse(newHead);
    return head;
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

    head=addOne(head);

    cout<<"List After Add 1: ";
    printList(head);
    cout << endl;

    return 0;
}
