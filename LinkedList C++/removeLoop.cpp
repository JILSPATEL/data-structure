#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
};

// Function to remove a loop in a linked list
void removeLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {  
            slow = head;
                while (slow->next != fast->next) {
                    slow = slow->next;
                    fast = fast->next;
                }
            
            fast->next = nullptr; // Break the loop
            return;
        }
    }
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Node *head = nullptr;
    Node *tail = nullptr;
    cout << "Enter numbers to add to the linked list (-1 to stop):\n";
    int val;
    while (cin >> val && val != -1) {
        Node *newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // ✅ Create a loop manually for testing: connect tail to 2nd node
    if (head && head->next) {
        tail->next = head->next;
    }

    removeLoop(head);
    printList(head);

    return 0;
}
