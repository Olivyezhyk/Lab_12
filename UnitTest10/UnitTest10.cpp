#include "pch.h"
#include "CppUnitTest.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "../Lab_12_07/Lab_12_07.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
    struct Node {
        int data;
        Node* next;
    };

    void appendToList(Node*& head, int value) {
        Node* newNode = new Node{ value, nullptr };
        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void printList(const Node* head, const string& label) {
        cout << label << ": ";
        while (head) {
            cout << head->data << " -> ";
            head = head->next;
        }
        cout << "NULL" << endl;
    }

    int getListLength(const Node* head) {
        int count = 0;
        while (head) {
            count++;
            head = head->next;
        }
        return count;
    }

    void reverseList(Node*& head) {
        Node* prev = nullptr;
        Node* current = head;
        while (current) {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    bool isFibonacci(int n, const int* fibArray, int size) {
        for (int i = 0; i < size; ++i) {
            if (fibArray[i] == n) return true;
        }
        return false;
    }

    int generateFibonacciArray(int maxVal, int* fibArray, int maxSize) {
        int a = 0, b = 1;
        int count = 0;
        while (a <= maxVal && count < maxSize) {
            fibArray[count++] = a;
            int temp = a + b;
            a = b;
            b = temp;
        }
        return count;
    }

    void findFibonacciNumbers(const Node* head, int* foundFib, int& foundCount) {
        int maxValue = 0;
        const Node* temp = head;
        while (temp) {
            if (temp->data > maxValue) maxValue = temp->data;
            temp = temp->next;
        }

        const int MAX_FIB_SIZE = 50;
        int fibArray[MAX_FIB_SIZE];
        int fibCount = generateFibonacciArray(maxValue, fibArray, MAX_FIB_SIZE);

        foundCount = 0;
        temp = head;
        while (temp) {
            if (isFibonacci(temp->data, fibArray, fibCount)) {
                foundFib[foundCount++] = temp->data;
            }
            temp = temp->next;
        }
    }

    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(AppendToListTest)
        {
            Node* list = nullptr;
            appendToList(list, 1);
            appendToList(list, 2);
            appendToList(list, 3);

            Assert::AreEqual(getListLength(list), 3);
        }

        TEST_METHOD(GetListLengthTest)
        {
            Node* list = nullptr;
            appendToList(list, 1);
            appendToList(list, 2);
            appendToList(list, 3);

            Assert::AreEqual(getListLength(list), 3);
        }

        TEST_METHOD(ReverseListTest)
        {
            Node* list = nullptr;
            appendToList(list, 1);
            appendToList(list, 2);
            appendToList(list, 3);

            reverseList(list);

            Assert::AreEqual(list->data, 3);
            Assert::AreEqual(list->next->data, 2);
            Assert::AreEqual(list->next->next->data, 1);
        }

        TEST_METHOD(FindFibonacciNumbersTest)
        {
            Node* list = nullptr;
            appendToList(list, 3);
            appendToList(list, 5);
            appendToList(list, 7);
            appendToList(list, 13);

            const int MAX_FOUND = 100;
            int foundFib[MAX_FOUND];
            int foundCount = 0;

            findFibonacciNumbers(list, foundFib, foundCount);

            Assert::AreEqual(foundCount, 3);
            Assert::AreEqual(foundFib[0], 3);
            Assert::AreEqual(foundFib[1], 5);
            Assert::AreEqual(foundFib[2], 13);
        }
    };
}
