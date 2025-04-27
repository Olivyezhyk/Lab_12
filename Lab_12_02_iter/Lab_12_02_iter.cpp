#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int* generateArray(int& size) {
    static int fixedArr[8] = { 3, 5, 3, 0, 5, 10, 2, 1 };
    size = 8;
    return fixedArr;
}

Node* createList(const int* arr, int size) {
    if (size == 0) return nullptr;

    Node* head = new Node{ arr[0], nullptr };
    Node* tail = head;

    for (int i = 1; i < size; ++i) {
        Node* newNode = new Node{ arr[i], nullptr };
        tail->next = newNode;
        tail = newNode;
    }
    return head;
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void insertAfterValue(Node*& head, int V1, int V2) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data == V1) {
            Node* newNode = new Node{ V2, current->next };
            current->next = newNode;
            current = newNode->next;
        }
        else {
            current = current->next;
        }
    }
}

int main() {
    int size;
    int* arr = generateArray(size);
    int V1 = 5;
    int V2 = 99;

    Node* head = createList(arr, size);

    cout << "List before insertion:" << endl;
    printList(head);

    insertAfterValue(head, V1, V2);

    cout << "List after inserting " << V2 << " after each " << V1 << ":" << endl;
    printList(head);

    freeList(head);

    return 0;
}
