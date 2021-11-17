#include "pch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "C:\Users\nikol\source\repos\Algos_Laba3\Algos_Laba3\Header.h"
#include "C:\Users\nikol\source\repos\Algos_Laba3\Algos_Laba3\LabaC.c"
#pragma warning(disable: 4996)
/*
IDE: Microsoft Visual Studio 2019
OS: Windows 10 Home rus 20H2 Build 19043.1348
PC configuration:
CPU: Intel(R) Core(TM) i3-7100U CPU @ 2.40GHz
Motherboard: LENOVO
RAM: 8GB
SDD: 256GB
*/

/*
LabSolution_StressTest results (run on Release VS configuration):
Time: 15.881 sec to generate graph
59.455 sec to output answer
RAM: about
*/
const char* filenameGraph = "StressTestGraph.txt";
const int verticesCount = (int)1e6;

TEST(LabSolution_StressTest, LabSolutionGraphGenerating) {
	const int maxDeltaNeighbour = verticesCount;
	// opening test file
	FILE* fileGraph = fopen(filenameGraph, "w");
	if (!fileGraph) {
		printf("Error while opening %s file!\n", filenameGraph);
		ASSERT_TRUE(fileGraph);
	}
	// generating random graph
	fprintf(fileGraph, "%d\n", verticesCount);
	for (int i = 0; i < verticesCount - 1; i++) {
		fprintf(fileGraph, "%d", i);
		for (int neighbour = i + rand() % (maxDeltaNeighbour - 1) + 1; neighbour < verticesCount; neighbour += rand() % (maxDeltaNeighbour - 1) + 1)
			fprintf(fileGraph, " %d", neighbour);
		fprintf(fileGraph, "\n");
	}
	fprintf(fileGraph, "%d\n", verticesCount - 1);
	fclose(fileGraph);
}

TEST(LabSolution_StressTest, LabSolutionMainStressTest) {
	const char* filenameOutput = "Output.txt";
	int depthFirstTraversalResult = 0;
	FILE* fileGraph = fopen(filenameGraph, "r");
	if (!fileGraph) {
		printf("Error while opening %s file!\n", filenameGraph);
		ASSERT_TRUE(fileGraph);
	}
	int size;
	fscanf(fileGraph, "%d", &size);
	graph_t* graph = GraphCreate(size);
	GraphRead(fileGraph,graph);
	fclose(fileGraph);
	if (!graph) {
		printf("Failed to read graph!\n");
		ASSERT_TRUE(graph);
	}
	FILE* fileOutput = fopen(filenameOutput, "w");
	if (!fileOutput) {
		GraphDelete(graph);
		printf("Error while opening %s file!\n", filenameOutput);
		ASSERT_TRUE(fileOutput);
	}
	depthFirstTraversalResult =BFS(graph, fileOutput);
	if (!depthFirstTraversalResult) {
		fclose(fileOutput);
		GraphDelete(graph);
		printf("Memory allocation failed while DepthFirstTraversalIterative!");
		ASSERT_TRUE(depthFirstTraversalResult);
	}
	fclose(fileOutput);
	GraphDelete(graph);
}