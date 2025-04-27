#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

TreeNode* addNode(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }

    if (value < root->data) {
        root->left = addNode(root->left, value);
    }
    else {
        root->right = addNode(root->right, value);
    }
    return root;
}

TreeNode* buildBalancedTree(int arr[], int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    TreeNode* node = new TreeNode(arr[mid]);

    node->left = buildBalancedTree(arr, start, mid - 1);
    node->right = buildBalancedTree(arr, mid + 1, end);

    return node;
}

void inOrderTraversal(TreeNode* root, int result[], int& index) {
    if (root == nullptr) return;

    inOrderTraversal(root->left, result, index);
    result[index++] = root->data;
    inOrderTraversal(root->right, result, index);
}

void deleteLeafNode(TreeNode*& root, int value) {
    if (root == nullptr) return;

    if (value < root->data) {
        deleteLeafNode(root->left, value);
    }
    else if (value > root->data) {
        deleteLeafNode(root->right, value);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
    }
}

void deleteNodeWithOneChild(TreeNode*& root, int value) {
    if (root == nullptr) return;

    if (value < root->data) {
        deleteNodeWithOneChild(root->left, value);
    }
    else if (value > root->data) {
        deleteNodeWithOneChild(root->right, value);
    }
    else {
        if (root->left == nullptr) {
            TreeNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root;
            root = root->left;
            delete temp;
        }
    }
}

TreeNode* findMinNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

TreeNode* deleteNodeWithTwoChildren(TreeNode* root, int value) {
    if (root == nullptr) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNodeWithTwoChildren(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNodeWithTwoChildren(root->right, value);
    }
    else {
        if (root->left != nullptr && root->right != nullptr) {
            TreeNode* minNode = findMinNode(root->right);

            root->data = minNode->data;

            root->right = deleteNodeWithTwoChildren(root->right, minNode->data);
        }
        else {
            TreeNode* temp = root;
            if (root->left == nullptr) {
                root = root->right;
            }
            else if (root->right == nullptr) {
                root = root->left;
            }
            delete temp;
        }
    }
    return root;
}

void deleteSubtree(TreeNode*& root, int value) {
    if (root == nullptr) return;

    if (value < root->data) {
        deleteSubtree(root->left, value);
    }
    else if (value > root->data) {
        deleteSubtree(root->right, value);
    }
    else {
        delete root;
        root = nullptr;
    }
}

int findMaxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int leftDepth = findMaxDepth(root->left);
    int rightDepth = findMaxDepth(root->right);
    return max(leftDepth, rightDepth) + 1;
}

void deleteTree(TreeNode*& root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
}

int main() {
    TreeNode* root = nullptr;
    int choice, value, index;
    int result[100];

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Create Binary Search Tree\n";
        cout << "2. Print Tree\n";
        cout << "3. Print Tree with Highlighted Current Element\n";
        cout << "4. Add Element\n";
        cout << "5. Balance Tree\n";
        cout << "6. Delete Leaf Node\n";
        cout << "7. Delete Node with One Child\n";
        cout << "8. Delete Node with Two Children\n";
        cout << "9. Delete Subtree\n";
        cout << "10. Find Maximum Depth\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int n;
            cout << "How many elements in the tree? ";
            cin >> n;
            for (int i = 0; i < n; ++i) {
                cout << "Enter value " << i + 1 << ": ";
                cin >> value;
                root = addNode(root, value);
            }
            break;
        }

        case 2: {
            index = 0;
            inOrderTraversal(root, result, index);
            cout << "Tree as list: ";
            for (int i = 0; i < index; ++i) {
                cout << result[i] << " ";
            }
            cout << endl;
            break;
        }

        case 3: {
            cout << "Enter the value to highlight: ";
            cin >> value;
            index = 0;
            inOrderTraversal(root, result, index);
            cout << "Tree as list: ";
            for (int i = 0; i < index; ++i) {
                if (result[i] == value) {
                    cout << "[" << result[i] << "] ";
                }
                else {
                    cout << result[i] << " ";
                }
            }
            cout << endl;
            break;
        }
        case 4: {
            cout << "Enter value to add: ";
            cin >> value;
            root = addNode(root, value);
            break;
        }
        case 5: {
            index = 0;
            inOrderTraversal(root, result, index);
            deleteTree(root);
            root = buildBalancedTree(result, 0, index - 1);
            cout << "Tree balanced successfully!\n";
            break;
        }

        case 6: {
            cout << "Enter value to delete (leaf): ";
            cin >> value;
            deleteLeafNode(root, value);
            break;
        }

        case 7: {
            cout << "Enter value to delete (one child): ";
            cin >> value;
            deleteNodeWithOneChild(root, value);
            break;
        }

        case 8: {
            cout << "Enter value to delete (two children): ";
            cin >> value;
            deleteNodeWithTwoChildren(root, value);
            break;
        }

        case 9: {
            cout << "Enter root value of subtree to delete: ";
            cin >> value;
            deleteSubtree(root, value);
            break;
        }

        case 10: {
            int depth = findMaxDepth(root);
            cout << "Maximum Depth: " << depth << endl;
            break;
        }

        case 0:
            deleteTree(root);
            return 0;

        default:
            cout << "Invalid choice!\n";
            break;
        }
    }

    return 0;
}
