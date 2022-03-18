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
		if (Bfactor(p->right) < 0)
			p->right = RotateRight(p->right);
		return RotateLeft(p);
	}
	if (Bfactor(p) == -2) {
		if (Bfactor(p->left) > 0)
			p->left = RotateLeft(p->left);
		return RotateRight(p);
	}
	return p;
}
node_t* Insert(node_t* p, int key, int data) {
	if (!p) {
		p = (node_t*)malloc(sizeof(node_t));
		if (!p)
			return NULL;
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
	if (key < p->key)
		p->left = Insert(p->left, key, data);
	if (key > p->key)
		p->right = Insert(p->right, key, data);
	return Balance(p);
}

node_t* Findmin(node_t* p) {
	return p->left ? Findmin(p->left) : p;
}

node_t* Removemin(node_t* p) {
	if (!p->left)
		return p->right;
	p->left = Removemin(p->left);
	return Balance(p);
}

node_t* DeleteKey(node_t* p, int key) {
	if (!p)
		return 0;
	if (key < p->key)
		p->left = DeleteKey(p->left, key);
	else if (key > p->key)
		p->right = DeleteKey(p->right, key);
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
	if (!p) {
		return NULL;
	}
	if (data == p->data) {
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
	node_t* q = DeleteData(p->left, data);
	node_t* r = DeleteData(p->right, data);
	return p;
}

node_t* SearchData(node_t* p, int data) {
	if (!p) {
		return NULL;
	}
	if (data == p->data) {
		return p;
	}
	node_t* q = SearchData(p->left, data);
	if (!q && q->left->data == data) {
		return q;
	}
	node_t* r = SearchData(p->right, data);
	if (!r && r->right->data == data) {
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
	if (k < p->key)
		SearchKey(p->left, k);
	else
		SearchKey(p->right, k);
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
	node_t* tmp = p;
	while (!tmp->right) {
		tmp = tmp->right;
	}
	int len1 = tmp->key;
	UpdateKey(q, len1);
	node_t* fict = malloc(sizeof(node_t));
	if (!fict) {
		return NULL;
	}
	fict->data = -1;
	fict->left = p;
	fict->right = q;
	fict->height = -1;
	fict->key = -1;
	fict = DeleteKey(fict, -1);
	return fict;
}


int test() {
	node_t* p = NULL;
	char command[16] = " ", ch;
	int key,data;
	while (fgets(command, 16, stdin)) {
		sscanf(command, "%c%i%i\n", &ch, &key, &data);
		switch (ch) {
		case 'a':
			p = Insert(p, key,data);
			break;
		case 'r':
			p = DeleteKey(p, key);
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