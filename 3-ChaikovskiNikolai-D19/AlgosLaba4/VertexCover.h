#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct edge_t {
	int first, second;
	struct edge_t* next;
	int check;
}edge_t;
typedef struct {
	int size;
	edge_t* head;
}edges_t;
typedef struct {
	int size;
	edges_t* edges;
}graph_t;
edge_t* EdgeCreate(int a, int b);
graph_t* GraphCreate(int size);
void EdgesDelete(edges_t* edges);
void GraphDelete(graph_t* graph);
void AddEdge(edges_t* edges, edge_t* edge);
graph_t* GraphRead(FILE* in, int* k);
int IsSolution(graph_t* graph);
void ChangeInGraph(graph_t* graph, int edge);
int* SearchRefurd(int* ver, int m, graph_t* graph, int k);
void VertexCover(graph_t* graph, int k);
int VertexCoverFile(FILE* in, FILE* out);