#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* create_list(const int arr[], int size) {
    if (size <= 0) return nullptr;

    Node* head = new Node{ arr[0], nullptr };
    Node* current = head;

    for (int i = 1; i < size; ++i) {
        current->next = new Node{ arr[i], nullptr };
        current = current->next;
    }

    current->next = head;
    return head;
}

void print_list(Node* head) {
    if (!head) return;

    Node* current = head;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}

int sum_positive_elements(Node* head) {
    if (!head) return 0;

    int sum = 0;
    Node* current = head;
    do {
        if (current->data > 0) {
            sum += current->data;
        }
        current = current->next;
    } while (current != head);

    return sum;
}

void free_list(Node*& head) {
    if (!head) return;

    Node* current = head->next;
    while (current != head) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    delete head;
    head = nullptr;
}

int main() {
    int values[] = { 3, -1, 7, 0, -5, 12 };
    int size = sizeof(values) / sizeof(values[0]);

    Node* head = create_list(values, size);

    cout << "Initial list: ";
    print_list(head);

    int sum = sum_positive_elements(head);
    cout << "Sum of positive elements: " << sum << endl;

    free_list(head);
    return 0;
}
