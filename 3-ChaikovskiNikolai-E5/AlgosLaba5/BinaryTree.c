#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTree.h"
#pragma warning(disable : 4996)
int TotalDigit(int num) {
	int count = 0;
	if (num == 0) {
		return 1;
	}
	else {
		if (num < 0) {
			count++;
		}
		do {
			count++;
			num = abs(num) / 10;
		} while (abs(num) > 0);
		return count;
	}
}
tree_t* Insert(tree_t* tree, int val) {
	if (!tree) {
		tree = (tree_t*)malloc(sizeof(tree_t));
		if (!tree) {
			printf("Error in memory.");
			return NULL;
		}
		tree->val = val;
		tree->len = 0;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	else {
		if (val <= tree->val) {
			tree->left = Insert(tree->left, val);
			if (!tree->left) {
				printf("Not enough memory. The element %d was not added", val);
				return tree;
			}
		}
		else if (val > tree->val) {
			tree->right = Insert(tree->right, val);
			if (!tree->right) {
				printf("Not enough memory. The element %d was not added", val);
				return tree;
			}
		}
	}
	return tree;
}
void FreeTree(tree_t* tree) {
	if (tree) {
		FreeTree(tree->left);
		FreeTree(tree->right);
		free(tree);
	}
}
int PrintTree(tree_t* tree, int n) {
	int i;
	if (!tree) {
		return 0;
	}
	else {
		PrintTree(tree->right, n + 5);
		for (i = 0; i < n; i++) {
			putchar(' ');
		}
		printf("%d\n", tree->val);
		for (i = 0; i < n; i++) {
			putchar(' ');
		}
		printf("%d\n", tree->len);
		PrintTree(tree->left, n + 5);
		return 1;
	}
}
void FillLen(tree_t* tree) {
	int tmpRight = 0, tmpLeft = 0;
	if (!tree) {
		return;
	}
	if (!tree->left && !tree->right) {
		tree->len = TotalDigit(tree->val);
		return;
	}
	if (tree->left) {
		FillLen(tree->left);
		tmpLeft = tree->left->len;
		tree->len = tmpLeft;
		if (!tree->right) {
			tree->len += TotalDigit(tree->val);
		}
	}
	if (tree->right) {
		FillLen(tree->right);
		tmpRight = tree->right->len + TotalDigit(tree->val);
		tree->len += tmpRight;
	}
}