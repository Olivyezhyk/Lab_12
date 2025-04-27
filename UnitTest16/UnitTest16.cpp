#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_12/Lab_12_12.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest16
{
    Note createNote(std::string surname, std::string name, std::string phone, int d, int m, int y) {
        return Note{ surname, name, phone, {d, m, y} };
    }

    TEST_CLASS(UnitTest16)
    {
    public:

        TEST_METHOD(TestAddNoteToList)
        {
            ListNode* head = nullptr;
            Note n = createNote("Smith", "John", "12345", 1, 1, 2000);
            addNoteToList(head, n);
            Assert::IsNotNull(head);
            Assert::AreEqual(std::string("Smith"), head->data.surname);
            Assert::AreEqual(std::string("12345"), head->data.phone);
            freeList(head);
        }

        TEST_METHOD(TestFindNoteByPhone_Found)
        {
            ListNode* head = nullptr;
            Note n1 = createNote("Smith", "John", "12345", 1, 1, 2000);
            Note n2 = createNote("Doe", "Jane", "67890", 2, 2, 1999);
            addNoteToList(head, n1);
            addNoteToList(head, n2);

            Note result;
            bool found = findNoteByPhone(head, "67890", result);
            Assert::IsTrue(found);
            Assert::AreEqual(std::string("Jane"), result.name);

            freeList(head);
        }

        TEST_METHOD(TestFindNoteByPhone_NotFound)
        {
            ListNode* head = nullptr;
            addNoteToList(head, createNote("Smith", "John", "12345", 1, 1, 2000));

            Note result;
            bool found = findNoteByPhone(head, "00000", result);
            Assert::IsFalse(found);

            freeList(head);
        }

        TEST_METHOD(TestDeleteNoteByPhone)
        {
            ListNode* head = nullptr;
            addNoteToList(head, createNote("Smith", "John", "12345", 1, 1, 2000));
            addNoteToList(head, createNote("Doe", "Jane", "67890", 2, 2, 1999));

            bool deleted = deleteNoteByPhone(head, "12345");
            Assert::IsTrue(deleted);

            Note result;
            bool found = findNoteByPhone(head, "12345", result);
            Assert::IsFalse(found);

            freeList(head);
        }
    };
}
