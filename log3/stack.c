#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];
    struct node* next;
};

static struct node* head = NULL;

static struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];
    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }
    printf("Введите название объекта: \n");
    scanf("%255s", s);
    if (*s == 0)
    {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }
    strcpy(p->inf, s);
    p->next = NULL;
    return p;
}

void stack_push(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;
    p->next = head;
    head = p;
    printf("Элемент добавлен на вершину стека.\n");
}

void stack_review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }
    while (struc)
    {
        printf("Имя - %s, \n", struc->inf);
        struc = struc->next;
    }
}

void stack_pop(void)
{
    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }
    struct node* temp = head;
    head = head->next;
    printf("С вершины стека удален элемент: %s\n", temp->inf);
    free(temp);
}
