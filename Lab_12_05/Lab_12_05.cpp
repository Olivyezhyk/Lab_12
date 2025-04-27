#include <iostream>
#include <fstream>
using namespace std;

struct Stack {
    int* arr;
    int top;
    int capacity;
};

Stack create_stack(int size) {
    Stack st;
    st.capacity = size;
    st.arr = new int[st.capacity];
    st.top = -1;
    return st;
}

void destroy_stack(Stack& st) {
    delete[] st.arr;
}

void push(Stack& st, int x) {
    if (st.top >= st.capacity - 1) {
        cout << "Stack overflow!" << endl;
        return;
    }
    st.arr[++st.top] = x;
}

int pop(Stack& st) {
    if (st.top == -1) {
        cout << "Stack underflow!" << endl;
        return -1;
    }
    return st.arr[st.top--];
}

bool stack_is_empty(const Stack& st) {
    return st.top == -1;
}

int size(const Stack& st) {
    return st.top + 1;
}

void print(const Stack& st) {
    if (st.top == -1) {
        cout << "Stack is empty." << endl;
        return;
    }
    for (int i = 0; i <= st.top; ++i) {
        cout << st.arr[i] << " ";
    }
    cout << endl;
}

Stack create_stack_from_input() {
    int n;
    cout << "Enter the number of elements in the stack: ";
    cin >> n;
    Stack st = create_stack(n);
    for (int i = 0; i < n; ++i) {
        int element;
        cout << "Enter element: ";
        cin >> element;
        push(st, element);
    }
    return st;
}

Stack create_stack_from_file(const string& filename) {
    ifstream file(filename);
    Stack st = create_stack(100);
    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        return st;
    }
    int element;
    while (file >> element) {
        push(st, element);
    }
    file.close();
    return st;
}

bool compare_stacks(const Stack& st1, const Stack& st2) {
    if (size(st1) != size(st2)) return false;
    for (int i = 0; i < size(st1); ++i) {
        if (st1.arr[i] != st2.arr[i]) return false;
    }
    return true;
}

Stack reverse_stack(Stack& st) {
    Stack reversed = create_stack(size(st));
    while (!stack_is_empty(st)) {
        push(reversed, pop(st));
    }
    return reversed;
}

Stack create_negative_stack(const Stack& st1, const Stack& st2) {
    Stack negative_stack = create_stack(size(st1) + size(st2));
    for (int i = 0; i < size(st1); ++i) {
        if (st1.arr[i] < 0) {
            push(negative_stack, st1.arr[i]);
        }
    }
    for (int i = 0; i < size(st2); ++i) {
        if (st2.arr[i] < 0) {
            push(negative_stack, st2.arr[i]);
        }
    }
    return negative_stack;
}

int main() {
    int choice;

    cout << "Select how to create stacks:\n";
    cout << "1. Create stacks from keyboard\n";
    cout << "2. Create stacks from file\n";
    cout << "Enter your choice (1/2): ";
    cin >> choice;

    Stack stack1, stack2;

    if (choice == 1) {
        cout << "Enter elements for Stack 1:" << endl;
        stack1 = create_stack_from_input();

        cout << "Enter elements for Stack 2:" << endl;
        stack2 = create_stack_from_input();
    }
    else if (choice == 2) {
        string filename;
        cout << "Enter the file name for Stack 1: ";
        cin >> filename;
        stack1 = create_stack_from_file(filename);

        cout << "Enter the file name for Stack 2: ";
        cin >> filename;
        stack2 = create_stack_from_file(filename);
    }
    else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    cout << "Stack 1 before transformation: ";
    print(stack1);

    cout << "Stack 2 before transformation: ";
    print(stack2);

    if (compare_stacks(stack1, stack2)) {
        cout << "Stack 1 and Stack 2 are the same. Reversing Stack 1." << endl;
        stack1 = reverse_stack(stack1);
        cout << "Stack 1 after reversal: ";
        print(stack1);
    }
    else {
        cout << "Stack 1 and Stack 2 are different. Creating a new stack with negative elements." << endl;
        Stack negative_stack = create_negative_stack(stack1, stack2);
        cout << "New stack with negative elements: ";
        print(negative_stack);
    }

    destroy_stack(stack1);
    destroy_stack(stack2);

    return 0;
}
