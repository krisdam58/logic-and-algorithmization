#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define VERTICES 6 // ���������� ������ � �����

int main() {
    setlocale(LC_ALL, "Russian");
    int adjMatrix[VERTICES][VERTICES];
    int i, j;
    int edgeCount = 0;

    // ������������� ���������� ��������� �����
    srand(time(NULL));

    // 1. ��������� ������� ��������� ��� ������������������ �����
    for (i = 0; i < VERTICES; i++) {
        adjMatrix[i][i] = 0; // ����� �����������
        for (j = i + 1; j < VERTICES; j++) {
            int val = rand() % 2;
            adjMatrix[i][j] = val;
            adjMatrix[j][i] = val; // ���������
        }
    }

    // ����� ������� ���������
    printf("������� ��������� ����� (%d ������):\n", VERTICES);
    for (i = 0; i < VERTICES; i++) {
        for (j = 0; j < VERTICES; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // 2. ����������� ������� ����� (���������� ����)
    for (i = 0; i < VERTICES; i++) {
        for (j = i + 1; j < VERTICES; j++) {
            if (adjMatrix[i][j] == 1) {
                edgeCount++;
            }
        }
    }
    printf("������ ����� (���������� �����): %d\n\n", edgeCount);

    // 3. ������ � ������������� ������
    printf("�������������� ������ (���������� � 1):\n");
    for (i = 0; i < VERTICES; i++) {
        int degree = 0;
        for (j = 0; j < VERTICES; j++) {
            if (adjMatrix[i][j] == 1) {
                degree++;
            }
        }

        printf("������� %d: ������� = %d", i + 1, degree);

        if (degree == 0) {
            printf(" -> �������������");
        }
        else if (degree == 1) {
            printf(" -> ��������");
        }

        if (degree == VERTICES - 1) {
            printf(" -> ������������");
        }
        printf("\n");
    }

    return 0;
}
