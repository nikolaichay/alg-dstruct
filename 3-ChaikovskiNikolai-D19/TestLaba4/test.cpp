#include "pch.h"
#include "VertexCover.h"
#include "VertexCover.c"

/*
*  OS: Arch Linux x86_64
 * PC configuration:
 *      CPU: AMD Ryzen 5 4500U (6) @ 2.375 GHz
 *      RAM: 16 GB
 *      SSD: 512 GB nvme
 */

/*
 * load test results (cmake build type release):
 * Time: 0.001s to generate graph file (size 60, k = 4)
 *       82.18s to read and walk around the graph
 * RAM:  up to 1.089 MiB
*/

const char* filename = "InStress.txt";
const int verticesCount = 60;
TEST(StressTest, graphGeneration) {
    const int maxNeighbourDelta = (int)(0.5*verticesCount);
    FILE* graphFile = fopen(filename, "w");
    if (!graphFile) {
        printf("Error while opening file\n");
        FAIL();
    }
    fprintf(graphFile, "%d %d\n", verticesCount, 4);
    for (int i = 0; i < verticesCount; i++) {
        for (int neighbour = i + rand() % (maxNeighbourDelta - 1) + 1; neighbour < verticesCount;
            neighbour += rand() % (maxNeighbourDelta - 1) + 1) {
            fprintf(graphFile, "%d %d\n", i + 1, neighbour + 1);
        }
    }
    fclose(graphFile);
}

TEST(StressTest, graphPath) {
    const char* filenameOut = "OutStress";
    FILE* graphFile = fopen(filename, "r");
    if (!graphFile) {
        perror("Error while opening file");
        FAIL();
    }
    int k = 0;
    graph_t* graph = GraphRead(graphFile,&k);
    fclose(graphFile);
    if (!graph) {
        perror("Error during graph creation");
        FAIL();
    }
    printf("read done\n");

    FILE* outFile = fopen(filenameOut, "w");
    if (!outFile) {
        GraphDelete(graph);
        perror("Error while opening file");
        FAIL();
    }
    VertexCover(graph, k, outFile);
    GraphDelete(graph);
    fclose(outFile);
}
TEST(VertexCoverTest, FunctionalTestIncorrectData) {
	char* in = "FirstTest.txt";
	FILE* inF = fopen(in, "r");
	if (!inF) {
		perror("");
		FAIL();
	}
	int k = 0;
	graph_t* graph = GraphRead(inF, &k);
	ASSERT_EQ(graph, nullptr);
	GraphDelete(graph);
	fclose(inF);
}
TEST(VertexCoverTest, FunctionalTestNoSolutions) {
	char* in = "SecondTest.txt";
	char* out = "SecondResult";
	FILE* inF = fopen(in, "r");
	if (!inF) {
		perror("");
		FAIL();
	}
	int k = 0;
	graph_t* graph = GraphRead(inF, &k);
	if (!graph) {
		perror("");
		fclose(inF);
		FAIL();
	}
	FILE* outF = fopen(out, "w");
	if (!outF) {
		perror("");
		fclose(inF);
		GraphDelete(graph);
		FAIL();
	}
	int check = VertexCover(graph, k, outF);
	EXPECT_EQ(check, -1);
	GraphDelete(graph);
	fclose(inF);
	fclose(outF);
}

TEST(VertexCoverTest, FunctionalTestSolutionFound) {
	char* in = "ThirdTest.txt";
	char* out = "ThirdResult";
	FILE* inF = fopen(in, "r");
	if (!inF) {
		perror("");
		FAIL();
	}
	int k = 0;
	graph_t* graph = GraphRead(inF, &k);
	if (!graph) {
		perror("");
		fclose(inF);
		FAIL();
	}
	FILE* outF = fopen(out, "w");
	if (!outF) {
		perror("");
		fclose(inF);
		GraphDelete(graph);
		FAIL();
	}
	int check = VertexCover(graph, k, outF);
	EXPECT_EQ(check, 1);
	GraphDelete(graph);
	fclose(inF);
	fclose(outF);
}