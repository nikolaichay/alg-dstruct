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
	if (p->key == key) {
		return p;
	}
	if (key < p->key) {
		p->left = Insert(p->left, key, data);
	}
	if (key > p->key) {
		p->right = Insert(p->right, key, data);
	}
	return Balance(p);
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
node_t* DeleteData(node_t* p, int data) {
	node_t* tmp = SearchData(p, data);
	if (!tmp) {
		return p;
	}
	int key = tmp->key;
	p = DeleteKey(p, key);
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
	p->key = p->key + new;
	UpdateKey(p->left, new);
	UpdateKey(p->right, new);
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
	node_t* tmp = p;
	while (!tmp->right) {
		tmp = tmp->right;
	}
	int len1 = tmp->key;
	tmp = p;
	while (!tmp->left) {
		tmp = tmp->left;
		k1++;
	}
	tmp = q;
	while (!tmp->left) {
		tmp = tmp->left;
		k2++;
	}
	tmp = q;
	while (!tmp->right) {
		tmp = tmp->right;
	}
	int len2 = tmp->key;
	if (k1 > k2) {
		UpdateKey(q, len1);
	}
	else {
		UpdateKey(p, len2);
		int k = k1;
		k2 = k1;
		k1 = k;
		tmp = p;
		p = q;
		q = tmp;
	}
	tmp = q;
	while (!tmp->right) {
		tmp = tmp->right;
	}
	node_t* cur = tmp;
	DeleteKey(q, cur->key);
	tmp = p;
	node_t* prev = NULL;
	while (k1 - k2 != 0) {
		prev = tmp;
		tmp->left;
		k1--;
	}
	cur->left = q;
	cur->right = tmp;
	prev->left = cur;
	Balance(prev);
	return p;
}


int test() {
	node_t* p = NULL;
	char command[16] = " ", ch;
	int key, data;
	while (fgets(command, 16, stdin)) { // Example of an input string a 1 3
		sscanf(command, "%c%i%i\n", &ch, &data, &key);
		switch (ch) {
		case 'a':
			p = Insert(p, key, data);
			break;
		case 'r':
			p = DeleteData(p, data);
			break;
		case 'f':
			SearchKey(p, key);
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
	test();
	return 0;
}