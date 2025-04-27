#include <iostream>
#include <fstream>
#include <string>

struct HelpItem {
    std::string term;
    std::string explanation[5];
    int linesCount;
    HelpItem* left;
    HelpItem* right;
};

void addHelpItem(HelpItem*& root) {
    HelpItem* newItem = new HelpItem;
    std::cout << "\nEnter term: ";
    std::getline(std::cin, newItem->term);

    do {
        std::cout << "How many explanation lines (1-5)? ";
        std::cin >> newItem->linesCount;
        std::cin.ignore();
    } while (newItem->linesCount < 1 || newItem->linesCount > 5);

    std::cout << "Enter explanation:\n";
    for (int i = 0; i < newItem->linesCount; ++i) {
        std::getline(std::cin, newItem->explanation[i]);
    }

    newItem->left = newItem->right = nullptr;

    if (!root) {
        root = newItem;
    }
    else {
        HelpItem* current = root;
        HelpItem* parent = nullptr;
        while (current) {
            parent = current;
            if (newItem->term < current->term) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        if (newItem->term < parent->term) {
            parent->left = newItem;
        }
        else {
            parent->right = newItem;
        }
    }
}

void displayHelpTree(HelpItem* root) {
    if (!root) return;
    displayHelpTree(root->left);
    std::cout << "\nTerm: " << root->term << "\nExplanation:\n";
    for (int i = 0; i < root->linesCount; ++i) {
        std::cout << root->explanation[i] << "\n";
    }
    displayHelpTree(root->right);
}

HelpItem* findHelpItem(HelpItem* root, const std::string& term) {
    while (root) {
        if (root->term == term) return root;
        if (term < root->term) root = root->left;
        else root = root->right;
    }
    return nullptr;
}

void removeHelpItem(HelpItem*& root, const std::string& term) {
    if (!root) return;

    if (term < root->term) {
        removeHelpItem(root->left, term);
    }
    else if (term > root->term) {
        removeHelpItem(root->right, term);
    }
    else {
        if (!root->left && !root->right) {
            delete root;
            root = nullptr;
        }
        else if (!root->left) {
            HelpItem* temp = root;
            root = root->right;
            delete temp;
        }
        else if (!root->right) {
            HelpItem* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            HelpItem* temp = root->right;
            while (temp && temp->left) temp = temp->left;
            root->term = temp->term;
            root->linesCount = temp->linesCount;
            for (int i = 0; i < temp->linesCount; ++i) {
                root->explanation[i] = temp->explanation[i];
            }
            removeHelpItem(root->right, temp->term);
        }
    }
}

void sortHelpTree(HelpItem*& root) {
    displayHelpTree(root);
}


void saveTreeToFile(HelpItem* root, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error opening file.\n";
        return;
    }

    if (root) {
        file << root->term << "\n";
        file << root->linesCount << "\n";
        for (int i = 0; i < root->linesCount; ++i) {
            file << root->explanation[i] << "\n";
        }
        saveTreeToFile(root->left, filename);
        saveTreeToFile(root->right, filename);
    }

    std::cout << "Saved to file.\n";
}

void loadTreeFromFile(HelpItem*& root, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File not found.\n";
        return;
    }

    while (root) {
        removeHelpItem(root, root->term);
    }

    while (!file.eof()) {
        HelpItem* newItem = new HelpItem;
        std::getline(file, newItem->term);
        if (newItem->term.empty()) {
            delete newItem;
            break;
        }
        file >> newItem->linesCount;
        file.ignore();
        for (int i = 0; i < newItem->linesCount; ++i) {
            std::getline(file, newItem->explanation[i]);
        }
        newItem->left = newItem->right = nullptr;

        if (!root) {
            root = newItem;
        }
        else {
            HelpItem* current = root;
            HelpItem* parent = nullptr;
            while (current) {
                parent = current;
                if (newItem->term < current->term) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }

            if (newItem->term < parent->term) {
                parent->left = newItem;
            }
            else {
                parent->right = newItem;
            }
        }
    }

    std::cout << "Loaded from file.\n";
}

void freeTree(HelpItem*& root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
    root = nullptr;
}

void menu() {
    HelpItem* helpTree = nullptr;
    int choice;
    std::string term, filename;

    do {
        std::cout << "\n=== MENU ===\n"
            << "1. Add term\n"
            << "2. Remove term\n"
            << "3. Show help list\n"
            << "4. Find explanation\n"
            << "5. Sort list\n"
            << "6. Save to file\n"
            << "7. Load from file\n"
            << "0. Exit\n"
            << "Your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            addHelpItem(helpTree);
            break;
        case 2:
            std::cout << "Enter term to remove: ";
            std::getline(std::cin, term);
            removeHelpItem(helpTree, term);
            break;
        case 3:
            displayHelpTree(helpTree);
            break;
        case 4:
            std::cout << "Enter term to search: ";
            std::getline(std::cin, term);
            {
                HelpItem* found = findHelpItem(helpTree, term);
                if (found) {
                    std::cout << "Explanation:\n";
                    for (int i = 0; i < found->linesCount; ++i)
                        std::cout << found->explanation[i] << "\n";
                }
                else {
                    std::cout << "Term not found.\n";
                }
            }
            break;
        case 5:
            sortHelpTree(helpTree);
            break;
        case 6:
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            saveTreeToFile(helpTree, filename);
            break;
        case 7:
            std::cout << "Enter filename to load: ";
            std::getline(std::cin, filename);
            loadTreeFromFile(helpTree, filename);
            break;
        case 0:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    freeTree(helpTree);
}

int main() {
    menu();
    return 0;
}
