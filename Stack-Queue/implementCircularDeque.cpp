#include <bits/stdc++.h>
using namespace std;

class MyCircularDeque{
public:
    vector<int>arr;
    int front,rear,size,cap;

    MyCircularDeque(int k){
        arr = vector<int>(k, -1);
        front = 0;
        rear = -1;
        size = 0;
        cap = k;
    }

    bool insertFront(int val){
        if(isFull()){
            return false;
        }
        if(isEmpty()){
            front=rear=0;
        }
        else{
            front=(front-1+cap)%cap;
        }
        arr[front]=val;
        size++;
        return true;
    }
    
    bool insertLast(int val){
        if(isFull()){
            return false;
        }
        if(isEmpty()){
            front=rear=0;
        }
        else{
            rear=(rear+1)%cap;
        }
        arr[rear]=val;
        size++;
        return true;
    }

    bool deleteFront(){
        if (isEmpty()) return false;
        if (size == 1) {
            front = 0; rear = -1;
        }
        else{
            front=(front+1)%cap;
        }
        size--;
        return true;
    }

    bool deleteLast(){
        if (isEmpty()) return false;
        if (size == 1) {
            front = 0; rear = -1;
        }
        else{
            rear=(rear-1+cap)%cap;
        }
        size--;
        return true;
    }

    int getFront(){
        return isEmpty()?-1:arr[front];
    }

    int getRear(){
        return isEmpty()?-1:arr[rear];
    }

    bool isEmpty(){
        return size==0;
    }

    bool isFull(){
        return size==cap;
    }
};

int main()
{
    MyCircularDeque dq(3);
    cout << "Insert Last 1: " << dq.insertLast(1) << "\n";                        // true
    cout << "Insert Last 2: " << dq.insertLast(2) << "\n";                        // true
    cout << "Insert Front 3: " << dq.insertFront(3) << "\n";                      // true
    cout << "Insert Front 4 (should fail - full): " << dq.insertFront(4) << "\n"; // false

    cout << "Get Rear: " << dq.getRear() << "\n"; // 2
    cout << "Is Full? " << dq.isFull() << "\n";   // true

    cout << "Delete Last: " << dq.deleteLast() << "\n";      // true
    cout << "Insert Front 4: " << dq.insertFront(4) << "\n"; // true
    cout << "Get Front: " << dq.getFront() << "\n";          // 4

    return 0;
}