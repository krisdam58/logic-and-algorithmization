#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph_labs.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    int size;
    int edgePercentage;

    srand(time(NULL));

    printf("Введите количество вершин графа: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Ошибка ввода размера!\n");
        return 1;
    }

    printf("Введите процент появления ребер (0-100): ");
    if (scanf("%d", &edgePercentage) != 1 || edgePercentage < 0 || edgePercentage > 100) {
        printf("Ошибка ввода процента!\n");
        return 1;
    }

    int** G = allocateMatrix(size);

    printf("\n================ ЗАДАНИЕ 1 ================\n");
    generateGraphMatrix(G, size, edgePercentage);
    printf("Сгенерированная матрица смежности графа:\n");
    printGraphMatrix(G, size);

    printf("\nРекурсивный DFS (Матрица смежности):\n");
    runRecursiveDFSMatrix(G, size);
    printf("\n");

    Node** adjLists = convertMatrixToLists(G, size);
    printf("\nРекурсивный DFS (Списки смежности):\n");
    runRecursiveDFSList(adjLists, size);
    printf("\n");

    printf("\n================ ЗАДАНИЕ 2 ================\n");
    printf("Итеративный DFS со стеком (Матрица смежности):\n");
    runIterativeDFSMatrix(G, size);
    printf("\n");

    freeMatrix(G, size);
    freeAdjLists(adjLists, size);

    return 0;
}
