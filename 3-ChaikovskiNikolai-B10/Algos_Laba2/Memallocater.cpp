#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void* head = NULL;
void* pmemory = NULL;
int allsize = 0;
int* GetSizeofBlock(void* Desc) {
	return (int*)Desc;
}
void** GetNext(void* Desc) {
	return (void**)((char*)Desc + sizeof(int));
}
int* GetSizeofRight(void* Desc) {
	return (int*)((char*)Desc + abs(*GetSizeofBlock(Desc)) - sizeof(int));
}
int meminit(void* pMemory, int size) {
	if (size <= memgetminimumsize()) {
		return 0;
	}
	void* const desc = (void*)pMemory;
	*GetSizeofBlock(desc) = size;
	*GetNext(desc) = NULL;
	*GetSizeofRight(desc) = size;
	allsize = size;
	head = desc;
	pmemory = pMemory;
	return size;
}
void* memalloc(int size) {
	if (size > allsize - memgetblocksize() || size < 1) {
		return NULL;
	}
	void* cur = head;
	void* prev = NULL;
	void* fit = NULL;
	while (cur) {
		if (*GetSizeofBlock(cur) >= size + memgetblocksize()) {
			fit = cur;
			break;
		}
		else {
			prev = cur;
			cur = *GetNext(cur);
		}
	}
	if (!fit) {
		return NULL;
	}
	if (*GetSizeofBlock(fit) > size + memgetblocksize() + memgetblocksize()) {
		void* newDesc = (void*)((char*)fit + memgetblocksize() + size);
		*GetSizeofBlock(newDesc) = *GetSizeofBlock(fit) - memgetblocksize() - size;
		*GetNext(newDesc) = *GetNext(fit);
		*GetSizeofRight(newDesc) = *GetSizeofBlock(newDesc);
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
			head = *GetNext(fit);
		}
	}
	*GetSizeofBlock(fit) = -*GetSizeofBlock(fit);
	*GetSizeofRight(fit) = *GetSizeofBlock(fit);
	*GetNext(fit) = NULL;
	return (void*)((char*)fit + sizeof(int) + sizeof(void*));
}
void memfree(void* p) {
	if (!p) {
		return;
	}
	void* desc = (void*)((char*)p - sizeof(int) - sizeof(void*));
	void* prevDesc = NULL;
	if ((char*)desc - 1 > (char*)pmemory)
		prevDesc = (void*)((char*)desc - abs(*((int*)desc - 1)));
	void* nextDesc = (void*)(GetSizeofRight(desc) + 1);
	char mergeLeft = 0, mergeRight = 0;
	*GetSizeofBlock(desc) = -*GetSizeofBlock(desc);
	*GetSizeofRight(desc) = *GetSizeofBlock(desc);
	if (prevDesc >= pmemory) {
		if (*GetSizeofBlock(prevDesc) > 0) {
			mergeLeft = 1;
			*GetSizeofBlock(prevDesc) += *GetSizeofBlock(desc);
			*GetSizeofRight(prevDesc) = *GetSizeofBlock(prevDesc);
			desc = prevDesc;
		}
	}
	if ((char*)nextDesc < (char*)pmemory + allsize) {
		if (*GetSizeofBlock(nextDesc) > 0) {
			mergeRight = 1;
			if (!mergeLeft) {
				*GetNext(desc) = head;
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
				head = *GetNext(nextDesc);
			}
			else {
				*GetNext(prevPrevDesc) = *GetNext(nextDesc);
			}
			*GetSizeofBlock(desc) += *GetSizeofBlock(nextDesc);
			*GetSizeofRight(desc) = *GetSizeofBlock(desc);
		}
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
		cur = (char*)(cur) + abs(*GetSizeofBlock(cur));
	}
}
int memgetminimumsize() {
	return sizeof(int) + sizeof(void*) + sizeof(int);
}
int memgetblocksize() {
	return sizeof(int) + sizeof(void*) + sizeof(int);
}