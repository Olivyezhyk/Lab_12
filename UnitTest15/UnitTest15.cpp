#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_11_tree/Lab_12_11_tree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest15
{
	TEST_CLASS(UnitTest15)
	{
	public:
		TEST_METHOD(TestFindHelpItem)
		{
			HelpItem* root = nullptr;

			HelpItem* item = new HelpItem;
			item->term = "Binary Tree";
			item->linesCount = 1;
			item->explanation[0] = "A tree data structure.";
			item->left = item->right = nullptr;
			root = item;

			HelpItem* found = findHelpItem(root, "Binary Tree");
			Assert::IsNotNull(found);
			Assert::AreEqual(std::string("A tree data structure."), found->explanation[0]);

			HelpItem* notFound = findHelpItem(root, "Hash Table");
			Assert::IsNull(notFound);

			freeTree(root);
		}
	};
}
