#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

struct Date {
    int day;
    int month;
    int year;
};

struct Note {
    std::string surname;
    std::string name;
    std::string phone;
    Date birthday;
};

struct TreeNode {
    Note data;
    TreeNode* left;
    TreeNode* right;
};

int getValidatedInt(int min, int max) {
    int value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        }
        else {
            break;
        }
    }
    return value;
}

Note inputNote() {
    Note n;
    std::cout << "Enter surname: ";
    std::cin >> n.surname;
    std::cout << "Enter name: ";
    std::cin >> n.name;
    std::cout << "Enter phone number: ";
    std::cin >> n.phone;
    std::cout << "Enter birthday (day month year): ";
    n.birthday.day = getValidatedInt(1, 31);
    n.birthday.month = getValidatedInt(1, 12);
    n.birthday.year = getValidatedInt(1900, 2100);
    return n;
}

TreeNode* createNode(const Note& n) {
    TreeNode* newNode = new TreeNode{ n, nullptr, nullptr };
    return newNode;
}

void insertNode(TreeNode*& root, const Note& newNote) {
    if (!root) {
        root = createNode(newNote);
        return;
    }

    if (newNote.phone < root->data.phone) {
        insertNode(root->left, newNote);
    }
    else if (newNote.phone > root->data.phone) {
        insertNode(root->right, newNote);
    }
    else {
        std::cout << "Duplicate phone number! Cannot add contact.\n";
    }
}

bool deleteNodeByPhone(TreeNode*& root, const std::string& phone) {
    if (!root) return false;

    if (phone < root->data.phone) {
        return deleteNodeByPhone(root->left, phone);
    }
    else if (phone > root->data.phone) {
        return deleteNodeByPhone(root->right, phone);
    }
    else {
        TreeNode* temp = root;
        if (!root->left) {
            root = root->right;
        }
        else if (!root->right) {
            root = root->left;
        }
        else {
            TreeNode* minNode = root->right;
            while (minNode->left) {
                minNode = minNode->left;
            }
            root->data = minNode->data;
            deleteNodeByPhone(root->right, minNode->data.phone);
        }
        delete temp;
        return true;
    }
}

bool findNodeByPhone(TreeNode* root, const std::string& phone, Note& result) {
    if (!root) return false;

    if (phone < root->data.phone) {
        return findNodeByPhone(root->left, phone, result);
    }
    else if (phone > root->data.phone) {
        return findNodeByPhone(root->right, phone, result);
    }
    else {
        result = root->data;
        return true;
    }
}

void printNote(const Note& n) {
    std::cout << std::left << std::setw(15) << n.surname
        << std::setw(15) << n.name
        << std::setw(15) << n.phone
        << std::setw(10) << (std::to_string(n.birthday.day) + "/" +
            std::to_string(n.birthday.month) + "/" +
            std::to_string(n.birthday.year)) << '\n';
}

void printTree(TreeNode* root) {
    if (!root) return;
    printTree(root->left);
    printNote(root->data);
    printTree(root->right);
}

void saveTree(TreeNode* root, std::ofstream& fout) {
    if (!root) return;
    fout << root->data.surname << " "
        << root->data.name << " "
        << root->data.phone << " "
        << root->data.birthday.day << " "
        << root->data.birthday.month << " "
        << root->data.birthday.year << "\n";
    saveTree(root->left, fout);
    saveTree(root->right, fout);
}

bool saveTreeToFile(TreeNode* root, const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout) return false;
    saveTree(root, fout);
    return true;
}

bool loadTreeFromFile(TreeNode*& root, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) return false;

    Note n;
    while (fin >> n.surname >> n.name >> n.phone
        >> n.birthday.day >> n.birthday.month >> n.birthday.year) {
        insertNode(root, n);
    }
    return true;
}

void freeTree(TreeNode*& root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
    root = nullptr;
}

bool isEarlier(const Date& a, const Date& b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

void insertByBirthday(TreeNode*& root, const Note& n) {
    if (!root) {
        root = createNode(n);
        return;
    }
    if (isEarlier(n.birthday, root->data.birthday)) {
        insertByBirthday(root->left, n);
    }
    else {
        insertByBirthday(root->right, n);
    }
}

void copyTreeToBirthdayTree(TreeNode* src, TreeNode*& dst) {
    if (!src) return;
    copyTreeToBirthdayTree(src->left, dst);
    insertByBirthday(dst, src->data);
    copyTreeToBirthdayTree(src->right, dst);
}

void sortTreeByBirthday(TreeNode*& root) {
    TreeNode* newRoot = nullptr;
    copyTreeToBirthdayTree(root, newRoot);
    freeTree(root);
    root = newRoot;
}

void menu() {
    TreeNode* root = nullptr;
    int choice;
    std::string phone, filename;
    Note result;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add new note\n";
        std::cout << "2. Delete note by phone\n";
        std::cout << "3. Search note by phone\n";
        std::cout << "4. Print all notes\n";
        std::cout << "5. Sort notes by birthday\n";
        std::cout << "6. Save list to file\n";
        std::cout << "7. Load list from file\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        choice = getValidatedInt(0, 7);

        switch (choice) {
        case 1:
            insertNode(root, inputNote());
            break;
        case 2:
            std::cout << "Enter phone to delete: ";
            std::cin >> phone;
            if (deleteNodeByPhone(root, phone))
                std::cout << "Deleted successfully.\n";
            else
                std::cout << "Phone not found.\n";
            break;
        case 3:
            std::cout << "Enter phone to search: ";
            std::cin >> phone;
            if (findNodeByPhone(root, phone, result))
                printNote(result);
            else
                std::cout << "No such contact found.\n";
            break;
        case 4:
            printTree(root);
            break;
        case 5:
            sortTreeByBirthday(root);
            std::cout << "Tree sorted by birthday.\n";
            break;
        case 6:
            std::cout << "Enter filename to save: ";
            std::cin >> filename;
            if (saveTreeToFile(root, filename))
                std::cout << "Saved successfully.\n";
            else
                std::cout << "Failed to save file.\n";
            break;
        case 7:
            std::cout << "Enter filename to load: ";
            std::cin >> filename;
            if (loadTreeFromFile(root, filename))
                std::cout << "Loaded successfully.\n";
            else
                std::cout << "Failed to load file.\n";
            break;
        }

    } while (choice != 0);

    freeTree(root);
    std::cout << "Goodbye!\n";
}

int main() {
    menu();
    return 0;
}