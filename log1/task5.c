#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

struct student {
    char famil[20];
    char name[20];
    char facult[20];
    int Nomzach;
};
/*1*/
struct node {
    struct student data;
    struct node* next;
};

int main(void)
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    struct node* head = NULL;
    struct node* last = NULL;
    struct node* p;

    struct student stud;

    char search[20];
    char number[20];

    while (1)
    {
        printf("Введите фамилию: ");
        scanf("%19s", stud.famil);
        /*2*/
        if (strcmp(stud.famil, "*") == 0)
            break;

        printf("Введите имя: ");
        scanf("%19s", stud.name);

        printf("Введите факультет: ");
        scanf("%19s", stud.facult);

        printf("Введите номер зачётной книжки: ");
        scanf("%d", &stud.Nomzach);

        p = (struct node*)malloc(sizeof(struct node));

        if (p == NULL)
        {
            printf("Ошибка выделения памяти!\n");
            return 1;
        }

        p->data = stud;
        p->next = NULL;

        if (head == NULL)
        {
            head = p;
            last = p;
        }
        else
        {
            last->next = p;
            last = p;
        }

        printf("\n");
    }

    printf("\nВведите данные для поиска: ");
    scanf("%19s", search);

    printf("\nРезультаты поиска:\n");

    p = head;

    while (p != NULL)
    {
        sprintf(number, "%d", p->data.Nomzach);
        /*3*/
        if (strstr(p->data.famil, search) != NULL ||
            strstr(p->data.name, search) != NULL ||
            strstr(p->data.facult, search) != NULL ||
            strstr(number, search) != NULL)
        {
            printf("\nФамилия: %s", p->data.famil);
            printf("\nИмя: %s", p->data.name);
            printf("\nФакультет: %s", p->data.facult);
            printf("\nНомер зачётной книжки: %d\n", p->data.Nomzach);
        }

        p = p->next;
    }

    p = head;

    while (p != NULL)
    {
        struct node* temp = p;
        p = p->next;
        free(temp);
    }

    return 0;
}