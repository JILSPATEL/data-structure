class MyCircularDeque {
public:
    vector<int> arr;
    int front, back, currSize, cap;

    MyCircularDeque(int k) {
        arr = vector<int>(k, -1);
        front = 0;
        back = -1;
        currSize = 0;
        cap = k;
    }

    bool insertFront(int value) {
        if (isFull())
            return false;
        if (currSize == 0) {
            front = back = 0;
        } else if (front == 0) {
            front = cap - 1;
        } else {
            front--;
        }
        arr[front] = value;
        currSize++;
        return true;
    }

    bool insertLast(int value) {
        if (isFull())
            return false;
        if (currSize == 0) {
            front = back = 0;
        } else if (back == cap - 1) {
            back = 0;
        } else {
            back++;
        }
        arr[back] = value;
        currSize++;
        return true;
    }

    bool deleteFront() {
        if (isEmpty())
            return false;
        if (currSize == 1) {
            front = 0;
            back = -1;
        } else if (front == cap - 1) {
            front = 0;
        } else {
            front++;
        }
        currSize--;
        return true;
    }

    bool deleteLast() {
        if (isEmpty())
            return false;
        if (currSize == 1) {
            front = 0;
            back = -1;
        } else if (back == 0) {
            back = cap - 1;
        } else {
            back--;
        }
        currSize--;
        return true;
    }

    int getFront() { return isEmpty() ? -1 : arr[front]; }

    int getRear() { return isEmpty() ? -1 : arr[back]; }

    bool isEmpty() { return currSize == 0; }

    bool isFull() { return currSize == cap; }
};

