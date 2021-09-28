#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct node_t {
		int elem;
		struct node_t* next;
	}node_t;
	typedef struct {
		node_t* head;
	}Plenty_t;
	Plenty_t* CreateZeroPlenty(void);
	void DestroyPlenty(Plenty_t* A);
	void FillPlenty(Plenty_t* A, int size, int step);
	bool AddInPlenty(Plenty_t* A, int elem);
	bool DeleteFromPlenty(Plenty_t* A, int elem);
	bool IsIncludePlenty(Plenty_t* A, int elem);
	Plenty_t* PlentyCombine(Plenty_t* A, Plenty_t* B);
	Plenty_t* PlentyIntersect(Plenty_t* A, Plenty_t* B);

#ifdef __cplusplus
}
#endif