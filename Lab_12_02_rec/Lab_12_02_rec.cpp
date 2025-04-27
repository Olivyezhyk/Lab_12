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
    Node* newNode = new Node{ arr[0], createList(arr + 1, size - 1) };
    return newNode;
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << endl;
        return;
    }
    cout << head->data << " ";
    printList(head->next);
}

void freeList(Node*& head) {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    delete temp;
    freeList(head);
}

void insertAfterValue(Node*& head, int V1, int V2) {
    if (head == nullptr) return;

    if (head->data == V1) {
        Node* newNode = new Node{ V2, head->next };
        head->next = newNode;
        insertAfterValue(newNode->next, V1, V2);
    }
    else {
        insertAfterValue(head->next, V1, V2);
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
