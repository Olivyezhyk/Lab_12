#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_10/Lab_12_10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest13
{
	TEST_CLASS(UnitTest13)
	{
	public:

		TEST_METHOD(TestAddAndSearch)
		{
			Node* root = nullptr;
			root = addNode(root, 10);
			root = addNode(root, 5);
			root = addNode(root, 15);

			Assert::IsNotNull(searchNode(root, 10));
			Assert::IsNotNull(searchNode(root, 5));
			Assert::IsNotNull(searchNode(root, 15));
			Assert::IsNull(searchNode(root, 100));
		}

		TEST_METHOD(TestDeleteNode)
		{
			Node* root = nullptr;
			root = addNode(root, 10);
			root = addNode(root, 5);
			root = addNode(root, 15);
			root = deleteNode(root, 10);

			Assert::IsNull(searchNode(root, 10));
			Assert::IsNotNull(searchNode(root, 5));
			Assert::IsNotNull(searchNode(root, 15));
		}

		TEST_METHOD(TestCountNodesAtLevel)
		{
			Node* root = nullptr;
			root = addNode(root, 10);
			root = addNode(root, 5);
			root = addNode(root, 15);
			root = addNode(root, 3);
			root = addNode(root, 7);

			Assert::AreEqual(1, countNodesAtLevel(root, 0));
			Assert::AreEqual(2, countNodesAtLevel(root, 1));
			Assert::AreEqual(2, countNodesAtLevel(root, 2));
			Assert::AreEqual(0, countNodesAtLevel(root, 3));
		}

		TEST_METHOD(TestFindMin)
		{
			Node* root = nullptr;
			root = addNode(root, 10);
			root = addNode(root, 5);
			root = addNode(root, 1);
			root = addNode(root, 7);

			Node* minNode = findMin(root);
			Assert::AreEqual(1, minNode->data);
		}
	};
}
