#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

static const int SIZES[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
static const int NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

void multiply(int N, const int* a, const int* b, int* c)
{
    int i, j, r;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int elem_c = 0;
            const int* ai = a + i * N;
            for (r = 0; r < N; r++) {
                elem_c += ai[r] * b[r * N + j];
            }
            c[i * N + j] = elem_c;
        }
    }
}

void fill_random(int N, int* m)
{
    int i;
    for (i = 0; i < N * N; i++)
        m[i] = rand() % 100 + 1;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    srand((unsigned)time(NULL));

    printf("    N        N^3 (операций)  Время (сек)\n");

    for (int k = 0; k < NUM_SIZES; k++) {
        int N = SIZES[k];
        size_t elems = (size_t)N * (size_t)N;

        int* a = (int*)malloc(elems * sizeof(int));
        int* b = (int*)malloc(elems * sizeof(int));
        int* c = (int*)malloc(elems * sizeof(int));

        if (!a || !b || !c) {
            fprintf(stderr, "Не хватает памяти для N = %d\n", N);
            free(a); free(b); free(c);
            continue;
        }

        fill_random(N, a);
        fill_random(N, b);

        clock_t start = clock();
        multiply(N, a, b, c);
        clock_t end = clock();

        double t = (double)(end - start) / CLOCKS_PER_SEC;
        double n3 = (double)N * (double)N * (double)N;

        printf("%8d%15.0f%15.6f\n", N, n3, t);

        free(a); free(b); free(c);
    }
    return 0;
}