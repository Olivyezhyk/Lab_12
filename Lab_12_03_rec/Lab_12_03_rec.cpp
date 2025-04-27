#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* createList(const int arr[], int size, int index = 0) {
    if (index == size) return nullptr;

    Node* newNode = new Node{ arr[index], nullptr, nullptr };
    newNode->next = createList(arr, size, index + 1);

    if (newNode->next) {
        newNode->next->prev = newNode;
    }

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

Node* filterListBySign(Node* head, bool positive) {
    if (head == nullptr) return nullptr;

    Node* newNode = nullptr;
    if ((positive && head->data > 0) || (!positive && head->data < 0)) {
        newNode = new Node{ head->data, nullptr, nullptr };
        newNode->next = filterListBySign(head->next, positive);

        if (newNode->next) {
            newNode->next->prev = newNode;
        }
    }
    else {
        newNode = filterListBySign(head->next, positive);
    }

    return newNode;
}

void deleteList(Node* head) {
    if (head == nullptr) return;
    Node* temp = head;
    deleteList(head->next);
    delete temp;
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
