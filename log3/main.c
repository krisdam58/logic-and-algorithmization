#include <stdio.h>
#include "priority_queue.h"
#include "queue.h"
#include "stack.h"
#include <locale.h>

void menu_priority_queue(void) {
    setlocale(LC_ALL, "Russian");
    int choice;
    while (1) {
        printf("\n--- ЗАДАНИЕ 1: ПРИОРИТЕТНАЯ ОЧЕРЕДЬ ---\n");
        printf("1. Добавить элемент (с учетом приоритета)\n");
        printf("2. Посмотреть очередь\n");
        //printf("3. Удалить любой элемент по имени\n");
        printf("3. Извлечение из вершины\n");
        printf("4. Изменение имени по приоритету\n");
        printf("0. Вернуться в главное меню\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1: priority_queue_push(); break;
        case 2: priority_queue_review(); break;
            //case 3: priority_queue_delete_any(); break;
        case 3: prioritet_stack_pop(); break;
        case 4: name_by_priority(); break;
        case 0: return;
        default: printf("Неверный пункт меню.\n");
        }
    }
}

void menu_queue(void) {
    setlocale(LC_ALL, "Russian");
    int choice;
    while (1) {
        printf("\n--- ЗАДАНИЕ 2: ОЧЕРЕДЬ (FIFO) ---\n");
        printf("1. Добавить элемент в очередь\n");
        printf("2. Посмотреть очередь\n");
        printf("3. Извлечь элемент из очереди (из начала)\n");
        printf("0. Вернуться в главное меню\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1: queue_push(); break;
        case 2: queue_review(); break;
        case 3: queue_pop(); break;
        case 0: return;
        default: printf("Неверный пункт меню.\n");
        }
    }
}

void menu_stack(void) {
    setlocale(LC_ALL, "Russian");
    int choice;
    while (1) {
        printf("\n--- ЗАДАНИЕ 3: СТЕК (LIFO) ---\n");
        printf("1. Добавить элемент в стек\n");
        printf("2. Посмотреть стек\n");
        printf("3. Извлечь элемент из стека\n");
        printf("0. Вернуться в главное меню\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1: stack_push(); break;
        case 2: stack_review(); break;
        case 3: stack_pop(); break;
        case 0: return;
        default: printf("Неверный пункт меню.\n");
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int task_choice;
    while (1) {
        printf("\n================ ГЛАВНОЕ МЕНЮ ================\n");
        printf("1. Работа с Приоритетной очередью\n");
        printf("2. Работа c Очередью\n");
        printf("3. Работа со Стеком\n");
        printf("0. Выход из программы\n");
        printf("Выберите задание: ");

        if (scanf("%d", &task_choice) != 1) {
            printf("Неверный ввод!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (task_choice) {
        case 1: menu_priority_queue(); break;
        case 2: menu_queue(); break;
        case 3: menu_stack(); break;
        case 0:
            printf("Программа завершена.\n");
            return 0;
        default:
            printf("Такого задания не существует. Попробуйте снова.\n");
        }
    }
    return 0;
}
