#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_01/Lab_12_01.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    struct Elem {
        Elem* link1;
        Elem* link2;
        int info;
    };

    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestStructureFromMain)
        {
            Elem* p = new Elem;
            p->info = 1;

            p->link1 = new Elem;
            p->link1->info = 2;

            p->link2 = new Elem;
            p->link2->info = 4;

            p->link1->link1 = p;
            p->link1->link2 = new Elem;
            p->link1->link2->info = 3;

            p->link1->link2->link1 = p->link1;
            p->link1->link2->link2 = p->link2;

            p->link2->link1 = p;
            p->link2->link2 = p->link1;

            Assert::AreEqual(1, p->info);
            Assert::AreEqual(2, p->link1->info);
            Assert::AreEqual(3, p->link1->link2->info);
            Assert::AreEqual(4, p->link1->link2->link2->info);

            Assert::IsTrue(p->link1->link1 == p);
            Assert::IsTrue(p->link1->link2->link1 == p->link1);
            Assert::IsTrue(p->link1->link2->link2 == p->link2);

            delete p->link1->link2;
            delete p->link1;
            delete p->link2;
            delete p;
        }
    };
}
