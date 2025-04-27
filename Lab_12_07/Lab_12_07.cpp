#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void appendToList(Node*& head, int value) {
    Node* newNode = new Node{ value, nullptr };
    if (!head) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void printList(const Node* head, const string& label) {
    cout << label << ": ";
    while (head) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int getListLength(const Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void reverseList(Node*& head) {
    Node* prev = nullptr;
    Node* current = head;
    while (current) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

bool isFibonacci(int n, const int* fibArray, int size) {
    for (int i = 0; i < size; ++i) {
        if (fibArray[i] == n) return true;
    }
    return false;
}

int generateFibonacciArray(int maxVal, int* fibArray, int maxSize) {
    int a = 0, b = 1;
    int count = 0;
    while (a <= maxVal && count < maxSize) {
        fibArray[count++] = a;
        int temp = a + b;
        a = b;
        b = temp;
    }
    return count;
}

void findFibonacciNumbers(const Node* head, int* foundFib, int& foundCount) {
    int maxValue = 0;
    const Node* temp = head;
    while (temp) {
        if (temp->data > maxValue) maxValue = temp->data;
        temp = temp->next;
    }

    const int MAX_FIB_SIZE = 50;
    int fibArray[MAX_FIB_SIZE];
    int fibCount = generateFibonacciArray(maxValue, fibArray, MAX_FIB_SIZE);

    foundCount = 0;
    temp = head;
    while (temp) {
        if (isFibonacci(temp->data, fibArray, fibCount)) {
            foundFib[foundCount++] = temp->data;
        }
        temp = temp->next;
    }
}

void readList(Node*& head) {
    string choice;
    cout << "Read from file or input manually? (file/manual): ";
    cin >> choice;

    if (choice == "file") {
        string filename;
        cout << "Enter filename: ";
        cin >> filename;
        ifstream file(filename);
        if (!file) {
            cerr << "Cannot open file.\n";
            return;
        }
        int value;
        while (file >> value) {
            appendToList(head, value);
        }
    }
    else {
        int count;
        cout << "How many numbers will you enter? ";
        cin >> count;
        cout << "Enter " << count << " integers:\n";
        for (int i = 0; i < count; ++i) {
            int value;
            cout << "Value " << (i + 1) << ": ";
            cin >> value;
            appendToList(head, value);
        }
    }
}


void deleteList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* list = nullptr;

    readList(list);
    cout << "\nOriginal list:" << endl;
    printList(list, "Input");

    int length = getListLength(list);
    cout << "List length: " << length << endl;

    const int MAX_FOUND = 100;
    int foundFib[MAX_FOUND];
    int foundCount = 0;

    findFibonacciNumbers(list, foundFib, foundCount);
    cout << "Fibonacci numbers found: ";
    for (int i = 0; i < foundCount; ++i) {
        cout << foundFib[i] << " ";
    }
    cout << endl;

    reverseList(list);
    cout << "\nReversed list:" << endl;
    printList(list, "Reversed");

    deleteList(list);
    return 0;
}
