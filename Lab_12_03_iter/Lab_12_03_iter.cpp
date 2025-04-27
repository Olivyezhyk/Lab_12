#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* createList(const int arr[], int size) {
    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < size; ++i) {
        Node* newNode = new Node{ arr[i], nullptr, nullptr };

        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    return head;
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

Node* filterListBySign(Node* head, bool positive) {
    Node* newHead = nullptr;
    Node* newTail = nullptr;

    Node* current = head;
    while (current) {
        if ((positive && current->data > 0) || (!positive && current->data < 0)) {
            Node* newNode = new Node{ current->data, nullptr, nullptr };
            if (!newHead) {
                newHead = newTail = newNode;
            }
            else {
                newTail->next = newNode;
                newNode->prev = newTail;
                newTail = newNode;
            }
        }
        current = current->next;
    }

    return newHead;
}

void deleteList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int values[] = { 3, -1, 4, -5, 2, -6, 8 };
    int size = sizeof(values) / sizeof(values[0]);

    Node* L = createList(values, size);
    cout << "List L: ";
    printList(L);

    Node* L1 = filterListBySign(L, true);
    cout << "List L1 (positive values): ";
    printList(L1);

    Node* L2 = filterListBySign(L, false);
    cout << "List L2 (negative values): ";
    printList(L2);

    deleteList(L);
    deleteList(L1);
    deleteList(L2);

    return 0;
}
