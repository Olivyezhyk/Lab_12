#include "pch.h"
#include "CppUnitTest.h"
#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>
#include "../Lab_12_06/Lab_12_06.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest9
{
    using WordQueue = queue<string>;

    void createQueueFromLine(const string& line, WordQueue& q) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            q.push(word);
        }
    }

    void concatenateQueues(const WordQueue& q1, const WordQueue& q2, WordQueue& result) {
        WordQueue temp = q1;
        while (!temp.empty()) {
            result.push(temp.front());
            temp.pop();
        }
        temp = q2;
        while (!temp.empty()) {
            result.push(temp.front());
            temp.pop();
        }
    }

    bool compareQueues(const WordQueue& q1, const WordQueue& q2) {
        WordQueue temp1 = q1;
        WordQueue temp2 = q2;

        while (!temp1.empty() && !temp2.empty()) {
            if (temp1.front() != temp2.front())
                return false;
            temp1.pop();
            temp2.pop();
        }
        return temp1.empty() && temp2.empty();
    }

    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(CreateQueueFromLineTest)
        {
            WordQueue queue;
            string line = "This is a test";
            createQueueFromLine(line, queue);

            Assert::AreEqual(queue.front().c_str(), "This");
            queue.pop();
            Assert::AreEqual(queue.front().c_str(), "is");
            queue.pop();
            Assert::AreEqual(queue.front().c_str(), "a");
            queue.pop();
            Assert::AreEqual(queue.front().c_str(), "test");
        }

        TEST_METHOD(ConcatenateQueuesTest)
        {
            WordQueue queue1, queue2, resultQueue;
            createQueueFromLine("Hello", queue1);
            createQueueFromLine("World", queue2);

            concatenateQueues(queue1, queue2, resultQueue);

            Assert::AreEqual(resultQueue.front().c_str(), "Hello");
            resultQueue.pop();
            Assert::AreEqual(resultQueue.front().c_str(), "World");
        }

        TEST_METHOD(CompareQueuesTest_Equal)
        {
            WordQueue queue1, queue2;
            createQueueFromLine("One two three", queue1);
            createQueueFromLine("One two three", queue2);

            bool result = compareQueues(queue1, queue2);
            Assert::IsTrue(result);
        }

        TEST_METHOD(CompareQueuesTest_Different)
        {
            WordQueue queue1, queue2;
            createQueueFromLine("One two three", queue1);
            createQueueFromLine("One two", queue2);

            bool result = compareQueues(queue1, queue2);
            Assert::IsFalse(result);
        }
    };
}
