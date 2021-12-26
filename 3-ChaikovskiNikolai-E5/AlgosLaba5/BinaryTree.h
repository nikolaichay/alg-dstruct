#pragma once
typedef struct tree_t {
	int val;
	int len;
	struct tree_t* left, * right;
}tree_t;
int TotalDigit(int val);
void FillLen(tree_t** tree);
tree_t* Insert(tree_t* tree, int val);
void FreeTree(tree_t* tree);
int PrintTree(tree_t* tree, int n);