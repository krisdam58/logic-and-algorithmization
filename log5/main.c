#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "graph.h"

int main() {
    setlocale(LC_ALL, "Russian");
    int adjMatrix[VERTICES][VERTICES];
    int incMatrix[VERTICES][MAX_EDGES];
    int edgeCount = 0;
    int choice;
    int isGenerated = 0;

    srand(time(NULL));

    while (1) {
        printf("================ ГЛАВНОЕ МЕНЮ ================\n");
        printf("1. Выполнить Задание 1 (Матрица смежности)\n");
        printf("2. Выполнить Задание 2 (Матрица инцидентности)\n");
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
            generateAdjMatrix(adjMatrix);
            printAdjMatrix(adjMatrix);
            int edges = countEdgesAdj(adjMatrix);
            printf("Размер графа (число ребер): %d\n\n", edges);
            analyzeVerticesAdj(adjMatrix);
            isGenerated = 1; // Флаг, что граф создан
            break;

        case 2:
            if (!isGenerated) {
                printf("Ошибка: сначала сгенерируйте граф в Задании 1!\n\n");
                break;
            }
            edgeCount = buildIncMatrix(adjMatrix, incMatrix);
            printIncMatrix(incMatrix, edgeCount);
            printf("Размер графа (через матрицу инцидентности): %d ребер\n\n", edgeCount);
            analyzeVerticesInc(incMatrix, edgeCount);
            break;

        default:
            printf("Неверный пункт меню. Попробуйте снова.\n\n");
        }
    }
    return 0;
}
