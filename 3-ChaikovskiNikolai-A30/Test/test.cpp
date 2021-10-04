#include "pch.h"
#include "Laba1Plenty.h"
TEST(Create_Plenty, Create_Normal) {
	Plenty_t* A = CreateZeroPlenty();
	ASSERT_NE(nullptr, A);//Из-за специфики гугол тестов, при попытке сравнить с помощью ф-ции ASSERT_NE() NULL с указателем выдается ошибка.
	ASSERT_EQ(nullptr, A->head);//Поэтому я везде, где сравниваю указатель с нулевым указателем, использую nullptr.
	DestroyPlenty(A);
}

TEST(Fill_Plenty, Fill_One) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	FillPlenty(A, 1, 1);
	ASSERT_NE(nullptr, A);
	ASSERT_NE(nullptr, A->head);
	ASSERT_EQ(1, A->head->elem);
	free(A->head);
	free(A);
}
TEST(Fill_Plenty, Fill_Four) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	FillPlenty(A, 3, 1);
	ASSERT_NE(nullptr, A);
	ASSERT_NE(nullptr, A->head);
	ASSERT_NE(nullptr, A->head->next);
	ASSERT_NE(nullptr, A->head->next->next);
	int a[3] = { 1, 2, 3 };
	node_t* p = A->head;
	ASSERT_EQ(a[0], p->elem);
	p = p->next;
	ASSERT_EQ(a[1], p->elem);
	p = p->next;
	ASSERT_EQ(a[2], p->elem);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
}
TEST(Add_Element, AddElem) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	p->next = NULL;
	bool check = AddInPlenty(A, 2);
	ASSERT_EQ(true, check);
	ASSERT_NE(nullptr, A->head->next);
	ASSERT_EQ(1, p->elem);
	ASSERT_EQ(2, p->next->elem);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
}
TEST(Add_Element, Add_Equal_Elem) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	p->next = NULL;
	bool check = AddInPlenty(A, 1);
	ASSERT_EQ(false, check);
	ASSERT_EQ(1, p->elem);
	ASSERT_EQ(nullptr, p->next);
	ASSERT_EQ(false, check);
	p = A->head;
	free(p);
	free(A);
}
TEST(Add_Element, Add_In_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = NULL;
	bool check = AddInPlenty(A, 1);
	ASSERT_EQ(false, check);
	ASSERT_EQ(1, A->head->elem);
	free(A->head);
	free(A);
}
TEST(Delete_Elem, Delete_Exist) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	bool check = DeleteFromPlenty(A, 2);
	ASSERT_EQ(true, check);
	ASSERT_EQ(nullptr, A->head->next);
	ASSERT_EQ(1, A->head->elem);
	free(A->head);
	free(A);
}
TEST(Delete_Elem, Delete_No_Exist) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	bool check = DeleteFromPlenty(A, 3);
	ASSERT_EQ(false, check);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
}
TEST(Delete_Elem, Delete_In_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = NULL;
	bool check = DeleteFromPlenty(A, 3);
	ASSERT_EQ(false, check);
	free(A);
}

TEST(Search, Elem_Exist) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	bool check = IsIncludePlenty(A, 1);
	ASSERT_EQ(true, check);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
}

TEST(Search, Elem_No_Exist) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	bool check = IsIncludePlenty(A, 0);
	ASSERT_EQ(false, check);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
}

TEST(Search, Plenty_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = NULL;
	bool check = IsIncludePlenty(A, 0);
	ASSERT_EQ(false, check);
	free(A);
}

TEST(Combine, Normal_Combine) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(B, nullptr);
	B->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(B->head, nullptr);
	p = B->head;
	p->elem = 3;
	p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 4;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* C = PlentyCombine(A, B);
	int a[4] = { 1,2,3,4 };
	ASSERT_NE(nullptr, C);
	ASSERT_NE(nullptr, C->head);
	ASSERT_NE(nullptr, C->head->next);
	ASSERT_NE(nullptr, C->head->next->next);
	ASSERT_NE(nullptr, C->head->next->next->next);
	ASSERT_EQ(a[0], C->head->elem);
	ASSERT_EQ(a[1], C->head->next->elem);
	ASSERT_EQ(a[2], C->head->next->next->elem);
	ASSERT_EQ(a[3], C->head->next->next->next->elem);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
	p = B->head;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(B);
	p = C->head;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(C);
}

TEST(Combine, Combine_One_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(B, nullptr);
	B->head = NULL;
	Plenty_t* C = PlentyCombine(A, B);
	ASSERT_NE(nullptr, C);
	ASSERT_NE(nullptr, C->head);
	ASSERT_NE(nullptr, C->head->next);
	ASSERT_EQ(1, C->head->elem);
	ASSERT_EQ(2, C->head->next->elem);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
	free(B);
	p = C->head;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(C);
}

TEST(Combine, Combine_Both_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = NULL;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(B, nullptr);
	B->head = NULL;
	Plenty_t* C = PlentyCombine(A, B);
	ASSERT_NE(nullptr, C);
	ASSERT_EQ(nullptr, C->head);
	free(A);
	free(B);
	free(C);
}

TEST(Intersect, Intersect_Normal) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(B, nullptr);
	B->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(B->head, nullptr);
	p = B->head;
	p->elem = 2;
	p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 3;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* C = PlentyIntersect(A, B);
	ASSERT_NE(nullptr, C);
	ASSERT_NE(nullptr, C->head);
	ASSERT_EQ(2, C->head->elem);
	ASSERT_EQ(nullptr, C->head->next);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
	p = B->head;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(B);
	p = C->head;
	free(p);
	free(C);
}

TEST(Intersect, Intersect_One_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(A->head, nullptr);
	node_t* p = A->head;
	p->elem = 1;
	node_t* p1 = (node_t*)malloc(sizeof(node_t));
	ASSERT_NE(p1, nullptr);
	p1->elem = 2;
	p1->next = NULL;
	p->next = p1;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(B, nullptr);
	B->head = NULL;
	Plenty_t* C = PlentyIntersect(A, B);
	ASSERT_NE(nullptr, C);
	ASSERT_EQ(nullptr, C->head);
	p = A->head;
	node_t* t;
	t = p->next;
	free(p);
	p = t;
	t = p->next;
	free(p);
	p = t;
	free(A);
	free(B);
	free(C);
}

TEST(Intersect, Intersect_Both_Empty) {
	Plenty_t* A = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(A, nullptr);
	A->head = NULL;
	Plenty_t* B = (Plenty_t*)malloc(sizeof(Plenty_t));
	ASSERT_NE(B, nullptr);
	B->head = NULL;
	Plenty_t* C = PlentyIntersect(A, B);
	ASSERT_NE(nullptr, C);
	ASSERT_EQ(nullptr, C->head);
	free(A);
	free(B);
	free(C);
}