#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Laba1Plenty.h"
//int main(void) {
//	return 0;
//}
Plenty_t* CreateZeroPlenty(void) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		return NULL;
	}
	A->head = NULL;
	return A;
}
void FillPlenty(Plenty_t* A, int size, int step) {
	if (A == NULL || size == 0) {
		return;
	}
	node_t* p;
	A->head = (node_t*)malloc(sizeof(node_t));
	if (A->head == NULL) {
		return;
	}
	if (step == 0) {
		AddInPlenty(A, 0);
		return;
	}
	p = A->head;
	for (int i = 1; i <= size; i++) {
		p->elem = step * i;
		if (i != size) {
			p->next = (node_t*)malloc(sizeof(node_t));
			if (p->next == NULL) {
				return;
			}
			p = p->next;
		}
	}
	p->next = NULL;
}
void DestroyPlenty(Plenty_t* A) {
	if (A == NULL) {
		return;
	}
	node_t* p, * t;
	p = A->head;
	if (p == NULL) {
		free(A);
		return;
	}
	t = NULL;
	while (p != NULL) {
		t = p->next;
		free(p);
		p = t;
	}
	free(A);
	return;
}
bool AddInPlenty(Plenty_t* A, int elem) {
	if (A == NULL) {
		return false;
	}
	node_t* p, * t, * h;
	t = (node_t*)malloc(sizeof(node_t));
	if (t == NULL) {
		return false;
	}
	t->next = NULL;
	if (A->head == NULL) {
		t->elem = elem;
		A->head = t;
		return true;
	}
	p = A->head;
	while (p->elem < elem) {
		if (p->next == NULL) {
			t->elem = elem;
			p->next = t;
			return true;
		}
		p = p->next;
	}
	if (p->elem == elem) {
		return false;
	}
	h = p->next;
	t->elem = p->elem;
	p->elem = elem;
	p->next = t;
	t->next = h;
	return true;
}
bool DeleteFromPlenty(Plenty_t* A, int elem) {
	if (A == NULL || A->head == NULL) {
		return false;
	}
	node_t* p, * t, * h;
	p = A->head;
	if (p->elem == elem) {
		h = p;
		if (p->next != NULL) {
			t = h->next;
			free(h);
			A->head = t;
			return true;
		}
		else {
			free(h);
			A->head = NULL;
			return true;
		}
	}
	while ((p->next != NULL) && (p->next->elem != elem)) {
		if (p->next->next == NULL) {
			return false;
		}
		p = p->next;
	}
	t = p->next->next;
	free(p->next);
	p->next = t;
	return true;
}
bool IsIncludePlenty(Plenty_t* A, int elem) {
	if (A == NULL || A->head == NULL) {
		return false;
	}
	node_t* p;
	p = A->head;
	do {
		if (p->elem == elem) {
			return true;
		}
		p = p->next;
	} while (p->next != NULL);
	return false;
}
Plenty_t* PlentyCombine(Plenty_t* A, Plenty_t* B) {
	if (A == NULL || B == NULL) {
		return NULL;
	}
	Plenty_t* C = CreateZeroPlenty();
	if (C == NULL) {
		return NULL;
	}
	node_t* p1 = A->head;
	node_t* p2 = B->head;
	while ((p1 != NULL) && (p2 != NULL)) {
		if (p1->elem > p2->elem) {
			if (!AddInPlenty(C, p2->elem)) {
				if (IsIncludePlenty(C, p2->elem)) {
					p2 = p2->next;
				}
				continue;
			}
			p2 = p2->next;
			continue;
		}
		if (p1->elem < p2->elem) {
			if (!AddInPlenty(C, p1->elem)) {
				if (IsIncludePlenty(C, p1->elem)) {
					p1 = p1->next;
				}
				continue;
			}
			p1 = p1->next;
			continue;
		}
		if (p1->elem == p2->elem) {
			if (!AddInPlenty(C, p2->elem)) {
				if (IsIncludePlenty(C, p2->elem)) {
					p2 = p2->next;
				}
				continue;
			}
			p2 = p2->next;
			p1 = p1->next;
			continue;
		}
	}
	while (p1 != NULL)
	{
		if (!AddInPlenty(C, p1->elem)) {
			if (IsIncludePlenty(C, p1->elem)) {
				p1 = p1->next;
			}
			continue;
		}
		p1 = p1->next;
	}
	while (p2 != NULL)
	{
		if (!AddInPlenty(C, p2->elem)) {
			if (IsIncludePlenty(C, p2->elem)) {
				p2 = p2->next;
			}
			continue;
		}
		p2 = p2->next;
	}
	return C;
}
Plenty_t* PlentyIntersect(Plenty_t* A, Plenty_t* B) {
	if (A == NULL || B == NULL) {
		return NULL;
	}
	Plenty_t* C = CreateZeroPlenty();
	if (C == NULL) {
		return NULL;
	}
	node_t* p1 = A->head;
	node_t* p2 = B->head;
	while ((p1 != NULL) && (p2 != NULL)) {
		if (p1->elem > p2->elem) {
			p2 = p2->next;
			continue;
		}
		if (p1->elem < p2->elem) {
			p1 = p1->next;
			continue;
		}
		if (p1->elem == p2->elem) {
			if (!AddInPlenty(C, p2->elem)) {
				if (IsIncludePlenty(C, p2->elem)) {
					p2 = p2->next;
				}
				continue;
			}
			p2 = p2->next;
			p1 = p1->next;
			continue;
		}
	}
	return C;
}