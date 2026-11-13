#include <stdio.h>
#include <stdlib.h>

void generateAdjMatrix(int** adjMatrix, int vertices, int isDirected, int edgeChance) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (!isDirected && j < i) {
                adjMatrix[i][j] = adjMatrix[j][i];
                continue;
            }

            int val = (rand() % 100 < edgeChance) ? 1 : 0;
            adjMatrix[i][j] = val;

            if (!isDirected) {

                adjMatrix[j][i] = val;
            }
        }
    }
}

void printAdjMatrix(int** adjMatrix, int vertices) {
    printf("Матрица смежности графа (%d вершин):\n", vertices);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int countEdgesAdj(int** adjMatrix, int vertices, int isDirected) {
    int count = 0;
    for (int i = 0; i < vertices; i++) {
        int startJ = isDirected ? 0 : i;
        for (int j = startJ; j < vertices; j++) {
            if (adjMatrix[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

void analyzeVerticesAdj(int** adjMatrix, int vertices, int isDirected) {
    printf("Анализ вершин через матрицу смежности:\n");
    for (int i = 0; i < vertices; i++) {
        int degree = 0;
        int inDegree = 0;  
        int outDegree = 0; 

        for (int j = 0; j < vertices; j++) {
            if (isDirected) {
                if (adjMatrix[i][j] == 1) outDegree++; 
                if (adjMatrix[j][i] == 1) inDegree++;  
            }
            else {
                if (adjMatrix[i][j] == 1) {
                    if (i == j) degree += 2; 
                    else degree += 1;
                }
            }
        }

        if (isDirected) {
            degree = inDegree + outDegree;
            printf("Вершина %d (deg=%d, +deg=%d, -deg=%d)", i + 1, degree, inDegree, outDegree);
        }
        else {
            printf("Вершина %d (deg=%d)", i + 1, degree);
        }

        int connectionsToOthers = 0;
        int hasLoop = adjMatrix[i][i] == 1;
        for (int j = 0; j < vertices; j++) {
            if (i != j) {
                if (isDirected) {
                    if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
                        connectionsToOthers++;
                    }
                }
                else {
                    if (adjMatrix[i][j] == 1) {
                        connectionsToOthers++;
                    }
                }
            }
        }
        if (connectionsToOthers == 0) printf(" -> ИЗОЛИРОВАННАЯ");
        else if (outDegree == 1 && !hasLoop) printf(" -> КОНЦЕВАЯ");
        if (outDegree == 5) printf(" -> ДОМИНИРУЮЩАЯ");
        printf("\n");
    }
    printf("\n");
}
