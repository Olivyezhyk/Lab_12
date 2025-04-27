#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_04_rec/Lab_12_04_rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest7
{
    TEST_CLASS(UnitTest7)
    {
    public:

        TEST_METHOD(TestCreateListRecursive)
        {
            int arr[] = { 3, -1, 7, 0, -5, 12 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Node* head = create_list_recursive(arr, size);

            Assert::IsNotNull(head, L"List should not be null");

            Node* current = head;
            int index = 0;
            while (current) {
                Assert::AreEqual(arr[index], current->data, L"List element data mismatch");
                current = current->next;
                index++;
            }

            free_list_recursive(head);
        }

        TEST_METHOD(TestSumPositiveElementsRecursive)
        {
            int arr[] = { 3, -1, 7, 0, -5, 12 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Node* head = create_list_recursive(arr, size);

            int sum = sum_positive_elements_recursive(head);

            Assert::AreEqual(22, sum, L"Sum of positive elements is incorrect");

            free_list_recursive(head);
        }

        TEST_METHOD(TestFreeListRecursive)
        {
            int arr[] = { 1, 2, 3, 4 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Node* head = create_list_recursive(arr, size);

            Assert::IsNotNull(head, L"List should not be null before freeing");

            free_list_recursive(head);

            Assert::IsNull(head, L"List should be null after freeing");
        }

    };
}
