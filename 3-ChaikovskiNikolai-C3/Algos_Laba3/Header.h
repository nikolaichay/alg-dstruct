#pragma once
typedef struct node_t {
	struct node_t* next;
	int data;
}node_t;
typedef struct {
	node_t* front, * back;
	int size;
}queue_t;
typedef struct {
	int size;
	queue_t** links;
}graph_t;
node_t* NodeCreate(int n);
queue_t* QueueCreate();
graph_t* GraphCreate(int size);
void QueueDelete(queue_t* queue);
void GraphDelete(graph_t* graph);
void Enqueue(queue_t* queue, int n);
int Dequeue(queue_t* queue);
void GraphRead(FILE* in, graph_t* graph);
int BFS(graph_t* graph, FILE* out);