#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define N 50000

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;

    i = left; j = right;

    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

void run_shell(int* a, int n) { shell(a, n); }
void run_qs(int* a, int n) { qs(a, 0, n - 1); }

int cmp(const void* p, const void* q) { return *(int*)p - *(int*)q; }
void run_qsort(int* a, int n) { qsort(a, n, sizeof(int), cmp); }

void gen_random(int* a, int n) { for (int i = 0; i < n; i++) a[i] = rand(); }
void gen_ascending(int* a, int n) { for (int i = 0; i < n; i++) a[i] = i; }
void gen_descending(int* a, int n) { for (int i = 0; i < n; i++) a[i] = n - i; }
void gen_half(int* a, int n) {
    for (int i = 0; i < n / 2; i++) a[i] = i;
    for (int i = n / 2; i < n; i++) a[i] = n - (i - n / 2);
}

double time_of(void (*sort)(int*, int), void (*gen)(int*, int))
{
    int* a = (int*)malloc(N * sizeof(int));
    gen(a, N);

    clock_t t0 = clock();
    sort(a, N);
    clock_t t1 = clock();

    free(a);
    return (double)(t1 - t0) / CLOCKS_PER_SEC;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    const char* names[4] = {
        "Случайный          ",
        "Возрастающий       ",
        "Убывающий          ",
        "Половина возр/убыв "
    };
    void (*gens[4])(int*, int) = {
        gen_random, gen_ascending, gen_descending, gen_half
    };

    srand((unsigned)time(NULL));

    printf("N = %d\n\n", N);
    printf("%-18s %-10s %-10s %-10s\n", "Тип массива", "Shell", "QS", "qsort");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < 4; i++) {
        printf("%-18s %-10.4f %-10.4f %-10.4f\n",
            names[i],
            time_of(run_shell, gens[i]),
            time_of(run_qs, gens[i]),
            time_of(run_qsort, gens[i]));
    }
    return 0;
}

