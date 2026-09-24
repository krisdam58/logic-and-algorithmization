#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];     
    int priority;     
    struct node* next;
};

static struct node* head = NULL;

static struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];
    int pr;

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

    printf("Введите приоритет объекта (число > 0, где 1 - высший): ");
    /* Цикл while для контроля корректности ввода приоритета */
    while (scanf("%d", &pr) != 1 || pr <= 0) {
        printf("Ошибка! Приоритет должен быть строго больше 0.\n");
        printf("Повторите ввод приоритета: ");
        while (getchar() != '\n');
    }

    strcpy(p->inf, s);
    p->priority = pr;
    p->next = NULL;
    return p;
}

void priority_queue_push(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;

    if (head == NULL || p->priority <= head->priority)
    {
        p->next = head;
        head = p;
    }
    else
    {
        struct node* current = head;
        while (current->next != NULL && current->next->priority < p->priority)
        {
            current = current->next;
        }
        p->next = current->next;
        current->next = p;
    }
    printf("Элемент успешно добавлен.\n");
}

void priority_queue_review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }
    while (struc)
    {
        printf("Имя - %s, [Приоритет: %d]\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

void priority_queue_delete_any(void)
{
    char name[256];
    struct node* struc = head;
    struct node* prev = NULL; 
    int flag = 0;

    printf("Введите название объекта для удаления: ");
    scanf("%255s", name);

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head = struc->next;
        free(struc);
        struc = head;
    }
    else
    {
        prev = struc;
        struc = struc->next;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;
            if (struc->next)
            {
                if (prev != NULL) {
                    prev->next = struc->next;
                }
                free(struc);
                if (prev != NULL) {
                    struc = prev->next;
                }
                else {
                    struc = head;
                }
            }
            else
            {
                if (prev != NULL) {
                    prev->next = NULL;
                }
                free(struc);
                printf("Элемент успешно удален.\n");
                return;
            }
        }
        else
        {
            prev = struc;
            struc = struc->next;
        }
    }

    if (flag == 0)
    {
        printf("Элемент не найден\n");
        return;
    }
    printf("Элемент успешно удален.\n");
}

