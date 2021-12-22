#include "pch.h"
#include "BinaryTree.h"
#include "BinaryTree.c"
TEST(FunctionalTest, OnlyRoot) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 111111111);
	FillLen(&tree);
	EXPECT_EQ(tree->len, 11);
	PrintTree(tree, 1);
	FreeTree(tree);
}

TEST(FunctionalTest, TreeWithZero) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 0);
	FillLen(&tree);
	EXPECT_EQ(tree->len, 2);
	FreeTree(tree);
}

TEST(FunctionalTest, CheckResult) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 51);
	tree = Insert(tree, 20);
	tree = Insert(tree, 1);
	tree = Insert(tree, 43);
	tree = Insert(tree, 66);
	tree = Insert(tree, 60);
	FillLen(&tree);
	EXPECT_EQ(tree->left->left->len, 2);
	EXPECT_EQ(tree->left->right->len, 3);
	EXPECT_EQ(tree->left->len, 8);
	EXPECT_EQ(tree->right->left->len, 3);
	EXPECT_EQ(tree->right->len, 6);
	EXPECT_EQ(tree->len, 18);
	PrintTree(tree, 1);
	FreeTree(tree);
}

TEST(FunctionalTest, NegativeElements) {
	tree_t* tree = nullptr;
	tree = Insert(tree, -12);
	tree = Insert(tree, -10);
	tree = Insert(tree, -1);
	tree = Insert(tree, -11);
	tree = Insert(tree, -14);
	FillLen(&tree);
	EXPECT_EQ(tree->left->len, 4);
	EXPECT_EQ((tree->right)->right->len, 3);
	EXPECT_EQ(tree->right->left->len, 4);
	EXPECT_EQ(tree->right->len, 12);
	EXPECT_EQ(tree->len, 21);
	PrintTree(tree, 1);
	FreeTree(tree);
}

TEST(FunctionalTest, ElementsWithOverDigitInTheRoot) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 99);
	tree = Insert(tree, 11);
	tree = Insert(tree, 413);
	FillLen(&tree);
	EXPECT_EQ(tree->right->len, 4);
	EXPECT_EQ(tree->left->len, 3);
	EXPECT_EQ(tree->len, 11);
	PrintTree(tree, 1);
	FreeTree(tree);
}