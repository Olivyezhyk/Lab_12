#include <iostream>
#include <fstream>
#include <string>

struct HelpItem {
    std::string term;
    std::string explanation[5];
    int linesCount;
    HelpItem* next;
};

void addHelpItem(HelpItem*& head) {
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

    newItem->next = nullptr;

    if (!head) {
        head = newItem;
    }
    else {
        HelpItem* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newItem;
    }
}

void displayHelpList(HelpItem* head) {
    std::cout << "\n=== Help List ===\n";
    while (head) {
        std::cout << "\nTerm: " << head->term << "\nExplanation:\n";
        for (int i = 0; i < head->linesCount; ++i) {
            std::cout << head->explanation[i] << "\n";
        }
        head = head->next;
    }
}

HelpItem* findHelpItem(HelpItem* head, const std::string& term) {
    while (head) {
        if (head->term == term)
            return head;
        head = head->next;
    }
    return nullptr;
}

void removeHelpItem(HelpItem*& head, const std::string& term) {
    HelpItem* prev = nullptr;
    HelpItem* curr = head;

    while (curr) {
        if (curr->term == term) {
            if (prev)
                prev->next = curr->next;
            else
                head = curr->next;

            delete curr;
            std::cout << "Term removed.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    std::cout << "Term not found.\n";
}

void sortHelpList(HelpItem*& head) {
    if (!head || !head->next) return;

    bool swapped;
    do {
        swapped = false;
        HelpItem* curr = head;
        HelpItem* prev = nullptr;
        HelpItem* next = head->next;

        while (next) {
            if (curr->term > next->term) {
                if (prev)
                    prev->next = next;
                else
                    head = next;

                curr->next = next->next;
                next->next = curr;

                swapped = true;
                prev = next;
                next = curr->next;
            }
            else {
                prev = curr;
                curr = next;
                next = next->next;
            }
        }
    } while (swapped);

    std::cout << "List sorted.\n";
}

void saveListToFile(HelpItem* head, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error opening file.\n";
        return;
    }

    while (head) {
        file << head->term << "\n";
        file << head->linesCount << "\n";
        for (int i = 0; i < head->linesCount; ++i) {
            file << head->explanation[i] << "\n";
        }
        head = head->next;
    }

    std::cout << "Saved to file.\n";
}

void loadListFromFile(HelpItem*& head, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File not found.\n";
        return;
    }

    while (head) {
        HelpItem* temp = head;
        head = head->next;
        delete temp;
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
        newItem->next = nullptr;

        if (!head) {
            head = newItem;
        }
        else {
            HelpItem* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newItem;
        }
    }

    std::cout << "Loaded from file.\n";
}

void freeList(HelpItem*& head) {
    while (head) {
        HelpItem* temp = head;
        head = head->next;
        delete temp;
    }
}

void menu() {
    HelpItem* helpList = nullptr;
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
            addHelpItem(helpList);
            break;
        case 2:
            std::cout << "Enter term to remove: ";
            std::getline(std::cin, term);
            removeHelpItem(helpList, term);
            break;
        case 3:
            displayHelpList(helpList);
            break;
        case 4:
            std::cout << "Enter term to search: ";
            std::getline(std::cin, term);
            {
                HelpItem* found = findHelpItem(helpList, term);
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
            sortHelpList(helpList);
            break;
        case 6:
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            saveListToFile(helpList, filename);
            break;
        case 7:
            std::cout << "Enter filename to load: ";
            std::getline(std::cin, filename);
            loadListFromFile(helpList, filename);
            break;
        case 0:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    freeList(helpList);
}

int main() {
    menu();
    return 0;
}
