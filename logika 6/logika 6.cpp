#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale>
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    int n;
    Node** head;
} AdjList;

int** allocMatrix(int n) {
    int** m = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        m[i] = (int*)calloc(n, sizeof(int));
    }
    return m;
}

void freeMatrix(int** m, int n) {
    if (!m) return;
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

int** generateRandomMatrix(int n, int probability) {
    int** m = allocMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((rand() % 100) < probability) {
                m[i][j] = m[j][i] = 1;
            }
        }
    }
    return m;
}

void printMatrix(int** m, int n, const char* title) {
    printf("\n%s (вершин: %d)\n     ", title, n);
    for (int i = 0; i < n; i++) {
        printf("v%-3d", i + 1);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("v%-3d ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%-4d", m[i][j]);
        }
        printf("\n");
    }
}

void printCartesianMatrix(int** m, int n1, int n2) {
    int total = n1 * n2;

    printf("\nДекартово произведение G1 X G2\n");
    printf("Всего вершин: %d:\n\n", total);

    for (int idx = 0; idx < total; idx++) {
        int i = idx / n2;
        int k = idx % n2;
        printf("Вершина %-2d -> (v%d, v%d)\n", idx + 1, i + 1, k + 1);
    }

    printf("\nМатрица смежности (все вершины 1-%d):\n     ", total);
    for (int j = 0; j < total; j++) {
        printf("%-3d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < total; i++) {
        printf("%-3d| ", i + 1);
        for (int j = 0; j < total; j++) {
            printf("%-3d", m[i][j]);
        }
        printf("\n");
    }
}

AdjList* createAdjList(int n) {
    AdjList* list = (AdjList*)malloc(sizeof(AdjList));
    list->n = n;
    list->head = (Node**)calloc(n, sizeof(Node*));
    return list;
}

void addEdgeToList(AdjList* list, int u, int v) {
    Node* curr = list->head[u];
    while (curr) {
        if (curr->vertex == v) return;
        curr = curr->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = list->head[u];
    list->head[u] = newNode;
}

void removeEdgeFromList(AdjList* list, int u, int v) {
    Node* curr = list->head[u];
    Node* prev = NULL;
    while (curr) {
        if (curr->vertex == v) {
            if (prev) prev->next = curr->next;
            else list->head[u] = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int hasSelfLoop(AdjList* list, int u) {
    Node* curr = list->head[u];
    while (curr) {
        if (curr->vertex == u) return 1;
        curr = curr->next;
    }
    return 0;
}

void freeAdjList(AdjList* list) {
    if (!list) return;
    for (int i = 0; i < list->n; i++) {
        Node* curr = list->head[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(list->head);
    free(list);
}

AdjList* matrixToAdjList(int** m, int n) {
    AdjList* list = createAdjList(n);
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) {
            if (m[i][j]) addEdgeToList(list, i, j);
        }
    }
    return list;
}

void printAdjList(AdjList* list, const char* title) {
    printf("\n%s (список смежности)\n", title);
    for (int i = 0; i < list->n; i++) {
        printf("Вершина v%d: ", i + 1);
        Node* curr = list->head[i];
        if (!curr) printf("нет смежных");
        while (curr) {
            printf("v%d ", curr->vertex + 1);
            curr = curr->next;
        }
        printf("\n");
    }
}

int** identifyVerticesMatrix(int** m, int n, int u, int v, int* newN) {
    if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
        printf("Ошибка: некорректные номера вершин!\n");
        return NULL;
    }
    *newN = n - 1;
    int** res = allocMatrix(*newN);

    int* map = (int*)malloc(n * sizeof(int));
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (i == u || i == v) map[i] = n - 2;
        else map[i] = idx++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j]) {
                int ni = map[i];
                int nj = map[j];
                res[ni][nj] = 1;
            }
        }
    }
    free(map);
    return res;
}

int** contractEdgeMatrix(int** m, int n, int u, int v, int* newN) {
    if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
        printf("Ошибка: некорректные номера вершин!\n");
        return NULL;
    }
    if (m[u][v] == 0) {
        printf("Ошибка: между вершинами v%d и v%d нет ребра!\n", u + 1, v + 1);
        return NULL;
    }
    int** res = identifyVerticesMatrix(m, n, u, v, newN);
    int z = *newN - 1;
    if (m[u][u] == 0 && m[v][v] == 0) {
        res[z][z] = 0;
    }
    return res;
}

int** splitVertexMatrix(int** m, int n, int u, int* newN) {
    if (u < 0 || u >= n) {
        printf("Ошибка: некорректный номер вершины!\n");
        return NULL;
    }
    *newN = n + 1;
    int** res = allocMatrix(*newN);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = m[i][j];
        }
    }

    for (int j = 0; j < n; j++) {
        if (m[u][j] && j != u) {
            res[n][j] = 1;
            res[j][n] = 1;
        }
    }

    if (m[u][u]) {
        res[n][n] = 1;
    }

    res[u][n] = 1;
    res[n][u] = 1;

    return res;
}

AdjList* identifyVerticesList(AdjList* list, int u, int v) {
    int n = list->n;
    if (u < 0 || u >= n || v < 0 || v >= n || u == v) return NULL;
    AdjList* res = createAdjList(n - 1);

    int* map = (int*)malloc(n * sizeof(int));
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (i == u || i == v) map[i] = n - 2;
        else map[i] = idx++;
    }

    for (int i = 0; i < n; i++) {
        Node* curr = list->head[i];
        while (curr) {
            int ni = map[i];
            int nj = map[curr->vertex];
            addEdgeToList(res, ni, nj);
            if (ni != nj) {
                addEdgeToList(res, nj, ni);
            }
            curr = curr->next;
        }
    }
    free(map);
    return res;
}

AdjList* contractEdgeList(AdjList* list, int u, int v) {
    int n = list->n;
    if (u < 0 || u >= n || v < 0 || v >= n || u == v) return NULL;
    Node* curr = list->head[u];
    int connected = 0;
    while (curr) {
        if (curr->vertex == v) { connected = 1; break; }
        curr = curr->next;
    }
    if (!connected) {
        printf("Ошибка (список): между вершинами v%d и v%d нет ребра!\n", u + 1, v + 1);
        return NULL;
    }

    int hadLoop = hasSelfLoop(list, u) || hasSelfLoop(list, v);
    AdjList* res = identifyVerticesList(list, u, v);
    int z = res->n - 1;
    if (!hadLoop) {
        removeEdgeFromList(res, z, z);
    }
    return res;
}

AdjList* splitVertexList(AdjList* list, int u) {
    int n = list->n;
    if (u < 0 || u >= n) return NULL;
    AdjList* res = createAdjList(n + 1);

    for (int i = 0; i < n; i++) {
        Node* curr = list->head[i];
        while (curr) {
            addEdgeToList(res, i, curr->vertex);
            curr = curr->next;
        }
    }

    Node* curr = list->head[u];
    while (curr) {
        int neighbor = curr->vertex;
        if (neighbor == u) {
            addEdgeToList(res, n, n);
        }
        else {
            addEdgeToList(res, n, neighbor);
            addEdgeToList(res, neighbor, n);
        }
        curr = curr->next;
    }

    addEdgeToList(res, u, n);
    addEdgeToList(res, n, u);

    return res;
}

int** unionGraphs(int** m1, int n1, int** m2, int n2, int* resN) {
    *resN = (n1 > n2) ? n1 : n2;
    int** res = allocMatrix(*resN);
    for (int i = 0; i < *resN; i++) {
        for (int j = 0; j < *resN; j++) {
            int e1 = (i < n1 && j < n1) ? m1[i][j] : 0;
            int e2 = (i < n2 && j < n2) ? m2[i][j] : 0;
            res[i][j] = e1 | e2;
        }
    }
    return res;
}

int** intersectionGraphs(int** m1, int n1, int** m2, int n2, int* resN) {
    *resN = (n1 < n2) ? n1 : n2;
    int** res = allocMatrix(*resN);
    for (int i = 0; i < *resN; i++) {
        for (int j = 0; j < *resN; j++) {
            res[i][j] = m1[i][j] & m2[i][j];
        }
    }
    return res;
}

int** ringSumGraphs(int** m1, int n1, int** m2, int n2, int* resN) {
    int maxN = (n1 > n2) ? n1 : n2;
    int** temp = allocMatrix(maxN);

    for (int i = 0; i < maxN; i++) {
        for (int j = 0; j < maxN; j++) {
            int e1 = (i < n1 && j < n1) ? m1[i][j] : 0;
            int e2 = (i < n2 && j < n2) ? m2[i][j] : 0;
            temp[i][j] = e1 ^ e2;
        }
    }
    int* active = (int*)calloc(maxN, sizeof(int));
    int count = 0;
    for (int i = 0; i < maxN; i++) {
        for (int j = 0; j < maxN; j++) {
            if (temp[i][j]) { active[i] = 1; break; }
        }
        if (active[i]) count++;
    }
    *resN = count;
    int** res = allocMatrix(count);
    int r = 0;
    for (int i = 0; i < maxN; i++) {
        if (!active[i]) continue;
        int c = 0;
        for (int j = 0; j < maxN; j++) {
            if (!active[j]) continue;
            res[r][c++] = temp[i][j];
        }
        r++;
    }
    free(active);
    freeMatrix(temp, maxN);
    return res;
}
//декартово произведение
int** cartesianProduct(int** m1, int n1, int** m2, int n2, int* resN) {
    *resN = n1 * n2;
    int** res = allocMatrix(*resN);
    for (int i = 0; i < n1; i++) {
        for (int k = 0; k < n2; k++) {
            for (int j = 0; j < n1; j++) {
                for (int l = 0; l < n2; l++) {
                    int u = i * n2 + k;
                    int v = j * n2 + l;
                    if ((i == j && m2[k][l]) || (k == l && m1[i][j])) {
                        res[u][v] = 1;
                    }
                }
            }
        }
    }
    return res;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));
    int n1, n2, prob1, prob2;
    printf("Введите количество вершин графа G1: ");
    scanf_s("%d", &n1);
    printf("Введите вероятность появления ребра для G1 (0-100%%): ");
    scanf_s("%d", &prob1);
    printf("Введите количество вершин графа G2: ");
    scanf_s("%d", &n2);
    printf("Введите вероятность появления ребра для G2 (0-100%%): ");
    scanf_s("%d", &prob2);
    int** M1 = generateRandomMatrix(n1, prob1);
    int** M2 = generateRandomMatrix(n2, prob2);
    printMatrix(M1, n1, "Матрица смежности M1 (Граф G1)");
    printMatrix(M2, n2, "Матрица смежности M2 (Граф G2)");
    AdjList* L1 = matrixToAdjList(M1, n1);
    AdjList* L2 = matrixToAdjList(M2, n2);
    printAdjList(L1, "Граф G1");
    printAdjList(L2, "Граф G2");
    int mainChoice = -1;
    while (mainChoice != 0) {
        printf("\nМеню операций:\n");
        printf("1. Унарные операции над графом G1\n");
        printf("2. Унарные операции над графом G2\n");
        printf("3. Бинарные операции над G1 и G2\n");
        printf("4. Показать исходные графы G1 и G2\n");
        printf("0. Завершить программу\n");
        printf("Выберите пункт: ");
        scanf_s("%d", &mainChoice);
        if (mainChoice == 1 || mainChoice == 2) {
            int** targetM = (mainChoice == 1) ? M1 : M2;
            AdjList* targetL = (mainChoice == 1) ? L1 : L2;
            int targetN = (mainChoice == 1) ? n1 : n2;
            const char* gName = (mainChoice == 1) ? "G1" : "G2";
            int unaryChoice = -1;
            while (unaryChoice != 0) {
                printf("\nУнарные операции над графом %s (вершины v1-v%d)\n", gName, targetN);
                printf("1. Отождествление вершин\n");
                printf("2. Стягивание ребра\n");
                printf("3. Расщепление вершины\n");
                printf("0. Вернуться в меню\n");
                printf("Выберите унарную операцию: ");
                scanf_s("%d", &unaryChoice);
                if (unaryChoice == 0) break;
                int u, v, newN;
                if (unaryChoice == 1) {
                    printf("Введите номера двух вершин для отождествления (1-%d): ", targetN);
                    scanf_s("%d %d", &u, &v);
                    int** resM = identifyVerticesMatrix(targetM, targetN, u - 1, v - 1, &newN);
                    if (resM) {
                        printMatrix(resM, newN, "Отождествление вершин (Матрица)");
                        freeMatrix(resM, newN);
                    }
                    AdjList* resL = identifyVerticesList(targetL, u - 1, v - 1);
                    if (resL) {
                        printAdjList(resL, "Отождествление вершин");
                        freeAdjList(resL);
                    }
                }
                else if (unaryChoice == 2) {
                    printf("Введите номера двух смежных вершин для стягивания ребра (1-%d): ", targetN);
                    scanf_s("%d %d", &u, &v);
                    int** resM = contractEdgeMatrix(targetM, targetN, u - 1, v - 1, &newN);
                    if (resM) {
                        printMatrix(resM, newN, "Стягивание ребра (Матрица)");
                        freeMatrix(resM, newN);
                    }
                    AdjList* resL = contractEdgeList(targetL, u - 1, v - 1);
                    if (resL) {
                        printAdjList(resL, "Стягивание ребра");
                        freeAdjList(resL);
                    }
                }
                else if (unaryChoice == 3) {
                    printf("Введите номер вершины для расщепления (1-%d): ", targetN);
                    scanf_s("%d", &u);
                    int** resM = splitVertexMatrix(targetM, targetN, u - 1, &newN);
                    if (resM) {
                        printMatrix(resM, newN, "Расщепление вершины (Матрица)");
                        freeMatrix(resM, newN);
                    }
                    AdjList* resL = splitVertexList(targetL, u - 1);
                    if (resL) {
                        printAdjList(resL, "Расщепление вершины");
                        freeAdjList(resL);
                    }
                }
                else {
                    printf("Неверный выбор!\n");
                }
            }
        }
        else if (mainChoice == 3) {
            int binChoice = -1;
            while (binChoice != 0) {
                printf("\nБинарные операции над G1 и G2\n");
                printf("1. Объединение G = G1 G2\n");
                printf("2. Пересечение G = G1 G2\n");
                printf("3. Кольцевая сумма G = G1 G2\n");
                printf("4. Декартово произведение G = G1 X G2\n");
                printf("0. Вернуться в меню\n");
                printf("Выберите бинарную операцию: ");
                scanf_s("%d", &binChoice);
                if (binChoice == 0) break;
                int resN;
                if (binChoice == 1) {
                    int** unM = unionGraphs(M1, n1, M2, n2, &resN);
                    printMatrix(unM, resN, "Объединение G1 G2");
                    freeMatrix(unM, resN);
                }
                else if (binChoice == 2) {
                    int** intM = intersectionGraphs(M1, n1, M2, n2, &resN);
                    printMatrix(intM, resN, "Пересечение G1 G2");
                    freeMatrix(intM, resN);
                }
                else if (binChoice == 3) {
                    int** ringM = ringSumGraphs(M1, n1, M2, n2, &resN);
                    if (resN == 0) {
                        printf("\nГрафы идентичны: кольцевая сумма пуста.\n");
                    }
                    else {
                        printMatrix(ringM, resN, "Кольцевая сумма G1 G2");
                    }
                    freeMatrix(ringM, resN);
                }
                else if (binChoice == 4) {
                    int** cartM = cartesianProduct(M1, n1, M2, n2, &resN);
                    printCartesianMatrix(cartM, n1, n2);
                    freeMatrix(cartM, resN);
                }
                else {
                    printf("Неверный выбор!\n");
                }
            }
        }
        else if (mainChoice == 4) {
            printMatrix(M1, n1, "Матрица смежности M1 (Граф G1)");
            printAdjList(L1, "Граф G1");
            printMatrix(M2, n2, "Матрица смежности M2 (Граф G2)");
            printAdjList(L2, "Граф G2");
        }
        else if (mainChoice != 0) {
            printf("Неверный пункт меню!\n");
        }
    }
    freeMatrix(M1, n1);
    freeMatrix(M2, n2);
    freeAdjList(L1);
    freeAdjList(L2);
    printf("Работа программы завершена.\n");
    return 0;
}