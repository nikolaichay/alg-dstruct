#include "pch.h"
#include "VertexCover.h"
#include "VertexCover.c"

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
load test results (cmake build type release):
Time: 0.006s to generate graph file (size 60, k = 4)
	  88.18s to read and walk around the graph
RAM:  up to 1.089 MiB
*/

const char* filename = "InStress.txt";
const int verticesCount = 60;
TEST(StressTest, GraphGeneration) {
	const int maxNeighbourDelta = (int)(0.5 * verticesCount);
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

TEST(StressTest, GraphCover) {
	const char* filenameOut = "OutStress";
	FILE* graphFile = fopen(filename, "r");
	if (!graphFile) {
		perror("Error while opening file");
		FAIL();
	}
	FILE* outFile = fopen(filenameOut, "w");
	if (!outFile) {
		fclose(graphFile);
		perror("Error while opening file");
		FAIL();
	}
	VertexCoverFile(graphFile, outFile);
	fclose(graphFile);
	fclose(outFile);
}
TEST(VertexCoverTest, FunctionalTestIncorrectData) {
	char* in = "FirstTest.txt";
	FILE* inF = fopen(in, "r");
	char* out = "FirstResult.txt";
	FILE* outF = fopen(out, "w");
	if (!inF) {
		perror("");
		FAIL();
	}
	int check = VertexCoverFile(inF, outF);
	EXPECT_EQ(check, 0);
	fclose(inF);
	fclose(outF);
}
TEST(VertexCoverTest, FunctionalTestNoSolutions) {
	char* in = "SecondTest.txt";
	char* out = "SecondResult.txt";
	char* ans = "SecondAnswer.txt";
	FILE* inF = fopen(in, "r");
	if (!inF) {
		perror("");
		FAIL();
	}
	FILE* outF = fopen(out, "w");
	if (!outF) {
		perror("");
		fclose(inF);
		FAIL();
	}
	int check = VertexCoverFile(inF, outF);
	ASSERT_EQ(check, 1);
	fclose(inF);
	fclose(outF);
	outF = fopen(out, "r");
	if (!outF) {
		perror("");
		FAIL();
	}
	FILE* ansF = fopen(ans, "r");
	if (!ansF) {
		fclose(outF);
		perror("");
		FAIL();
	}
	int a;
	int b;
	fscanf(outF, "%d", &a);
	fscanf(ansF, "%d", &b);
	EXPECT_EQ(a, b);
	fclose(outF);
	fclose(ansF);
}

TEST(VertexCoverTest, FunctionalTestSolutionFound) {
	char* in = "ThirdTest.txt";
	char* out = "ThirdResult.txt";
	char* ans = "ThirdAnswer.txt";
	FILE* inF = fopen(in, "r");
	if (!inF) {
		perror("");
		FAIL();
	}
	FILE* outF = fopen(out, "w");
	if (!outF) {
		perror("");
		fclose(inF);
		FAIL();
	}
	int check = VertexCoverFile(inF, outF);
	EXPECT_EQ(check, 1);
	fclose(inF);
	fclose(outF);
	outF = fopen(out, "r");
	if (!outF) {
		perror("");
		FAIL();
	}
	FILE* ansF = fopen(ans, "r");
	if (!ansF) {
		fclose(outF);
		perror("");
		FAIL();
	}
	int a, b;
	a = 0;
	b = 0;
	while (fscanf(outF, "%d", &a) != EOF && fscanf(ansF, "%d", &b) != EOF) {
		EXPECT_EQ(a, b);
	}
	fclose(outF);
	fclose(ansF);
}