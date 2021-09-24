#include "pch.h"
#include "Laba1Plenty.h"
bool CompareValues(Plenty_t* A, int a[], int size) {
	int i = 0;
	node_t* p = A->head;
	while (i < size && p != NULL) {
		if (a[i] != p->elem)
			return false;
		i++;
		p = p->next;
	}
	return true;
}
TEST(Create_Plenty,Create_Normal) {
	Plenty_t* A = CreateZeroPlenty();
	ASSERT_FALSE(A==NULL);
	ASSERT_TRUE(A->head == NULL);
	DestroyPlenty(A);
}

TEST(Fill_Plenty, Fill_One) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	FillPlenty(A, 1, 1);
	ASSERT_EQ(1,A->head->elem);
	DestroyPlenty(A);
}
TEST(Fill_Plenty, Fill_Five) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	FillPlenty(A, 3, 1);
	int a[3] = { 1, 2, 3};
	node_t* p = A->head;
	ASSERT_EQ(a[0], p->elem);
	p = p->next;
	ASSERT_EQ(a[1], p->elem);
	p = p->next;
	ASSERT_EQ(a[2], p->elem);
	DestroyPlenty(A);
}
TEST(Add_Element, AddElelm) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head=(node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	p->next = NULL;
	AddInPlenty(A, 2);
	ASSERT_EQ(1, p->elem);
	ASSERT_EQ(2, p->next->elem);
	DestroyPlenty(A);
}
TEST(Add_Element, Add_In_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = NULL;
	AddInPlenty(A, 1);
	ASSERT_EQ(1, A->head->elem);
	DestroyPlenty(A);
}
TEST(Delete_Elem, Delete_Exist) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = (node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	DeleteFromPlenty(A, 2);
	ASSERT_EQ(NULL, A->head->next);
	ASSERT_EQ(1, A->head->elem);
	DestroyPlenty(A);
}
TEST(Delete_Elem, Delete_No_Exist) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = (node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	bool check = DeleteFromPlenty(A, 32);
	ASSERT_EQ(false, check);
	DestroyPlenty(A);
}
TEST(Delete_Elem, Delete_In_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = NULL;
	bool check = DeleteFromPlenty(A, 32);
	ASSERT_EQ(false, check);
	DestroyPlenty(A);
}

TEST(Search, Elem_Exist) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = (node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	bool check = IsIncludePlenty(A, 1);
	ASSERT_EQ(true, check);
	DestroyPlenty(A);
}

TEST(Search, Elem_No_Exist) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = (node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	bool check = IsIncludePlenty(A, 0);
	ASSERT_EQ(false, check); 
	DestroyPlenty(A);
}

TEST(Search, Plenty_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = NULL;
	bool check = IsIncludePlenty(A, 0);
	ASSERT_EQ(false, check);
	DestroyPlenty(A);
}

TEST(Combine, Normal_Combine) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = (node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (B == NULL) {
		ASSERT_TRUE(0);
	}
	B->head = (node_t*)malloc(sizeof(node_t));
	p = B->head;
	p->elem = 3;
	p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 4;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* C = PlentyCombine(A, B);
	int a[4] = { 1,2,3,4 };
	bool check = CompareValues(C, a, 4);
	ASSERT_EQ(true, check);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}

TEST(Combine, Combine_One_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = (node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (B == NULL) {
		ASSERT_TRUE(0);
	}
	B->head = NULL;
	Plenty_t* C = PlentyCombine(A, B);
	ASSERT_EQ(1, C->head->elem);
	ASSERT_EQ(2, C->head->next->elem);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}

TEST(Combine, Combine_Both_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head =NULL;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (B == NULL) {
		ASSERT_TRUE(0);
	}
	B->head = NULL;
	Plenty_t* C = PlentyCombine(A, B);
	ASSERT_EQ(NULL, C->head);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}

TEST(Intersect, Intersect_Normal) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = (node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (B == NULL) {
		ASSERT_TRUE(0);
	}
	B->head = (node_t*)malloc(sizeof(node_t));
	p = B->head;
	p->elem = 2;
	p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 3;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* C = PlentyIntersect(A, B);
	ASSERT_EQ(2, C->head->elem);
	ASSERT_EQ(NULL, C->head->next);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}

TEST(Intersect, Intersect_One_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = (node_t*)malloc(sizeof(node_t));
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (B == NULL) {
		ASSERT_TRUE(0);
	}
	B->head = NULL;
	Plenty_t* C = PlentyIntersect(A, B);
	ASSERT_EQ(NULL, C->head);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}

TEST(Intersect, Intersect_Both_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (A == NULL) {
		ASSERT_TRUE(0);
	}
	A->head = NULL;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	if (B == NULL) {
		ASSERT_TRUE(0);
	}
	B->head = NULL;
	Plenty_t* C = PlentyIntersect(A, B);
	ASSERT_EQ(NULL, C->head);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
	_CrtDumpMemoryLeaks;
}