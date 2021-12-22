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
			printf("error in memory");
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
				return NULL;
			}
		}
		else if (val > tree->val) {
			tree->right = Insert(tree->right, val);
			if (!tree->right) {
				return NULL;
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
void PrintTree(tree_t* tree, int n) {
	int i;
	if (tree) {
		PrintTree(tree->right, n + 3);
		for (i = 0; i < n; i++) {
			putchar(' ');
		}
		printf("%d\n", tree->val);
		for (i = 0; i < n; i++) {
			putchar(' ');
		}
		printf("%d\n", tree->len);
		PrintTree(tree->left, n + 3);

	}
}
void FillLen(tree_t** tree) {
	int fillRes = 0, curWidth = 0, tmp = 0, curVal = 0, tmpRight = 0, tmpLeft = 0;
	if (!tree) {
		return;
	}
	if (!(*tree)->left && !(*tree)->right) {
		curVal = TotalDigit((*tree)->val);
		curWidth = TotalDigit(curVal + tmp);
		fillRes = curVal + curWidth;
		if (TotalDigit(fillRes) > TotalDigit(curWidth)) {
			fillRes++;
		}
		(*tree)->len = fillRes;
		return;
	}
	if ((*tree)->left) {
		FillLen(&((*tree)->left));
		tree_t* tmpTree = *tree;
		tmpTree = tmpTree->left;
		tmp = tmpTree->len;
		curVal = TotalDigit((*tree)->val);
		curWidth = TotalDigit(curVal + tmp);
		fillRes = tmp;
		if (!(*tree)->right) {
			fillRes = tmp + curVal + curWidth;
		}
	}
	if ((*tree)->right) {
		FillLen(&((*tree)->right));
		tree_t* tmpTree = *tree;
		tmpTree = tmpTree->right;
		tmp = tmpTree->len;
		curVal = TotalDigit((*tree)->val);
		curWidth = TotalDigit(curVal + tmp + fillRes);
		fillRes += tmp + curVal + curWidth;
	}
	if ((*tree)->right) {
		tmpRight = (*tree)->right->len;
	}
	if ((*tree)->left) {
		tmpLeft = (*tree)->left->len;
	}
	if (TotalDigit(fillRes) > TotalDigit(tmpRight + tmpLeft + curVal)) {
		fillRes++;
	}
	(*tree)->len = fillRes;
}