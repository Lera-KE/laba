#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long bubble_swaps = 0;
long long insertion_swaps = 0;
long long merge_swaps = 0;
long long heap_swaps = 0;
long long radix_swaps = 0;


void bubble_sort(int* arr, int n) {
    bubble_swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                bubble_swaps++;
            }
        }
    }
}


void insertion_sort(int* arr, int n) {
    insertion_swaps = 0;
    for (int i = 1; i < n; i++) {
        int k = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > k) {
            arr[j + 1] = arr[j];
            insertion_swaps++;
            j--;
        }
        arr[j + 1] = k;
    }
}


void merge_sort(int* arr, int n) {
    merge_swaps = 0;
    if (n < 2) return;

    int mid = n / 2;
    int* left = (int*)malloc(mid * sizeof(int));
    int* right = (int*)malloc((n - mid) * sizeof(int));

    for (int i = 0; i < mid; i++) left[i] = arr[i];
    for (int i = mid; i < n; i++) right[i - mid] = arr[i];

    merge_sort(left, mid);
    merge_sort(right, n - mid);

    int i = 0, j = 0, k = 0;
    while (i < mid && j < n - mid) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
        merge_swaps++;
    }
    while (i < mid) { arr[k++] = left[i++]; merge_swaps++; }
    while (j < n - mid) { arr[k++] = right[j++]; merge_swaps++; }

    free(left);
    free(right);
}


void heap_sort(int* arr, int n) {
    heap_swaps = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        int root = i;
        while (1) {
            int largest = root;
            int left = 2 * root + 1;
            int right = 2 * root + 2;

            if (left < n && arr[left] > arr[largest]) largest = left;
            if (right < n && arr[right] > arr[largest]) largest = right;

            if (largest == root) break;

            int temp = arr[root];
            arr[root] = arr[largest];
            arr[largest] = temp;
            heap_swaps++;
            root = largest;
        }
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heap_swaps++;

        int root = 0;
        while (1) {
            int largest = root;
            int left = 2 * root + 1;
            int right = 2 * root + 2;

            if (left < i && arr[left] > arr[largest]) largest = left;
            if (right < i && arr[right] > arr[largest]) largest = right;

            if (largest == root) break;

            int t = arr[root];
            arr[root] = arr[largest];
            arr[largest] = t;
            heap_swaps++;
            root = largest;
        }
    }
}


void radix_sort(int* arr, int n) {
    radix_swaps = 0;
    if (n <= 1) return;

    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }

    int* output = (int*)malloc(n * sizeof(int));
    int* count = (int*)malloc(10 * sizeof(int));

    for (int exp = 1; max / exp > 0; exp *= 10) {
        for (int i = 0; i < 10; i++) count[i] = 0;

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
            radix_swaps++;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }

    free(output);
    free(count);
}


double measure_time(void (*sort_func)(int*, int), int* arr, int n, long long* swaps, long long* counter) {
    int* copy = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) copy[i] = arr[i];
    *counter = 0;
    clock_t start = clock();
    sort_func(copy, n);
    clock_t end = clock();
    *swaps = *counter;
    free(copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}


int main() {
    int sizes[] = { 10, 1000, 10000, 100000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int* arr = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) arr[i] = rand();

        printf("Размер массива : % d\n", n);

        long long sw;
        double t;
        long long cnt;

        t = measure_time(bubble_sort, arr, n, &sw, &bubble_swaps);
        printf("Сортировка пузырьком : %f сек - %lld операций\n", t, sw);

        t = measure_time(insertion_sort, arr, n, &sw, &insertion_swaps);
        printf("Сортировка вставками : %f сек - %lld операций\n", t, sw);

        t = measure_time(merge_sort, arr, n, &sw, &merge_swaps);
        printf("Сортировка слиянием : %f сек - %lld операций\n", t, sw);

        t = measure_time(heap_sort, arr, n, &sw, &heap_swaps);
        printf("Пирамидальная сортировка : %f сек - %lld операций\n", t, sw);

        t = measure_time(radix_sort, arr, n, &sw, &radix_swaps);
        printf("Поразрядная сортировка : %fсек - %lld операций\n\n", t, sw);

        free(arr);
    }
    return 0;
}