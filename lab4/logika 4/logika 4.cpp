#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_HEIGHT 10
#define MAX_WIDTH 80

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
struct Node* root = NULL;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;
        if (data < root->data) root->left = r;
        else root->right = r;
        return r;
    }
    if (data < r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);
    return root;
}

struct Node* CreateTreeUnique(struct Node* root, int data)
{
    if (root == NULL) {
        root = (struct Node*)malloc(sizeof(struct Node));
        if (root == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(0);
        }
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }
    if (data < root->data)
        root->left = CreateTreeUnique(root->left, data);
    else if (data > root->data)
        root->right = CreateTreeUnique(root->right, data);
    return root;
}

void InvertTree(struct Node* r)
{
    if (r == NULL) return;

    InvertTree(r->left);
    InvertTree(r->right);

    struct Node* temp = r->left;
    r->left = r->right;
    r->right = temp;
}

int GetHeight(struct Node* r) {
    if (r == NULL) return 0;
    int left_h = GetHeight(r->left);
    int right_h = GetHeight(r->right);
    return (left_h > right_h ? left_h : right_h) + 1;
}

void FillScreenBuffer(struct Node* r, char screen[MAX_HEIGHT][MAX_WIDTH], int level, int left, int right) {
    if (r == NULL || level >= MAX_HEIGHT) return;

    int x = (left + right) / 2;

    char buf[32];
    int len = sprintf_s(buf, sizeof(buf), "%d(%d)", r->data, level);

    int start_x = x - len / 2;
    for (int i = 0; i < len; i++) {
        if (start_x + i >= 0 && start_x + i < MAX_WIDTH - 1) {
            screen[level][start_x + i] = buf[i];
        }
    }

    FillScreenBuffer(r->left, screen, level + 1, left, x - 1);
    FillScreenBuffer(r->right, screen, level + 1, x + 1, right);
}

void print_tree_top_down(struct Node* r) {
    if (r == NULL) {
        printf("Дерево пустое\n");
        return;
    }

    int height = GetHeight(r);
    if (height > MAX_HEIGHT) {
        printf("Дерево слишком глубокое для красивого вывода в консоль.\n");
        return;
    }

    char screen[MAX_HEIGHT][MAX_WIDTH];
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            screen[i][j] = ' ';
        }
    }

    FillScreenBuffer(r, screen, 0, 0, MAX_WIDTH - 2);

    for (int i = 0; i < height; i++) {
        int last_char = MAX_WIDTH - 1;
        while (last_char > 0 && screen[i][last_char - 1] == ' ') {
            last_char--;
        }
        screen[i][last_char] = '\0';

        printf("%s\n\n", screen[i]);
    }
}

void FreeTree(struct Node* r)
{
    if (r == NULL) return;
    FreeTree(r->left);
    FreeTree(r->right);
    free(r);
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;

    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1) { start = 0; break; }
        root = CreateTree(root, root, D);
    }

    printf("\nДерево\n\n");
    print_tree_top_down(root);

    FreeTree(root);
    root = NULL;

    printf("-1 - окончание построения дерева\n");
    start = 1;
    while (start) {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1) { start = 0; break; }
        root = CreateTreeUnique(root, D);
    }

    printf("\nДерево без дубликатов\n\n");
    print_tree_top_down(root);

    FreeTree(root);
    root = NULL;

    return 0;
}
