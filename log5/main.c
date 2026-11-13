#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "graph.h"

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));
    int vertices = 0;
    int choice;
    int isGenerated = 0;

    int** adjMatrix = NULL;
    int** incMatrix = NULL;
    int edgeCount = 0;
    int maxEdges = 0;

    int isDirected = 0;
    int edgeChance = 50; 

    while (1) {
        printf("1. Задание 1 (Матрица смежности)\n");
        printf("2. Задание 2 (Матрица инцидентности)\n");
        printf("0. Выход из программы\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Завершение.\n");
            break;
        }
        printf("\n");

        if (choice == 0) {
            printf("Программа завершена.\n");
            break;
        }

        switch (choice) {
        case 1:
            if (isGenerated) {
                for (int i = 0; i < vertices; i++) {
                    free(adjMatrix[i]);
                }
                free(adjMatrix);
                isGenerated = 0;
            }

            printf("Введите количество вершин графа: ");
            if (scanf("%d", &vertices) != 1 || vertices <= 0) {
                printf("Некорректное количество вершин!\n\n");
                break;
            }

            printf("Выберите тип графа (0 - неориентированный, 1 - ориентированный): ");
            if (scanf("%d", &isDirected) != 1 || (isDirected != 0 && isDirected != 1)) {
                printf("Некорректный выбор типа графа!\n\n");
                break;
            }

            printf("Введите шанс появления ребра (в процентах от 0 до 100): ");
            if (scanf("%d", &edgeChance) != 1 || edgeChance < 0 || edgeChance > 100) {
                printf("Некорректный процент!\n\n");
                break;
            }

            if (isDirected) {
                maxEdges = vertices * vertices;
            }
            else {
                maxEdges = (vertices * (vertices + 1)) / 2;
            }

            adjMatrix = (int**)malloc(vertices * sizeof(int*));
            for (int i = 0; i < vertices; i++) {
                adjMatrix[i] = (int*)malloc(vertices * sizeof(int));
            }

            generateAdjMatrix(adjMatrix, vertices, isDirected, edgeChance);
            printAdjMatrix(adjMatrix, vertices);

            int edges = countEdgesAdj(adjMatrix, vertices, isDirected);
            printf("Размер графа: %d\n\n", edges);

            analyzeVerticesAdj(adjMatrix, vertices, isDirected);
            isGenerated = 1;
            break;

        case 2:
            if (!isGenerated) {
                printf("Ошибка: сначала сгенерируйте граф в пункте 1!\n\n");
                break;
            }

            if (incMatrix != NULL) {
                for (int i = 0; i < vertices; i++) {
                    free(incMatrix[i]);
                }
                free(incMatrix);
            }

            incMatrix = (int**)malloc(vertices * sizeof(int*));
            for (int i = 0; i < vertices; i++) {
                incMatrix[i] = (int*)malloc(maxEdges * sizeof(int));
            }

            edgeCount = buildIncMatrix(adjMatrix, vertices, incMatrix, maxEdges, isDirected);
            printIncMatrix(incMatrix, vertices, edgeCount);

            printf("Размер графа (через матрицу инцидентности): %d ребер\n\n", edgeCount);
            analyzeVerticesInc(incMatrix, vertices, edgeCount, isDirected);
            break;

        default:
            printf("Неверный пункт меню. Попробуйте снова.\n\n");
        }
    }

    if (isGenerated) {
        for (int i = 0; i < vertices; i++) {
            free(adjMatrix[i]);
        }
        free(adjMatrix);
    }
    if (incMatrix != NULL) {
        for (int i = 0; i < vertices; i++) {
            free(incMatrix[i]);
        }
        free(incMatrix);
    }

    return 0;
}