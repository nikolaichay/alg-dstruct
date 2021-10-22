#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void* head = NULL;
void* pmemory = NULL;
int allsize = 0;
int* GetSizeofBlock(void* Desc) {
	return (int*)(Desc);
}
void** GetNext(void* Desc) {
	return (void**)((char*)Desc + sizeof(int));
}
int* GetSizeofNext(void* Desc) {
	return (int*)((char*)Desc + abs(*GetSizeofBlock(Desc)) - sizeof(int));
}
int meminit(void* pMemory, int size) {
	if (size < memgetminimumsize()) {
		return 0;
	}
	void* desc = pMemory;
	*GetSizeofBlock(desc) = size;
	*GetNext(desc) = NULL;
	*GetSizeofNext(desc) = size;
	allsize = size;
	head = desc;
	pmemory = pMemory;
	return 1;
}
void* memalloc(int size) {
	if (size > allsize - memgetblocksize() || size < 1) {
		return NULL;
	}
	void* cur = head;
	void* prev = NULL;
	while (cur) {
		if (GetSizeofBlock(cur) < size + memgetblocksize()) {
			prev = cur;
			cur = *GetNext(cur);
		}
	}
	if (!cur) {
		return NULL;
	}
	void* fit = cur;
	if (GetSizeofBlock(fit) > size + 2 * memgetblocksize()) {
		void* newDesc = (void*)((char*)fit + memgetblocksize() + size);
		*GetSizeofBlock(newDesc) = GetSizeofBlock(fit) - size - memgetblocksize();
		*GetNext(newDesc) = *GetNext(fit);
		*GetSizeofNext(newDesc) = GetSizeofBlock(newDesc);
		if (prev) {
			*GetNext(prev) = newDesc;
		}
		else {
			head = newDesc;
		}
		*GetSizeofBlock(fit) = size + memgetblocksize();
	}
	else {
		if (prev) {
			*GetNext(prev) = *GetNext(fit);
		}
		else {
			head = GetNext(fit);
		}
	}
	*GetSizeofBlock(fit) = -*GetSizeofBlock(fit);
	*GetSizeofNext(fit) = *GetSizeofBlock(fit);
	*GetNext(fit) = NULL;
	return (void*)((char*)fit + sizeof(int) + sizeof(void*));
}
void memfree(void* p) {
	void* desc = (void*)((char*)p - sizeof(int) - sizeof(void*));
	void* prevDesc = NULL;
	void* nextDesc = (void*)(*GetSizeofNext(desc) + 1);
	if ((char*)(desc)-1 > (char*)pmemory) {
		prevDesc = (void*)(*(int*)desc - 1);
	}
	char mergeLeft = 0, mergeRight = 0;
	*GetSizeofBlock(desc) = -*GetSizeofBlock(desc);
	*GetSizeofNext(desc) = *GetSizeofBlock(desc);
	if (prevDesc >= pmemory && *GetSizeofBlock(prevDesc) > 0) {
		mergeLeft = 1;
		*GetSizeofBlock(prevDesc) += *GetSizeofBlock(desc);
		*GetSizeofNext(prevDesc) = *GetSizeofBlock(desc);
		desc = prevDesc;
	}
	if ((char*)nextDesc < (char*)pmemory + allsize && *GetSizeofBlock(nextDesc)>0) {
		mergeRight = 1;
		if (!mergeLeft) {
			*GetNext(desc)=head;
			head = desc;
		}
		void* prevPrevDesc = head;
		void* cur = head;
		while (cur) {
			if (*GetNext(cur) == nextDesc) {
				prevPrevDesc = cur;
				break;
			}
			cur = *GetNext(cur);
		}
		if (nextDesc == prevPrevDesc) {
			head = GetNext(nextDesc);
		}
		else {
			*GetNext(prevPrevDesc)=*GetNext(nextDesc);
		}
		*GetSizeofBlock(desc) += *GetSizeofBlock(nextDesc);
		*GetSizeofNext(desc) = *GetSizeofBlock(desc);
	}
	if (!mergeLeft && !mergeRight) {
		*GetNext(desc) = head;
		head = desc;
	}
}
void memdone() {
	void* cur = pmemory;
	while ((char*)cur < (char*)pmemory + allsize) {
		if (GetSizeofBlock(cur) < 0) {
			fprintf(stderr, "Memory leak detected: %d bytes of %p\n", *(char*)(*GetNext(cur)), (char*)cur + sizeof(int) + sizeof(void*));
		}
		cur = (char*)(cur)+abs(*GetSizeofBlock(cur));
	}
}
int memgetminimumsize() {
	return sizeof(int) + sizeof(void*) + sizeof(int);
}
//Сделанно
int memgetblocksize() {
	return sizeof(int) + sizeof(void*) + sizeof(int);
}
//Сделанно