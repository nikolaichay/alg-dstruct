#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Header.h"
#pragma warning(disable: 4996)

node_t* NodeCreate(int n) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	if (!node) {
		return NULL;
	}
	node->data = n;
	node->next = NULL;
	return node;
}
queue_t* QueueCreate() {
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	if (!queue) {
		return NULL;
	}
	queue->front = NULL;
	queue->back = NULL;
	queue->size = 0;
	return queue;
}
graph_t* GraphCreate(int size) {
	graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
	if (!graph) {
		return NULL;
	}
	graph->size = size;
	graph->links = (queue_t**)malloc(size * sizeof(queue_t));
	if (!graph->links) {
		free(graph);
		return NULL;
	}
	for (int i = 0; i < size; i++) {
		graph->links[i] = QueueCreate();
		if (!graph->links[i]) {
			free(graph);
			return NULL;
		}
	}
	return graph;
}
void QueueDelete(queue_t* queue) {
	node_t* node = queue->front;
	for (int i = 0; i < queue->size; i++) {
		node_t* tmp = node;
		node = node->next;
		free(tmp);
	}
	free(queue);
}
void GraphDelete(graph_t* graph) {
	if (graph) {
		for (int i = 0; i < graph->size; i++) {
			QueueDelete(graph->links[i]);
		}
		free(graph->links);
		free(graph);
	}
}
void Enqueue(queue_t* queue, int n) {
	node_t* node = NodeCreate(n);
	if (!node) {
		return;
	}
	if (queue->size > 0) {
		queue->back->next = node;
		queue->back = node;
	}
	else {
		queue->front = node;
		queue->back = node;
	}
	queue->size++;
}
int Dequeue(queue_t* queue) {
	if (queue->size > 0) {
		node_t* node = queue->front;
		int value = node->data;
		queue->front = node->next;
		free(node);
		queue->size--;
		return value;
	}
	else
		return 0;
}
void GraphRead(FILE* in, graph_t* graph) {
	int first, nextVal = 0;
	char c;
	if (!in) {
		return;
	}
	while (fscanf(in, "%i%c", &first, &c) > 0) {
		if (c != ' ') {
			continue;
		}
		while (fscanf(in, "%i%c", &nextVal, &c) > 0) {
			Enqueue(graph->links[first], nextVal);
			Enqueue(graph->links[nextVal], first);
			if (c != ' ') {
				break;
			}
		}
	}
}
int BFS(graph_t* graph, FILE* out) {
	bool* flags = (bool*)calloc(graph->size, sizeof(bool));
	if (!flags) {
		return 0;
	}
	queue_t* queue = QueueCreate();
	if (!queue) {
		free(flags);
		return 0;
	}
	int cur = 0;
	flags[0] = 1;
	do {
		fprintf(out, "%d", cur);
		int size = graph->links[cur]->size;
		for (int i = 0; i < size; i++) {
			int n = Dequeue(graph->links[cur]);
			if (!flags[n]) {
				flags[n] = 1;
				Enqueue(queue, n);
			}
		}
		if (queue->size > 0) {
			fprintf(out, " ");
		}
	} while ((cur = Dequeue(queue)));
	free(flags);
	QueueDelete(queue);
	return 1;
}