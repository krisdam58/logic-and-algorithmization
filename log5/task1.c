#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void generateAdjMatrix(int adjMatrix[VERTICES][VERTICES]) {
    for (int i = 0; i < VERTICES; i++) {
        adjMatrix[i][i] = 0;
        for (int j = i + 1; j < VERTICES; j++) {
            int val = rand() % 2;
            adjMatrix[i][j] = val;
            adjMatrix[j][i] = val;
        }
    }
}

void printAdjMatrix(int adjMatrix[VERTICES][VERTICES]) {
    printf("Матрица смежности графа (%d вершин):\n", VERTICES);
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int countEdgesAdj(int adjMatrix[VERTICES][VERTICES]) {
    int count = 0;
    for (int i = 0; i < VERTICES; i++) {
        for (int j = i + 1; j < VERTICES; j++) {
            if (adjMatrix[i][j] == 1) count++;
        }
    }
    return count;
}

void analyzeVerticesAdj(int adjMatrix[VERTICES][VERTICES]) {
    printf("Анализ вершин через матрицу смежности:\n");
    for (int i = 0; i < VERTICES; i++) {
        int degree = 0;
        for (int j = 0; j < VERTICES; j++) {
            if (adjMatrix[i][j] == 1) degree++;
        }
        printf("Вершина %d (deg=%d)", i + 1, degree);
        if (degree == 0) printf(" -> ИЗОЛИРОВАННАЯ");
        else if (degree == 1) printf(" -> КОНЦЕВАЯ");
        if (degree == VERTICES - 1) printf(" -> ДОМИНИРУЮЩАЯ");
        printf("\n");
    }
    printf("\n");
}
