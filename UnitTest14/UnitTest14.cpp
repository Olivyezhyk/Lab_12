#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "../Lab_12_11/Lab_12_11.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest14
{
    TEST_CLASS(UnitTest14)
    {
    public:
        HelpItem* head;

        TEST_METHOD_INITIALIZE(Init)
        {
            head = nullptr;
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
            while (head) {
                HelpItem* temp = head;
                head = head->next;
                delete temp;
            }
        }

        void createTestList()
        {
            HelpItem* a = new HelpItem{ "Zebra", {"Animal"}, 1, nullptr };
            HelpItem* b = new HelpItem{ "Apple", {"Fruit"}, 1, nullptr };
            HelpItem* c = new HelpItem{ "Lemon", {"Sour fruit"}, 1, nullptr };

            a->next = b;
            b->next = c;
            head = a;
        }

        TEST_METHOD(Test_FindHelpItem)
        {
            createTestList();
            auto found = findHelpItem(head, "Apple");
            Assert::IsNotNull(found);
            Assert::AreEqual(std::string("Apple"), found->term);

            auto notFound = findHelpItem(head, "Banana");
            Assert::IsNull(notFound);
        }

        TEST_METHOD(Test_RemoveHelpItem)
        {
            createTestList();
            removeHelpItem(head, "Apple");
            auto result = findHelpItem(head, "Apple");
            Assert::IsNull(result);

            removeHelpItem(head, "NonExisting");
            Assert::IsNotNull(head);
        }

        TEST_METHOD(Test_SortHelpList)
        {
            createTestList();
            sortHelpList(head);

            Assert::AreEqual(std::string("Apple"), head->term);
            Assert::AreEqual(std::string("Lemon"), head->next->term);
            Assert::AreEqual(std::string("Zebra"), head->next->next->term);
        }

        TEST_METHOD(Test_AddHelpItem_Manually)
        {
            HelpItem* newItem = new HelpItem{
                "C++", {"A programming language", "Used for systems programming"}, 2, nullptr
            };

            head = newItem;
            Assert::AreEqual(std::string("C++"), head->term);
            Assert::AreEqual(2, head->linesCount);
            Assert::AreEqual(std::string("Used for systems programming"), head->explanation[1]);
        }
    };
}

