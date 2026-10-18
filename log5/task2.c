#include <stdio.h>
#include "graph.h"

int buildIncMatrix(int adjMatrix[VERTICES][VERTICES], int incMatrix[VERTICES][MAX_EDGES]) {
    int edgeCount = 0;
    // Обнуление
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < MAX_EDGES; j++) incMatrix[i][j] = 0;
    }
    // Заполнение
    for (int i = 0; i < VERTICES; i++) {
        for (int j = i + 1; j < VERTICES; j++) {
            if (adjMatrix[i][j] == 1) {
                incMatrix[i][edgeCount] = 1;
                incMatrix[j][edgeCount] = 1;
                edgeCount++;
            }
        }
    }
    return edgeCount;
}

void printIncMatrix(int incMatrix[VERTICES][MAX_EDGES], int edgeCount) {
    printf("Матрица инцидентности графа (%d ребер):\n", edgeCount);
    for (int i = 0; i < VERTICES; i++) {
        printf("V%d: ", i + 1);
        for (int j = 0; j < edgeCount; j++) {
            printf("%d ", incMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void analyzeVerticesInc(int incMatrix[VERTICES][MAX_EDGES], int edgeCount) {
    printf("Анализ вершин через матрицу инцидентности:\n");
    for (int i = 0; i < VERTICES; i++) {
        int degree = 0;
        for (int j = 0; j < edgeCount; j++) {
            if (incMatrix[i][j] == 1) degree++;
        }
        printf("Вершина %d (deg=%d)", i + 1, degree);
        if (degree == 0) printf(" -> ИЗОЛИРОВАННАЯ");
        else if (degree == 1) printf(" -> КОНЦЕВАЯ");
        if (degree == VERTICES - 1) printf(" -> ДОМИНИРУЮЩАЯ");
        printf("\n");
    }
    printf("\n");
}
