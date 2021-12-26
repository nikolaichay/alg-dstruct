#include "pch.h"
#include "BinaryTree.h"
#include "BinaryTree.c"
int Compare(char const* name_out, char const* name_expected) {
	FILE* out = fopen(name_out, "r");
	if (!out) {
		perror("");
		return -1;
	}
	FILE* expected = fopen(name_expected, "r");
	if (!expected) {
		perror("");
		fclose(out);
		return -1;
	}
	fseek(out, 0, SEEK_END);
	fseek(expected, 0, SEEK_END);
	if (ftell(out) != ftell(expected)) {
		fclose(out);
		fclose(expected);
		return 0;
	}
	fseek(out, 0, SEEK_SET);
	fseek(expected, 0, SEEK_SET);
	int val = -1;
	int exp = -1;
	while ((fscanf(out, "%d ", &val) > 0) && (fscanf(expected, "%d ", &exp) > 0)) {
		if (val != exp) {
			fclose(out);
			fclose(expected);
			return 0;
		}
	}
	fclose(out);
	fclose(expected);
	return 1;
}
TEST(FunctionalTest, OnlyRoot) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 111111111);
	if (!tree) {
		printf("Not enough memory");
		ASSERT_TRUE(tree);
	}
	FillLen(tree);
	EXPECT_EQ(tree->len, 9);
	FILE* out = fopen("Result1.txt", "w");
	if (!out) {
		FreeTree(tree);
		FAIL();
	}
	int check = PrintTree(tree, 1, out);
	FreeTree(tree);
	EXPECT_EQ(check, 1);
	fclose(out);
	check = 0;
	check = Compare("Result1.txt", "Answer1.txt");
	EXPECT_EQ(check, 1);
}

TEST(FunctionalTest, TreeWithZero) {
	tree_t* tree = nullptr;
	tree = Insert(tree, 0);
	if (!tree) {
		printf("Not enough memory");
		ASSERT_TRUE(tree);
	}
	FillLen(tree);
	FILE* out = fopen("Result2.txt", "w");
	if (!out) {
		FreeTree(tree);
		FAIL();
	}
	int check = PrintTree(tree, 1, out);
	FreeTree(tree);
	EXPECT_EQ(check, 1);
	fclose(out);
	check = 0;
	check = Compare("Result2.txt", "Answer2.txt");
	EXPECT_EQ(check, 1);
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
	FILE* out = fopen("Result3.txt", "w");
	if (!out) {
		FreeTree(tree);
		FAIL();
	}
	int check = PrintTree(tree, 1, out);
	FreeTree(tree);
	EXPECT_EQ(check, 1);
	fclose(out);
	check = 0;
	check = Compare("Result3.txt", "Answer3.txt");
	EXPECT_EQ(check, 1);
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
	FILE* out = fopen("Result4.txt", "w");
	if (!out) {
		FreeTree(tree);
		FAIL();
	}
	int check = PrintTree(tree, 1, out);
	FreeTree(tree);
	EXPECT_EQ(check, 1);
	fclose(out);
	check = 0;
	check = Compare("Result4.txt", "Answer4.txt");
	EXPECT_EQ(check, 1);
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
	FILE* out = fopen("Result5.txt", "w");
	if (!out) {
		FreeTree(tree);
		FAIL();
	}
	int check = PrintTree(tree, 1, out);
	FreeTree(tree);
	EXPECT_EQ(check, 1);
	fclose(out);
	check = 0;
	check = Compare("Result5.txt", "Answer5.txt");
	EXPECT_EQ(check, 1);
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
	FILE* out = fopen("Result6.txt", "w");
	if (!out) {
		FreeTree(tree);
		FAIL();
	}
	int check = PrintTree(tree, 1, out);
	FreeTree(tree);
	EXPECT_EQ(check, 1);
	fclose(out);
	check = 0;
	check = Compare("Result6.txt", "Answer6.txt");
	EXPECT_EQ(check, 1);
}