#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph_labs.h"

void runIterativeDFSMatrix(int** G, int size) {
    bool* NUM = (bool*)calloc(size, sizeof(bool));

    int* stack = (int*)malloc(size * sizeof(int));
    int top = -1;

    for (int startVertex = 0; startVertex < size; startVertex++) {
        if (NUM[startVertex] == false) {

            stack[++top] = startVertex;

            while (top >= 0) {
                int v = stack[top--];

                if (NUM[v] == false) {
                    NUM[v] = true;
                    printf("%d ", v + 1);
                }

                for (int i = size - 1; i >= 0; i--) {
                    if (G[v][i] == 1 && NUM[i] == false) {
                        stack[++top] = i;
                    }
                }
            }
        }
    }

    free(stack);
    free(NUM);
}
