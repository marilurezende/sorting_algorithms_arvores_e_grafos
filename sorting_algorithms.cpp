#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000   


void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void copyArray(int src[], int dest[], int n) {
    for(int i = 0; i < n; i++)
        dest[i] = src[i];
}


void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


void selectionSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        int min = i;
        for(int j = i+1; j < n; j++) {
            if(arr[j] < arr[min])
                min = j;
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}


void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return i+1;
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}


void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = L[i];
        i++; k++;
    }

    while(j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}


void shellSort(int arr[], int n) {
    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for(j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}



void generateRandom(int arr[], int n) {
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

void generateSorted(int arr[], int n) {
    for(int i = 0; i < n; i++)
        arr[i] = i;
}

void generateReverse(int arr[], int n) {
    for(int i = 0; i < n; i++)
        arr[i] = n - i;
}


void runAlgorithm(void (*sortFunc)(int[], int), int arr[], int n, const char* name) {
    clock_t start, end;
    double time_spent;

    start = clock();
    sortFunc(arr, n);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s -> Tempo: %f segundos\n", name, time_spent);
}


void menu() {
    printf("\n===== MENU =====\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
    printf("6 - Shell Sort\n");
    printf("7 - Executar todos\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}


int main() {
    srand(time(NULL));

    int n;
    printf("Digite o tamanho do array: ");
    scanf("%d", &n);

    if(n <= 0 || n > MAX) {
        printf("Tamanho invalido.\n");
        return 0;
    }

    int original[MAX], arr[MAX];
    int option;

    generateRandom(original, n);

    do {
        menu();
        scanf("%d", &option);

        switch(option) {
            case 1:
                copyArray(original, arr, n);
                runAlgorithm(bubbleSort, arr, n, "Bubble Sort");
                break;

            case 2:
                copyArray(original, arr, n);
                runAlgorithm(selectionSort, arr, n, "Selection Sort");
                break;

            case 3:
                copyArray(original, arr, n);
                runAlgorithm(insertionSort, arr, n, "Insertion Sort");
                break;

            case 4:
                copyArray(original, arr, n);
                {
                    clock_t start = clock();
                    quickSort(arr, 0, n-1);
                    clock_t end = clock();
                    printf("Quick Sort -> Tempo: %f segundos\n",
                        (double)(end - start) / CLOCKS_PER_SEC);
                }
                break;

            case 5:
                copyArray(original, arr, n);
                {
                    clock_t start = clock();
                    mergeSort(arr, 0, n-1);
                    clock_t end = clock();
                    printf("Merge Sort -> Tempo: %f segundos\n",
                        (double)(end - start) / CLOCKS_PER_SEC);
                }
                break;

            case 6:
                copyArray(original, arr, n);
                runAlgorithm(shellSort, arr, n, "Shell Sort");
                break;

            case 7:
                copyArray(original, arr, n);
                runAlgorithm(bubbleSort, arr, n, "Bubble Sort");

                copyArray(original, arr, n);
                runAlgorithm(selectionSort, arr, n, "Selection Sort");

                copyArray(original, arr, n);
                runAlgorithm(insertionSort, arr, n, "Insertion Sort");

                copyArray(original, arr, n);
                {
                    clock_t start = clock();
                    quickSort(arr, 0, n-1);
                    clock_t end = clock();
                    printf("Quick Sort -> Tempo: %f segundos\n",
                        (double)(end - start) / CLOCKS_PER_SEC);
                }

                copyArray(original, arr, n);
                {
                    clock_t start = clock();
                    mergeSort(arr, 0, n-1);
                    clock_t end = clock();
                    printf("Merge Sort -> Tempo: %f segundos\n",
                        (double)(end - start) / CLOCKS_PER_SEC);
                }

                copyArray(original, arr, n);
                runAlgorithm(shellSort, arr, n, "Shell Sort");
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(option != 0);

    return 0;
}