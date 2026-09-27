#include <iostream>
using namespace std;

class Stack {
    int *arr;
    int top;
    int capacity;

public:
    Stack(int size) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    bool push(int x) {
        if (top >= capacity - 1) {
            cout << "Stack Overflow\n";
            return false;
        }
        arr[++top] = x;
        return true;
    }

    int pop() {
        if (top < 0) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }

    bool isEmpty() {
        return top < 0;
    }

    int size() {
        return top + 1;
    }

    int getMax() {
        int mx = arr[0];
        for (int i = 1; i <= top; i++) {
            if (arr[i] > mx) mx = arr[i];
        }
        return mx;
    }

    int getMin() {
        int mn = arr[0];
        for (int i = 1; i <= top; i++) {
            if (arr[i] < mn) mn = arr[i];
        }
        return mn;
    }

    // Handles both odd and even count of elements
    void displayMiddle() {
        int n = top + 1; // total elements currently in stack

        if (n == 0) {
            cout << "Stack is empty, no middle element.\n";
            return;
        }

        if (n % 2 == 1) {
            // Odd count -> single middle element
            int midIndex = n / 2; // 0-based index counted from bottom
            cout << "Middle element: " << arr[midIndex] << endl;
        } else {
            // Even count -> two middle elements
            int idx1 = n / 2 - 1;
            int idx2 = n / 2;
            cout << "Middle elements: " << arr[idx1] << " and " << arr[idx2] << endl;
        }
    }

    void display() {
        cout << "Stack (bottom -> top): ";
        for (int i = 0; i <= top; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    Stack s(n);

    cout << "Enter elements (first entered = bottom, last entered = top):\n";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        s.push(val);
    }

    cout << "\n--- Stack Contents ---\n";
    s.display();

    if (!s.isEmpty()) {
        cout << "\n--- Results ---\n";
        cout << "Maximum value: " << s.getMax() << endl;
        cout << "Minimum value: " << s.getMin() << endl;
        s.displayMiddle();
    } else {
        cout << "Stack is empty.\n";
    }

    return 0;
}
