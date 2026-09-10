#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    int rows, cols;

    srand(time(NULL));

    printf("Введите количество строк: ");
    scanf("%d", &rows);
    printf("Введите количество столбцов: ");
    scanf("%d", &cols);

    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    printf("\nСгенерированный массив:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 81 - 30;
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Суммы по строкам:\n");
    for (int i = 0; i < rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < cols; j++) {
            row_sum += matrix[i][j];
        }
        printf("Строка %d: %d\n", i + 1, row_sum);
    }


    printf("Суммы по столбцам:\n");
    for (int j = 0; j < cols; j++) {
        int col_sum = 0;
        for (int i = 0; i < rows; i++) {
            col_sum += matrix[i][j];
        }
        printf("Столбец %d: %d\n", j + 1, col_sum);
    }

    int sum = 0;
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int d = (i >= j) ? 1 : 0;
            sum += matrix[i][j] * d;
            count += d;
        }
    }

    printf("\nСумма элементов ниже и на главной диагонали: %d\n", sum);
    printf("Количество элементов ниже и на главной диагонали: %d\n", count);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}