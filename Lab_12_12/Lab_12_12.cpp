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

struct ListNode {
    Note data;
    ListNode* next;
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

void addNoteToList(ListNode*& head, const Note& newNote) {
    ListNode* newNode = new ListNode{ newNote, nullptr };
    if (!head) {
        head = newNode;
    }
    else {
        ListNode* current = head;
        while (current->next)
            current = current->next;
        current->next = newNode;
    }
}

bool deleteNoteByPhone(ListNode*& head, const std::string& phone) {
    ListNode* current = head;
    ListNode* prev = nullptr;
    while (current) {
        if (current->data.phone == phone) {
            if (prev) prev->next = current->next;
            else head = current->next;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

bool findNoteByPhone(ListNode* head, const std::string& phone, Note& result) {
    while (head) {
        if (head->data.phone == phone) {
            result = head->data;
            return true;
        }
        head = head->next;
    }
    return false;
}

void printNote(const Note& n) {
    std::cout << std::left << std::setw(15) << n.surname
        << std::setw(15) << n.name
        << std::setw(15) << n.phone
        << std::setw(10) << (std::to_string(n.birthday.day) + "/" +
            std::to_string(n.birthday.month) + "/" +
            std::to_string(n.birthday.year)) << '\n';
}

void printList(ListNode* head) {
    if (!head) {
        std::cout << "The list is empty.\n";
        return;
    }
    std::cout << "\nDirectory:\n";
    std::cout << std::left << std::setw(15) << "Surname"
        << std::setw(15) << "Name"
        << std::setw(15) << "Phone"
        << std::setw(10) << "Birthday" << "\n";
    std::cout << "----------------------------------------------------------\n";
    while (head) {
        printNote(head->data);
        head = head->next;
    }
}

bool isEarlier(const Date& a, const Date& b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

void sortListByBirthday(ListNode*& head) {
    if (!head || !head->next) return;

    for (ListNode* i = head; i; i = i->next) {
        for (ListNode* j = i->next; j; j = j->next) {
            if (isEarlier(j->data.birthday, i->data.birthday)) {
                std::swap(i->data, j->data);
            }
        }
    }
}

bool saveListToFile(ListNode* head, const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout) return false;
    while (head) {
        fout << head->data.surname << " "
            << head->data.name << " "
            << head->data.phone << " "
            << head->data.birthday.day << " "
            << head->data.birthday.month << " "
            << head->data.birthday.year << "\n";
        head = head->next;
    }
    return true;
}

bool loadListFromFile(ListNode*& head, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) return false;

    ListNode* newHead = nullptr;
    Note n;
    while (fin >> n.surname >> n.name >> n.phone
        >> n.birthday.day >> n.birthday.month >> n.birthday.year) {
        addNoteToList(newHead, n);
    }

    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    head = newHead;
    return true;
}

void freeList(ListNode*& head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void menu() {
    ListNode* head = nullptr;
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
            addNoteToList(head, inputNote());
            break;
        case 2:
            std::cout << "Enter phone to delete: ";
            std::cin >> phone;
            if (deleteNoteByPhone(head, phone))
                std::cout << "Deleted successfully.\n";
            else
                std::cout << "Phone not found.\n";
            break;
        case 3:
            std::cout << "Enter phone to search: ";
            std::cin >> phone;
            if (findNoteByPhone(head, phone, result))
                printNote(result);
            else
                std::cout << "No such contact found.\n";
            break;
        case 4:
            printList(head);
            break;
        case 5:
            sortListByBirthday(head);
            std::cout << "List sorted by birthday.\n";
            break;
        case 6:
            std::cout << "Enter filename to save: ";
            std::cin >> filename;
            if (saveListToFile(head, filename))
                std::cout << "Saved successfully.\n";
            else
                std::cout << "Failed to save file.\n";
            break;
        case 7:
            std::cout << "Enter filename to load: ";
            std::cin >> filename;
            if (loadListFromFile(head, filename))
                std::cout << "Loaded successfully.\n";
            else
                std::cout << "Failed to load file.\n";
            break;
        }

    } while (choice != 0);

    freeList(head);
    std::cout << "Goodbye!\n";
}

int main() {
    menu();
    return 0;
}
