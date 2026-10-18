#ifndef GRAPH_H
#define GRAPH_H

#define VERTICES 6       // Количество вершин в графе
#define MAX_EDGES 15     // Максимальное число ребер: (6 * 5) / 2

// Прототипы функций для Задания 1
void generateAdjMatrix(int adjMatrix[VERTICES][VERTICES]);
void printAdjMatrix(int adjMatrix[VERTICES][VERTICES]);
int countEdgesAdj(int adjMatrix[VERTICES][VERTICES]);
void analyzeVerticesAdj(int adjMatrix[VERTICES][VERTICES]);

// Прототипы функций для Задания 2
int buildIncMatrix(int adjMatrix[VERTICES][VERTICES], int incMatrix[VERTICES][MAX_EDGES]);
void printIncMatrix(int incMatrix[VERTICES][MAX_EDGES], int edgeCount);
void analyzeVerticesInc(int incMatrix[VERTICES][MAX_EDGES], int edgeCount);

#endif
