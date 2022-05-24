#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)


typedef struct {
	char* str;
	int deleted;
} node;


const int size = 524288;

node* HashMap(void) {
	node* map = (node*)malloc(size * sizeof(node));
	if (!map) {
		return NULL;
	}
	for (int i = 0; i < size; i++) {
		map[i].str = NULL;
		map[i].deleted = 0;
	}
	return map;
}

int Hash(const char* str, int iter) {
	int c0 = 29;
	double c1 = 0.5;
	double c2 = 0.5;
	int h1 = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		h1 = c0 * h1 + str[i];
	}
	h1 = h1 % size;

	int h2 = (int)(h1 + c1 * iter + c2 * iter * iter) % size;

	return h2;
}

int Search(node* map, const char* str) {
	int h = Hash(str, 0);
	int i = 0;
	while (map[h].str && i < size) {
		if (!map[h].deleted && strcmp(map[h].str, str) == 0) {
			return 1;
		}
		i++;
		h = Hash(str, i);
	}
	return 0;
}

int Insert(node* map, const char* str) {
	int i = 0;
	int h = Hash(str, 0);
	int first_deleted = -1;
	while (map[h].str && i < size) {
		if (strcmp(map[h].str, str) == 0 && !map[h].deleted) {
			return 1;
		}
		if (map[h].deleted && first_deleted == -1) {
			first_deleted = h;
		}
		i++;
		h = Hash(str, i);
	}

	if (first_deleted != -1) {
		if (map[first_deleted].str) {
			free(map[first_deleted].str);
		}
		map[first_deleted].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
		if (!map[first_deleted].str) {
			return 0;
		}
		strcpy(map[first_deleted].str, str);
		map[first_deleted].deleted = 0;
	}
	else {
		map[h].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
		if (!map[h].str) {
			return 0;
		}
		strcpy(map[h].str, str);
	}
}

void RemoveElement(node* map, const char* str) {
	int h = Hash(str, 0);
	int i = 0;
	while (map[h].str && i < size) {
		if (strcmp(map[h].str, str) == 0 && !map[h].deleted) {
			map[h].deleted = 1;
			return;
		}
		i++;
		h = Hash(str, i);
	}
}

void DestroyHashMap(node* map) {
	if (!map) {
		return;
	}
	for (int i = 0; i < size; i++) {
		free(map[i].str);
	}
	free(map);
}

int main() {
	node* map = HashMap();
	char command;
	char str[10000];
	while (scanf("%c", &command) > 0) {
		switch (command) {
		case 'a':
			scanf("%s", &str);
			Insert(map, str);
			break;
		case 'f':
			scanf("%s", &str);
			if (Search(map, str))
				printf("%s", "yes\n");
			else
				printf("%s", "no\n");
			break;
		case 'r':
			scanf("%s", &str);
			RemoveElement(map, str);
			break;
		}

	}
	DestroyHashMap(map);
	return 0;
}