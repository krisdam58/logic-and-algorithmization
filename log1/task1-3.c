//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h> 
//#include <time.h>   
//#include <locale.h>
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//    int size;
//    srand((int)time(NULL));
//
//    printf("Введите размер массива: ");
//    if (scanf("%d", &size) != 1 || size <= 0) {
//        printf("Ошибка!\n");
//        return 1;
//    }
//
//    int* array = (int*)malloc(size * sizeof(int));
//    if (array == NULL) {
//        printf("Ошибка: не удалось выделить память.\n");
//        return 1;
//    }
//
//    printf("Сгенерированный массив: ");
//    for (int i = 0; i < size; i++) {
//        array[i] = rand() % 100;
//        printf("%d ", array[i]);
//    }
//    printf("\n");
//
//    int min = array[0];
//    int max = array[0];
//
//    for (int i = 1; i < size; i++) {
//        if (array[i] < min) {
//            min = array[i];
//        }
//        if (array[i] > max) {
//            max = array[i];
//        }
//    }
//
//    int dif = max - min;
//    printf("Разница между max и min: %d\n", dif);
//    return 0;
//}
