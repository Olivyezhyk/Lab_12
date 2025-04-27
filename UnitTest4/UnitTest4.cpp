#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_03_iter/Lab_12_03_iter.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4
{
	TEST_CLASS(UnitTest4)
	{
	public:
		
        TEST_METHOD(TestFilterListBySign)
        {
            int arr[] = { 3, -1, 4, -5, 2, -6, 0, 8 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Node* head = createList(arr, size);

            Node* positiveList = filterListBySign(head, true);
            int expectedPositive[] = { 3, 4, 2, 8 };
            int expectedPositiveSize = sizeof(expectedPositive) / sizeof(expectedPositive[0]);

            Node* current = positiveList;
            for (int i = 0; i < expectedPositiveSize; ++i) {
                Assert::IsNotNull(current, L"List ended prematurely");
                Assert::AreEqual(expectedPositive[i], current->data, L"Values differ at position", LINE_INFO());
                current = current->next;
            }
            Assert::IsNull(current, L"Positive list is longer than expected");

            Node* negativeList = filterListBySign(head, false);
            int expectedNegative[] = { -1, -5, -6 };
            int expectedNegativeSize = sizeof(expectedNegative) / sizeof(expectedNegative[0]);

            current = negativeList;
            for (int i = 0; i < expectedNegativeSize; ++i) {
                Assert::IsNotNull(current, L"List ended prematurely");
                Assert::AreEqual(expectedNegative[i], current->data, L"Values differ at position", LINE_INFO());
                current = current->next;
            }
            Assert::IsNull(current, L"Negative list is longer than expected");

            deleteList(head);
            deleteList(positiveList);
            deleteList(negativeList);
        }
	};
}
