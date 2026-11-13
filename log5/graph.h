#ifndef GRAPH_H
#define GRAPH_H

void generateAdjMatrix(int** adjMatrix, int vertices, int isDirected, int edgeChance);
void printAdjMatrix(int** adjMatrix, int vertices);
int countEdgesAdj(int** adjMatrix, int vertices, int isDirected);
void analyzeVerticesAdj(int** adjMatrix, int vertices, int isDirected);

int buildIncMatrix(int** adjMatrix, int vertices, int** incMatrix, int maxEdges, int isDirected);
void printIncMatrix(int** incMatrix, int vertices, int edgeCount);
void analyzeVerticesInc(int** incMatrix, int vertices, int edgeCount, int isDirected);

#endif
