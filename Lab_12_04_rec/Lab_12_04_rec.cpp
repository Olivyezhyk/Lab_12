#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* create_list_recursive(const int arr[], int size, int index = 0) {
    if (index >= size) return nullptr;

    Node* newNode = new Node{ arr[index], nullptr };
    newNode->next = create_list_recursive(arr, size, index + 1);
    return newNode;
}

void print_list_recursive(Node* head) {
    if (!head) return;
    cout << head->data << " ";
    print_list_recursive(head->next);
}

int sum_positive_elements_recursive(Node* head) {
    if (!head) return 0;
    int sum = 0;
    if (head->data > 0) {
        sum = head->data;
    }
    return sum + sum_positive_elements_recursive(head->next);
}

void free_list_recursive(Node*& head) {
    if (!head) return;

    Node* current = head;
    head = head->next;
    delete current;

    free_list_recursive(head);
}


int main() {
    int values[] = { 3, -1, 7, 0, -5, 12 };
    int size = sizeof(values) / sizeof(values[0]);

    Node* head = create_list_recursive(values, size);

    cout << "Initial list: ";
    print_list_recursive(head);
    cout << endl;

    int sum = sum_positive_elements_recursive(head);
    cout << "Sum of positive elements: " << sum << endl;

    free_list_recursive(head);
    return 0;
}
