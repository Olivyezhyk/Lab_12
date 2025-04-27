#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_08/Lab_12_08.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest11
{
	TEST_CLASS(UnitTest11)
	{
	public:
		
        TEST_METHOD(TestFilterDeniedAccess)
        {
            DNode* head = nullptr;
            DNode* tail = nullptr;
            appendToDList(head, tail, "file1.txt", 100, "2023-01-01", READ);
            appendToDList(head, tail, "file2.txt", 200, "2023-01-02", DENIED);
            appendToDList(head, tail, "file3.txt", 300, "2023-01-03", WRITE);
            appendToDList(head, tail, "file4.txt", 400, "2023-01-04", DENIED);

            SNode* deniedList = nullptr;
            int deniedCount = 0;
            filterDeniedAccess(head, deniedList, deniedCount);

            Assert::AreEqual(2, deniedCount);

            Assert::IsNotNull(deniedList);
            Assert::AreEqual(string("file2.txt"), deniedList->name);
            Assert::IsNotNull(deniedList->next);
            Assert::AreEqual(string("file4.txt"), deniedList->next->name);
            Assert::IsNull(deniedList->next->next);

            deleteDList(head);
            deleteSList(deniedList);
        }

	};
}
