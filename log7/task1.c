#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph_labs.h"

int** allocateMatrix(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int**)malloc(size * sizeof(int));
    }
    return G;
}

void freeMatrix(int** G, int size) {
    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);
}

void generateGraphMatrix(int** G, int size, int edgePercentage) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            int randomVal = (rand() % 100) + 1;

            if (randomVal <= edgePercentage) {
                G[i][j] = 1;
                G[j][i] = 1; 
            }
            else {
                G[i][j] = 0;
                G[j][i] = 0;
            }
        }
    }
}

void printGraphMatrix(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

static void DFSMatrix(int v, int** G, int size, bool* NUM) {
    NUM[v] = true;
    printf("%d ", v + 1);

    for (int i = 0; i < size; i++) {
        if (G[v][i] == 1 && NUM[i] == false) {
            DFSMatrix(i, G, size, NUM);
        }
    }
}

void runRecursiveDFSMatrix(int** G, int size) {
    bool* NUM = (bool*)calloc(size, sizeof(bool));

    for (int v = 0; v < size; v++) {
        if (NUM[v] == false) {
            DFSMatrix(v, G, size, NUM);
        }
    }
    free(NUM);
}

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Node** convertMatrixToLists(int** G, int size) {
    Node** adjLists = (Node**)malloc(size * sizeof(Node*));

    for (int i = 0; i < size; i++) {
        adjLists[i] = NULL;
        for (int j = size - 1; j >= 0; j--) {
            if (G[i][j] == 1) {
                Node* newNode = createNode(j);
                newNode->next = adjLists[i];
                adjLists[i] = newNode;
            }
        }
    }
    return adjLists;
}

void freeAdjLists(Node** adjLists, int size) {
    for (int i = 0; i < size; i++) {
        Node* temp = adjLists[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(adjLists);
}

static void DFSList(int v, Node** adjLists, bool* NUM) {
    NUM[v] = true;
    printf("%d ", v + 1);

    Node* temp = adjLists[v];
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (NUM[connectedVertex] == false) {
            DFSList(connectedVertex, adjLists, NUM);
        }
        temp = temp->next;
    }
}

void runRecursiveDFSList(Node** adjLists, int size) {
    bool* NUM = (bool*)calloc(size, sizeof(bool));

    for (int v = 0; v < size; v++) {
        if (NUM[v] == false) {
            DFSList(v, adjLists, NUM);
        }
    }
    free(NUM);
}
