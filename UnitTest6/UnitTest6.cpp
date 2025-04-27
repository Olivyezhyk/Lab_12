#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_04_iter/Lab_12_04_iter.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest6
{
	TEST_CLASS(UnitTest6)
	{
	public:
		
		TEST_METHOD(TestSumPositiveElements)
        {
            int arr[] = { 3, -1, 7, 0, -5, 12 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Node* head = create_list(arr, size);

            int sum = sum_positive_elements(head);

            Assert::AreEqual(22, sum, L"Sum of positive elements is incorrect");

            free_list(head);
        }

        TEST_METHOD(TestCreateList)
        {
            int arr[] = { 3, -1, 7, 0, -5, 12 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Node* head = create_list(arr, size);

            Assert::IsNotNull(head, L"List should not be null");

            Node* current = head;
            int index = 0;
            do {
                Assert::AreEqual(arr[index], current->data, L"List element data mismatch");
                current = current->next;
                index++;
            } while (current != head);

            free_list(head);
        }

        TEST_METHOD(TestFreeList)
        {
            int arr[] = { 1, 2, 3, 4 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Node* head = create_list(arr, size);

            Assert::IsNotNull(head, L"List should not be null before freeing");

            free_list(head);

            Assert::IsNull(head, L"List should be null after freeing");
        }

	};
}
