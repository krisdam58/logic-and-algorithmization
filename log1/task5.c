#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

struct student {
    char famil[20];  
    char name[20];   
    char facult[20]; 
    int Nomzach;
};

int main(void) {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    struct student stud[3]; 
    int i;
    char search_famil[20];
    int found = 0;

    for (i = 0; i < 3; i++) {
        printf("Введите фамилию студента: ");
        scanf("%19s", stud[i].famil);

        printf("Введите имя студента %s: ", stud[i].famil);
        scanf("%19s", stud[i].name);

        printf("Введите название факультета студента %s %s: ", stud[i].famil, stud[i].name);
        scanf("%19s", stud[i].facult);

        printf("Введите номер зачётной книжки студента %s %s: ", stud[i].famil, stud[i].name);
        scanf("%d", &stud[i].Nomzach);
        printf("\n");
    }

    printf("Введите фамилию для поиска: ");
    scanf("%19s", search_famil);

    printf("\nРезультаты поиска:\n");
    for (i = 0; i < 3; i++) {
        if (strcmp(stud[i].famil, search_famil) == 0) {
            printf("Студент %s %s обучается на факультете %s, номер зачётной книжки: %d\n",
                stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
            found = 1;
        }
    }

    if (!found) {
        printf("Студент с фамилией %s не найден.\n", search_famil);
    }

    return 0;
}
