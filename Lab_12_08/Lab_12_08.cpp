#include <iostream>
#include <string>
using namespace std;

enum AccessType { READ, WRITE, DENIED };

struct DNode {
    string name;
    int size;
    string date;
    AccessType access;
    DNode* prev;
    DNode* next;
};

struct SNode {
    string name;
    int size;
    string date;
    SNode* next;
};

void appendToDList(DNode*& head, DNode*& tail, const string& name, int size, const string& date, AccessType access) {
    DNode* newNode = new DNode{ name, size, date, access, tail, nullptr };
    if (!head) head = tail = newNode;
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void printDList(const DNode* head, const string& label) {
    cout << label << ":\n";
    while (head) {
        cout << "File: " << head->name
            << ", Size: " << head->size
            << ", Date: " << head->date
            << ", Access: ";
        switch (head->access) {
        case READ: cout << "READ"; break;
        case WRITE: cout << "WRITE"; break;
        case DENIED: cout << "DENIED"; break;
        }
        cout << endl;
        head = head->next;
    }
    cout << endl;
}

void appendToSList(SNode*& head, const string& name, int size, const string& date) {
    SNode* newNode = new SNode{ name, size, date, nullptr };
    if (!head) head = newNode;
    else {
        SNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void filterDeniedAccess(const DNode* dHead, SNode*& sHead, int& deniedCount) {
    deniedCount = 0;
    while (dHead) {
        if (dHead->access == DENIED) {
            appendToSList(sHead, dHead->name, dHead->size, dHead->date);
            deniedCount++;
        }
        dHead = dHead->next;
    }
}

void printSList(const SNode* head, const string& label) {
    cout << label << ":\n";
    while (head) {
        cout << "File: " << head->name
            << ", Size: " << head->size
            << ", Date: " << head->date << endl;
        head = head->next;
    }
    cout << endl;
}

void deleteDList(DNode*& head) {
    while (head) {
        DNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void deleteSList(SNode*& head) {
    while (head) {
        SNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    DNode* dHead = nullptr;
    DNode* dTail = nullptr;

    int n;
    cout << "How many files to input? ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string name, date;
        int size, accessInt;
        cout << endl;
        cout << "File " << i + 1 << " name: ";
        cin >> name;
        cout << "Size: ";
        cin >> size;
        cout << "Creation date: ";
        cin >> date;
        cout << "Access (0=READ, 1=WRITE, 2=DENIED): ";
        cin >> accessInt;
        appendToDList(dHead, dTail, name, size, date, static_cast<AccessType>(accessInt));
    }

    cout << endl;
    printDList(dHead, "Original Doubly-Linked List");

    SNode* deniedList = nullptr;
    int deniedCount = 0;

    filterDeniedAccess(dHead, deniedList, deniedCount);

    printSList(deniedList, "Filtered Singly-Linked List (DENIED access)");
    cout << "Number of files with DENIED access: " << deniedCount << endl;

    deleteDList(dHead);
    deleteSList(deniedList);

    return 0;
}
