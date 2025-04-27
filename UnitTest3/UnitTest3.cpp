#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_02_rec/Lab_12_02_rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{
    TEST_CLASS(UnitTest3)
    {
    public:

        TEST_METHOD(TestInsertAfterValue)
        {
            int arr[] = { 1, 5, 2, 5, 3 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Node* head = createList(arr, size);

            insertAfterValue(head, 5, 99);

            int expected[] = { 1, 5, 99, 2, 5, 99, 3 };
            int expectedSize = sizeof(expected) / sizeof(expected[0]);

            Node* current = head;
            for (int i = 0; i < expectedSize; ++i) {
                Assert::IsNotNull(current, L"List ended prematurely");
                Assert::AreEqual(expected[i], current->data, L"Values differ at position", LINE_INFO());
                current = current->next;
            }

            Assert::IsNull(current, L"List is longer than expected");

            freeList(head);
        }

    };
}
