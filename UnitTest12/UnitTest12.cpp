#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_09/Lab_12_09.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTests
{
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* addNode(TreeNode* root, int value) {
        if (root == nullptr) return new TreeNode(value);
        if (value < root->data) root->left = addNode(root->left, value);
        else root->right = addNode(root->right, value);
        return root;
    }

    int findMaxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int left = findMaxDepth(root->left);
        int right = findMaxDepth(root->right);
        return std::max(left, right) + 1;
    }

    void deleteLeafNode(TreeNode*& root, int value) {
        if (!root) return;
        if (value < root->data) deleteLeafNode(root->left, value);
        else if (value > root->data) deleteLeafNode(root->right, value);
        else if (!root->left && !root->right) {
            delete root;
            root = nullptr;
        }
    }

    void deleteTree(TreeNode*& root) {
        if (!root) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }

    TEST_CLASS(TreeUnitTest)
    {
    public:

        TEST_METHOD(TestAddAndDepth)
        {
            TreeNode* root = nullptr;
            root = addNode(root, 10);
            addNode(root, 5);
            addNode(root, 15);

            Assert::AreEqual(2, findMaxDepth(root));

            deleteTree(root);
        }

        TEST_METHOD(TestDeleteLeaf)
        {
            TreeNode* root = nullptr;
            root = addNode(root, 20);
            addNode(root, 10);
            addNode(root, 30);
            addNode(root, 5);

            deleteLeafNode(root, 5);

            Assert::IsNull(root->left->left);

            deleteTree(root);
        }

        TEST_METHOD(TestDepthOfEmptyTree)
        {
            TreeNode* root = nullptr;
            Assert::AreEqual(0, findMaxDepth(root));
        }
    };
}
