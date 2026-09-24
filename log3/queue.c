#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];
    struct node* next;
};

static struct node* head = NULL;
static struct node* last = NULL;

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

void queue_push(void)
{
    struct node* p = NULL;
    p = get_struct();
    if (head == NULL && p != NULL)
    {
        head = p;
        last = p;
    }
    else if (head != NULL && p != NULL)
    {
        last->next = p;
        last = p;
    }
}

void queue_review(void)
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

void queue_pop(void)
{
    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }
    struct node* temp = head;
    head = head->next;
    if (head == NULL) last = NULL;
    printf("Извлечен элемент: %s\n", temp->inf);
    free(temp);
}
