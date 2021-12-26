#include "pch.h"
#include "BinaryTree.h"
#include "BinaryTree.c"
TEST(FunctionalTest, OnlyRoot) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 111111111);
	if (!tree) {
		printf("Not enough memory");
		ASSERT_TRUE(tree);
	}
	FillLen(tree);
	EXPECT_EQ(tree->len, 9);
	int check = PrintTree(tree, 1);
	EXPECT_EQ(check, 1);
	FreeTree(tree);
}

TEST(FunctionalTest, TreeWithZero) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 0);
	if (!tree) {
		printf("Not enough memory");
		ASSERT_TRUE(tree);
	}
	FillLen(tree);
	int check = PrintTree(tree, 1);
	EXPECT_EQ(check, 1);
	FreeTree(tree);
}

TEST(FunctionalTest, CheckResult) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 51);
	if (!tree) {
		printf("Not enough memory");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 20);
	tree = Insert(tree, 1);
	tree = Insert(tree, 43);
	tree = Insert(tree, 66);
	tree = Insert(tree, 60);
	FillLen(tree);
	EXPECT_EQ(tree->left->left->len, 1);
	EXPECT_EQ(tree->left->right->len, 2);
	EXPECT_EQ(tree->left->len, 5);
	EXPECT_EQ(tree->right->left->len, 2);
	EXPECT_EQ(tree->right->len, 4);
	EXPECT_EQ(tree->len, 11);
	int check = PrintTree(tree, 1);
	EXPECT_EQ(check, 1);
	FreeTree(tree);
}

TEST(FunctionalTest, NegativeElements) {
	tree_t* tree = nullptr;
	tree = Insert(tree, -12);
	if (!tree) {
		printf("Not enough memory");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, -10);
	tree = Insert(tree, -1);
	tree = Insert(tree, -11);
	tree = Insert(tree, -14);
	FillLen(tree);
	EXPECT_EQ(tree->left->len, 3);
	EXPECT_EQ((tree->right)->right->len, 2);
	EXPECT_EQ(tree->right->left->len, 3);
	EXPECT_EQ(tree->right->len, 8);
	EXPECT_EQ(tree->len, 14);
	int check = PrintTree(tree, 1);
	EXPECT_EQ(check, 1);
	FreeTree(tree);
}

TEST(FunctionalTest, ElementsWithOverDigitInTheRoot) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 99);
	if (!tree) {
		printf("Not enough memory");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 11);
	tree = Insert(tree, 413);
	FillLen(tree);
	EXPECT_EQ(tree->right->len, 3);
	EXPECT_EQ(tree->left->len, 2);
	EXPECT_EQ(tree->len, 7);
	int check = PrintTree(tree, 1);
	EXPECT_EQ(check, 1);
	FreeTree(tree);
}
TEST(FunctionalTest, NegativeAndPositiveElements) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 12);
	if (!tree) {
		printf("Not enough memory");
		ASSERT_TRUE(tree);
	}
	tree = Insert(tree, 5);
	tree = Insert(tree, -10);
	tree = Insert(tree, 8);
	tree = Insert(tree, 14);
	FillLen(tree);
	EXPECT_EQ(tree->left->len, 5);
	EXPECT_EQ(tree->right->len, 2);
	EXPECT_EQ(tree->left->right->len, 1);
	EXPECT_EQ(tree->left->left->len, 3);
	EXPECT_EQ(tree->len, 9);
	int check = PrintTree(tree, 1);
	EXPECT_EQ(check, 1);
	FreeTree(tree);
}