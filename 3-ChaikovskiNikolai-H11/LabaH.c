#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
	int key;
	int height;
	int data;
	struct node_t* left;
	struct node_t* right;
}node_t;

unsigned char Height(node_t* p) {
	return p ? p->height : 0;
}

int Bfactor(node_t* p) {
	return Height(p->right) - Height(p->left);
}

void FixHeight(node_t* p) {
	unsigned char hl = Height(p->left);
	unsigned char hr = Height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node_t* RotateRight(node_t* p) {
	node_t* q = p->left;
	p->left = q->right;
	q->right = p;
	FixHeight(p);
	FixHeight(q);
	return q;
}

node_t* RotateLeft(node_t* q) {
	node_t* p = q->right;
	q->right = p->left;
	p->left = q;
	FixHeight(q);
	FixHeight(p);
	return p;
}

node_t* Balance(node_t* p) {
	FixHeight(p);
	if (Bfactor(p) == 2) {
		if (Bfactor(p->right) < 0) {
			p->right = RotateRight(p->right);
		}
		return RotateLeft(p);
	}
	if (Bfactor(p) == -2) {
		if (Bfactor(p->left) > 0) {
			p->left = RotateLeft(p->left);
		}
		return RotateRight(p);
	}
	return p;
}

node_t* Insert(node_t* p, int key, int data) {
	if (!p) {
		p = (node_t*)malloc(sizeof(node_t));
		if (!p) {
			return NULL;
		}
		else {
			p->data = data;
			p->left = NULL;
			p->right = NULL;
			p->height = 1;
			p->key = key;
			return p;
		}
	}

	if (key < p->key) {
		p->left = Insert(p->left, key, data);
	}
	if (key >= p->key) {
		p->right = Insert(p->right, key, data);
	}
	return Balance(p);
}

node_t* InsertForTest(node_t* p, int data) {
	if (!p) {
		p = Insert(p, 0, data);
	}
	else {
		node_t* tmp = p;
		while (tmp->right) {
			tmp = tmp->right;
		}
		p = Insert(p, (tmp->key) + 1, data);
	}
	return p;
}

node_t* Findmin(node_t* p) {
	return p->left ? Findmin(p->left) : p;
}

node_t* Removemin(node_t* p) {
	if (!p->left) {
		return p->right;
	}
	p->left = Removemin(p->left);
	return Balance(p);
}

node_t* DeleteKey(node_t* p, int key) {
	if (!p) {
		return NULL;
	}
	if (key < p->key) {
		p->left = DeleteKey(p->left, key);
	}
	else if (key > p->key) {
		p->right = DeleteKey(p->right, key);
	}
	else {
		node_t* q = p->left;
		node_t* r = p->right;
		free(p);
		if (!r) {
			return q;
		}
		node_t* min = Findmin(r);
		min->right = Removemin(r);
		min->left = q;
		return Balance(min);
	}
	return Balance(p);
}

node_t* SearchData(node_t* p, int data) {
	if (!p) {
		return NULL;
	}
	if (data == p->data) {
		return p;
	}
	node_t* q = SearchData(p->left, data);
	if (q && q->data == data) {
		return q;
	}
	node_t* r = SearchData(p->right, data);
	if (r && r->data == data) {
		return r;
	}
	return NULL;
}

node_t* SearchKey(node_t* p, int k) {
	if (!p) {
		fprintf(stdout, "no\n");
		return NULL;
	}
	if (k == p->key) {
		fprintf(stdout, "yes\n");
		return p;
	}
	if (k < p->key) {
		return SearchKey(p->left, k);
	}
	else {
		return SearchKey(p->right, k);
	}
}

node_t* DeleteData(node_t* p, int data) {
	node_t* tmp = SearchData(p, data);
	if (!tmp) {
		return p;
	}
	int key = tmp->key;
	p = DeleteKey(p, key);
	return p;
}

void TreeDestroy(node_t* p) {
	if (p) {
		TreeDestroy(p->left);
		TreeDestroy(p->right);
		free(p);
	}
}

void UpdateKey(node_t* p, int new) {
	if (!p) {
		return;
	}
	p->key = p->key + new + 1;
	UpdateKey(p->left, new);
	UpdateKey(p->right, new);
}

void PrintTree(node_t* p, int level) {
	if (!p) {
		return;
	}
	PrintTree(p->left, level + 1);
	for (int i = 0; i < level; ++i) {
		printf(" ");
	}
	printf("%i,%i\n", p->key, p->data);
	PrintTree(p->right, level + 1);
	return;
}
node_t* Merge(node_t* p, node_t* q) {
	if (!p) {
		return q;
	}
	if (!q) {
		return p;
	}
	int k1 = 0;
	int k2 = 0;
	int k = 0;
	node_t* tmp = p;
	while (tmp->right) {
		tmp = tmp->right;
	}
	int len1 = tmp->key;
	tmp = q;
	while (tmp->right) {
		tmp = tmp->right;
	}
	int len2 = tmp->key;
	tmp = p;
	while (tmp->left) {
		tmp = tmp->left;
		k1++;
	}
	tmp = p;
	while (tmp->right) {
		tmp = tmp->right;
		k++;
	}
	k1 = k1 > k ? k1 : k;
	tmp = q;
	k = 0;
	while (tmp->left) {
		tmp = tmp->left;
		k2++;
	}
	tmp = q;
	while (tmp->right) {
		tmp = tmp->right;
		k++;
	}
	k2 = k2 > k ? k2 : k;
	if (k1 > k2) {
		UpdateKey(p, len2);
	}
	else {
		UpdateKey(q, len1);
		int k = k1;
		k1 = k2;
		k2 = k;
		tmp = p;
		p = q;
		q = tmp;
	}
	tmp = q;
	node_t* prev = NULL;
	while (tmp->right) {
		prev = tmp;
		tmp = tmp->right;
	}
	node_t* cur = tmp;
	prev->right = NULL;
	tmp = p;
	prev = NULL;
	while (k1 - k2 - 1 != 0) {
		prev = tmp;
		tmp = tmp->left;
		k1--;
	}
	cur->left = q;
	cur->right = tmp;
	prev->left = cur;
	prev = Balance(prev);
	p = Balance(p);
	return p;
}

int lab() {
	node_t* p = NULL;
	node_t* tmp;
	char command[16] = " ", ch;
	int data;
	while (fgets(command, 16, stdin)) {
		sscanf(command, "%c%i", &ch, &data);
		switch (ch) {
		case 'a':
			p = InsertForTest(p, data);
			break;
		case 'r':
			p = DeleteData(p, data);
			break;
		case 'f':
			tmp = SearchData(p, data);
			if (!tmp) {
				printf("no");
			}
			else {
				printf("yes");
			}
			break;
		default:
			TreeDestroy(p);
			return 0;
		}
	}
	TreeDestroy(p);
	return 0;
}
int main() {
	lab();
	return 0;
}
