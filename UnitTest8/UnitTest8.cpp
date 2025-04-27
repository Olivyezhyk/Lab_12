#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_05/Lab_12_05.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(StackTests)
    {
    public:

        TEST_METHOD(TestCreateStack)
        {
            Stack st = create_stack(5);
            Assert::AreEqual(st.capacity, 5);
            Assert::IsTrue(stack_is_empty(st));
            destroy_stack(st);
        }

        TEST_METHOD(TestPushPop)
        {
            Stack st = create_stack(5);
            push(st, 10);
            push(st, 20);
            Assert::AreEqual(pop(st), 20);
            Assert::AreEqual(pop(st), 10);
            destroy_stack(st);
        }

        TEST_METHOD(TestCompareStacks_Equal)
        {
            int arr1[] = { 1, 2, 3 };
            int arr2[] = { 1, 2, 3 };
            Stack st1 = create_stack(3);
            Stack st2 = create_stack(3);

            for (int i = 0; i < 3; ++i) {
                push(st1, arr1[i]);
                push(st2, arr2[i]);
            }

            Assert::IsTrue(compare_stacks(st1, st2));
            destroy_stack(st1);
            destroy_stack(st2);
        }

        TEST_METHOD(TestCompareStacks_Different)
        {
            int arr1[] = { 1, 2, 3 };
            int arr2[] = { 4, 5, 6 };
            Stack st1 = create_stack(3);
            Stack st2 = create_stack(3);

            for (int i = 0; i < 3; ++i) {
                push(st1, arr1[i]);
                push(st2, arr2[i]);
            }

            Assert::IsFalse(compare_stacks(st1, st2));
            destroy_stack(st1);
            destroy_stack(st2);
        }
    };
}
