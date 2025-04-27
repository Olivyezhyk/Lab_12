#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <sstream>
#include <string>
#include "../Lab_12_12_tree/Lab_12_12_tree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest1)
    {
    public:

        void setInput(const std::string& input)
        {
            std::istringstream in(input);
            std::cin.rdbuf(in.rdbuf());
        }

        TEST_METHOD(TestInsertNode)
        {
            TreeNode* root = nullptr;
            Note n1 = { "John", "Doe", "123", {1, 1, 2000} };
            Note n2 = { "Jane", "Smith", "456", {2, 2, 1995} };
            Note n3 = { "Alice", "Johnson", "789", {3, 3, 1985} };

            insertNode(root, n1);
            insertNode(root, n2);
            insertNode(root, n3);

            Assert::AreEqual(root->data.phone.c_str(), "123");
            Assert::AreEqual(root->right->data.phone.c_str(), "456");
            Assert::AreEqual(root->right->right->data.phone.c_str(), "789");
        }
        TEST_METHOD(TestFindNodeByPhone)
        {
            TreeNode* root = nullptr;
            Note n1 = { "John", "Doe", "123", {1, 1, 2000} };
            Note n2 = { "Jane", "Smith", "456", {2, 2, 1995} };

            insertNode(root, n1);
            insertNode(root, n2);

            Note foundNote;
            bool result = findNodeByPhone(root, "123", foundNote);

            Assert::IsTrue(result);
            Assert::AreEqual(foundNote.phone.c_str(), "123");
            Assert::AreEqual(foundNote.surname.c_str(), "John");

        }

        TEST_METHOD(TestSaveAndLoad)
        {
            TreeNode* root = nullptr;
            Note n1 = { "John", "Doe", "123", {1, 1, 2000} };
            Note n2 = { "Jane", "Smith", "456", {2, 2, 1995} };

            insertNode(root, n1);
            insertNode(root, n2);

            std::string filename = "test_contacts.txt";
            bool saveResult = saveTreeToFile(root, filename);
            Assert::IsTrue(saveResult);

            TreeNode* newRoot = nullptr;
            bool loadResult = loadTreeFromFile(newRoot, filename);
            Assert::IsTrue(loadResult);

            Note loadedNote;
            bool found = findNodeByPhone(newRoot, "123", loadedNote);
            Assert::IsTrue(found);
            Assert::AreEqual(loadedNote.phone.c_str(), "123");
        }
    };
}
