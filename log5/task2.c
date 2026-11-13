#include <stdio.h>
#include <stdlib.h>

int buildIncMatrix(int** adjMatrix, int vertices, int** incMatrix, int maxEdges, int isDirected) {
    int edgeCount = 0;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < maxEdges; j++) {
            incMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < vertices; i++) {
        int startJ = isDirected ? 0 : i;
        for (int j = startJ; j < vertices; j++) {
            if (adjMatrix[i][j] == 1) {
                if (i == j) {
                    incMatrix[i][edgeCount] = 2;
                }
                else {
                    if (isDirected) {
                        incMatrix[i][edgeCount] = -1; 
                        incMatrix[j][edgeCount] = 1;  
                    }
                    else {
                        incMatrix[i][edgeCount] = 1;
                        incMatrix[j][edgeCount] = 1;
                    }
                }
                edgeCount++;
            }
        }
    }
    return edgeCount;
}

void printIncMatrix(int** incMatrix, int vertices, int edgeCount) {
    if (edgeCount == 0) {
        printf("Матрица инцидентности пуста (в графе нет ребер).\n\n");
        return;
    }
    printf("Матрица инцидентности графа (%d ребер):\n", edgeCount);
    for (int i = 0; i < vertices; i++) {
        printf("V%d: ", i + 1);
        for (int j = 0; j < edgeCount; j++) {
            printf("%2d ", incMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void analyzeVerticesInc(int** incMatrix, int vertices, int edgeCount, int isDirected) {
    printf("Анализ вершин через матрицу инцидентности:\n");

    for (int i = 0; i < vertices; i++) {
        int degree = 0;
        int inDegree = 0;
        int outDegree = 0;
        int hasLoop = 0;

        int* connectedTo = (int*)calloc(vertices, sizeof(int));

        for (int j = 0; j < edgeCount; j++) {
            if (isDirected) {
                int nonZeroCount = 0;
                for (int v = 0; v < vertices; v++) {
                    if (incMatrix[v][j] != 0) nonZeroCount++;
                }

                if (incMatrix[i][j] == 2) {
                    inDegree++;
                    outDegree++;
                    degree += 2;
                    hasLoop = 1;
                }
                else if (incMatrix[i][j] == -1) {
                    outDegree++;
                    degree++;
                    for (int v = 0; v < vertices; v++) {
                        if (incMatrix[v][j] == 1) { connectedTo[v] = 1; break; }
                    }
                }
                else if (incMatrix[i][j] == 1) {
                    inDegree++;
                    degree++;
                    for (int v = 0; v < vertices; v++) {
                        if (incMatrix[v][j] == -1) { connectedTo[v] = 1; break; }
                    }
                }
            }
            else {
                if (incMatrix[i][j] == 2) {
                    degree += 2;
                    hasLoop = 1;
                }
                else if (incMatrix[i][j] == 1) {
                    degree += 1;
                    for (int v = 0; v < vertices; v++) {
                        if (v != i && incMatrix[v][j] == 1) {
                            connectedTo[v] = 1;
                            break;
                        }
                    }
                }
            }
        }

        if (isDirected) {
            printf("Вершина %d (deg=%d, +deg=%d, -deg=%d)", i + 1, degree, inDegree, outDegree);
        }
        else {
            printf("Вершина %d (deg=%d)", i + 1, degree);
        }

        int connectionsToOthers = 0;
        for (int v = 0; v < vertices; v++) {
            if (v != i && connectedTo[v] == 1) {
                connectionsToOthers++;
            }
        }
        if (connectionsToOthers == 0) printf(" -> ИЗОЛИРОВАННАЯ");
        else if (outDegree == 1 && !hasLoop) printf(" -> КОНЦЕВАЯ");
        if (outDegree == 5) printf(" -> ДОМИНИРУЮЩАЯ");
        printf("\n");

        free(connectedTo);
    }
    printf("\n");
}
