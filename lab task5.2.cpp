#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// ---------- Linked List based Stack (Stack 3) ----------
struct Node {
    int data;
    Node* next;
};

class LinkedStack {
    Node* top;

public:
    LinkedStack() {
        top = nullptr;
    }

    void push(int x) {
        Node* temp = new Node();
        temp->data = x;
        temp->next = top;
        top = temp;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        Node* temp = top;
        int val = temp->data;
        top = top->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    // Returns elements in bottom-to-top order
    // (top of stack is the head of linked list, so we
    //  collect head->tail first, then reverse it)
    vector<int> getElementsBottomToTop() {
        vector<int> topToBottom;
        Node* cur = top;
        while (cur != nullptr) {
            topToBottom.push_back(cur->data);
            cur = cur->next;
        }
        vector<int> bottomToTop(topToBottom.rbegin(), topToBottom.rend());
        return bottomToTop;
    }

    void display() {
        vector<int> elems = getElementsBottomToTop();
        cout << "Stack 3 (bottom -> top): ";
        for (int x : elems) cout << x << " ";
        cout << endl;
    }
};

// ---------- Array based Circular Queue ----------
class CircularQueue {
    int* arr;
    int front, rear, capacity;

public:
    CircularQueue(int size) {
        capacity = size;
        arr = new int[capacity];
        front = rear = -1;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isFull() {
        return (rear + 1) % capacity == front;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool enqueue(int val) {
        if (isFull()) {
            cout << "Circular Queue is full, cannot enqueue " << val << endl;
            return false;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        arr[rear] = val;
        return true;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Circular Queue is empty\n";
            return -1;
        }
        int val = arr[front];
        if (front == rear) {
            front = rear = -1; // queue becomes empty
        } else {
            front = (front + 1) % capacity;
        }
        return val;
    }

    void display() {
        if (isEmpty()) {
            cout << "Circular Queue is empty\n";
            return;
        }
        cout << "Circular Queue (front -> rear): ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % capacity;
        }
        cout << endl;
    }
};

// ---------- Helper to read a stack's elements (bottom-to-top) ----------
void readStack(vector<int>& stackArr, int n, const string& label) {
    cout << "Enter " << n << " elements for " << label
         << " (first entered = bottom, last entered = top):\n" << flush;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        stackArr.push_back(val);
    }
}

void displayArrayStack(const vector<int>& stackArr, const string& label) {
    cout << label << " (bottom -> top): ";
    for (int x : stackArr) cout << x << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n1, n2;

    cout << "Enter size of Stack 1: " << flush;
    cin >> n1;
    vector<int> stack1;
    readStack(stack1, n1, "Stack 1");

    cout << "Enter size of Stack 2: " << flush;
    cin >> n2;
    vector<int> stack2;
    readStack(stack2, n2, "Stack 2");

    cout << "\n--- Input Stacks ---\n";
    displayArrayStack(stack1, "Stack 1");
    displayArrayStack(stack2, "Stack 2");

    // ---------- Build Stack 3 by alternating from the bottom ----------
    LinkedStack stack3;
    int minLen = min(n1, n2);

    for (int i = 0; i < minLen; i++) {
        stack3.push(stack1[i]);
        stack3.push(stack2[i]);
    }

    // Append remaining elements from the longer stack
    if (n1 > n2) {
        for (int i = minLen; i < n1; i++) stack3.push(stack1[i]);
    } else if (n2 > n1) {
        for (int i = minLen; i < n2; i++) stack3.push(stack2[i]);
    }

    cout << "\n--- Merged Stack (Stack 3, Linked List) ---\n";
    stack3.display();

    // ---------- Sort Stack 3's elements in ascending order ----------
    vector<int> sortedElems = stack3.getElementsBottomToTop();
    sort(sortedElems.begin(), sortedElems.end());

    cout << "\n--- Sorted Elements (ascending) ---\n";
    for (int x : sortedElems) cout << x << " ";
    cout << endl;

    // ---------- Build and display Circular Queue from sorted elements ----------
    int n3 = sortedElems.size();
    CircularQueue cq(n3);

    for (int val : sortedElems) {
        cq.enqueue(val);
    }

    cout << "\n--- Circular Queue built from sorted elements ---\n";
    cq.display();

    return 0;
}
