#include <iostream>
using namespace std;
struct node
{
    int data;
    node *next;
    node(int val)
    {
        data = val;
        next = nullptr;
    }
};
void printList(node *&head)
{
    node *temp = head;
    while (temp)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
}
int main()
{
    node *head = nullptr;

    int val;
    cout << "Enter -1 For End The Program" << endl;
    while (cin >> val && val != -1)
    {
        node *newNode = new node(val);
        newNode->next = head;
        head = newNode;
    }
    printList(head);
    return 0;
}
