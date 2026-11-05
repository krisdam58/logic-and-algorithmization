#ifndef GRAPH_LABS_H
#define GRAPH_LABS_H

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

int** allocateMatrix(int size);
void freeMatrix(int** G, int size);
void generateGraphMatrix(int** G, int size, int edgePercentage);
void printGraphMatrix(int** G, int size);
void runRecursiveDFSMatrix(int** G, int size);

Node* createNode(int v);
Node** convertMatrixToLists(int** G, int size);
void freeAdjLists(Node** adjLists, int size);
void runRecursiveDFSList(Node** adjLists, int size);

void runIterativeDFSMatrix(int** G, int size);

#endif 
