#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

Node* addNode(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = addNode(root->left, value);
    }
    else {
        root->right = addNode(root->right, value);
    }
    return root;
}

Node* addMultipleNodes(Node* root) {
    int n, value;
    cout << "Enter number of nodes to add: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> value;
        root = addNode(root, value);
    }
    return root;
}

Node* searchNode(Node* root, int value) {
    if (root == nullptr || root->data == value) {
        return root;
    }
    if (value < root->data) {
        return searchNode(root->left, value);
    }
    else {
        return searchNode(root->right, value);
    }
}

Node* findMin(Node* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return root;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int countNodesAtLevel(Node* root, int level, int currentLevel = 0) {
    if (root == nullptr) return 0;
    if (currentLevel == level) return 1;
    return countNodesAtLevel(root->left, level, currentLevel + 1) +
           countNodesAtLevel(root->right, level, currentLevel + 1);
}

void printNodesAtLevel(Node* root, int level, int currentLevel = 0) {
    if (root == nullptr) return;
    if (currentLevel == level) {
        cout << root->data << " ";
    }
    printNodesAtLevel(root->left, level, currentLevel + 1);
    printNodesAtLevel(root->right, level, currentLevel + 1);
}

void menu() {
    Node* root = nullptr;
    int choice, value, level;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add multiple nodes\n";
        cout << "2. Search for a node\n";
        cout << "3. Delete a node\n";
        cout << "4. Count nodes at a specific level\n";
        cout << "5. Print nodes at a specific level\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            root = addMultipleNodes(root);
            break;

        case 2:
            cout << "Enter value to search: ";
            cin >> value;
            if (searchNode(root, value)) {
                cout << "Node with value " << value << " found.\n";
            }
            else {
                cout << "Node with value " << value << " not found.\n";
            }
            break;

        case 3:
            cout << "Enter value to delete: ";
            cin >> value;
            root = deleteNode(root, value);
            cout << "Node with value " << value << " deleted.\n";
            break;

        case 4:
            cout << "Enter level to count nodes: ";
            cin >> level;
            cout << "Number of nodes at level " << level << ": "
                 << countNodesAtLevel(root, level) << endl;
            break;

        case 5:
            cout << "Enter level to print nodes: ";
            cin >> level;
            cout << "Nodes at level " << level << ": ";
            printNodesAtLevel(root, level);
            cout << endl;
            break;

        case 6:
            return;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
