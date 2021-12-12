#include "VertexCover.h"
edge_t* EdgeCreate(int a, int b) {
	edge_t* edge = (edge_t*)malloc(sizeof(edge_t));
	if (!edge) {
		return NULL;
	}
	edge->first = a;
	edge->second = b;
	edge->next = NULL;
	return edge;
}
graph_t* GraphCreate(int size) {
	graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
	if (!graph) {
		return NULL;
	}
	graph->size = size;
	edges_t* edges = (edges_t*)malloc(sizeof(edges_t));
	if (!edges) {
		free(graph);
		return NULL;
	}
	edges->head = NULL;
	edges->size = 0;
	graph->edges = edges;
	return graph;
}
void EdgesDelete(edges_t* edges) {
	edge_t* tmp = edges->head;
	while (tmp != NULL) {
		tmp = edges->head->next;
		free(edges->head);
		edges->head = tmp;
	}
	free(edges);
}
void GraphDelete(graph_t* graph) {
	if (graph) {
		EdgesDelete(graph->edges);
		free(graph);
	}
}
void AddEdge(edges_t* edges, edge_t* edge) {
	edge->check = 0;
	if (!edges->head) {
		edges->head = edge;
		edges->size++;
	}
	else {
		edge->next = edges->head;
		edges->head = edge;
		edges->size++;
	}
}
graph_t* GraphRead(FILE* in, int* k) {
	int size = 0;
	fscanf(in, "%d %d\n", &size, k);
	if (!size) {
		return NULL;
	}
	if (!in) {
		return NULL;
	}
	graph_t* graph = GraphCreate(size);
	if (!graph) {
		return NULL;
	}
	int first, second = 0;
	while (fscanf(in, "%d %d\n", &first, &second) > 0) {
		edge_t* edge = EdgeCreate(first, second);
		if (!edge) {
			GraphDelete(graph);
			return NULL;
		}
		AddEdge(graph->edges, edge);
	}
	edge_t* head = graph->edges->head;
	while (head) {
		//printf("%d, %d\n", head->first, head->second);
		head = head->next;
	}
	return graph;
}
int IsSolution(graph_t* graph) {
	edge_t* head = graph->edges->head;
	while (!head) {
		if (head->check == 0) {
			return 0;
		}
		head = head->next;
	}
	return 1;
}
void ChangeInGraph(graph_t* graph, int edge) {
	edge_t* head = graph->edges->head;
	while (!head) {
		if (head->first == abs(edge) || head->second == abs(edge)) {
			head->check = (head->check + (edge / abs(edge)));
		}
		head = head->next;
	}
}
int* SearchRefurd(int* ver, int m, graph_t* graph, int k) {
	if (m <= k && IsSolution(graph)) {
		return ver;
	}
	if (m >= k) {
		return NULL;
	}
	else {
		for (int i = m + 1; i <= graph->edges->size; i++) {
			ver[m] = i;
			ChangeInGraph(graph, i);
			if (SearchRefurd(ver, m + 1, graph, k)) {
				return ver;
			}
			ChangeInGraph(graph, -i);
		}
		return NULL;
	}
}
void VertexCover(graph_t* graph, int k, FILE* out) {
	int n = graph->size;
	int* ver = (int*)calloc(k, sizeof(int));
	int m = 0;
	int* tmpver = SearchRefurd(ver, m, graph, k);
	if (!tmpver) {
		fprintf(out, "%d ", 0);
		free(ver);
		return;
	}
	else {
		ver = tmpver;
		for (int i = 0; i < k; i++) {
			if (ver[i] != 0) {
				fprintf(out, "%d ", ver[i]);
			}
		}
	}
	free(ver);
	return;
}
int VertexCoverFile(FILE* in, FILE* out) {
	int k = 0;
	graph_t* graph = GraphRead(in, &k);
	if (!graph) {
		return 0;
	}
	VertexCover(graph, k, out);
	GraphDelete(graph);
	return 1;
}