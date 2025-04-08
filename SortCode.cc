#include "SortCode.h"
#include <climits>

void BubbleSort(int* array, int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void InsertionSort(int* array, int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        while(j >= 0 && array[j] > key) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

void SelectionSort(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        int temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

void MergeSort(int* array, int p, int r) {
    if (p < r) {
        int q = (p + r)/2;
        MergeSort(array, p, q);
        MergeSort(array, q+1, r);
        int n1 = q - p + 1;
        int n2 = r - q;
        int* L = new int[n1 + 1];
        int* R = new int[n2 + 1];
        for (int i = 0; i < n1; i++) {
            L[i] = array[p+i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = array[q + 1 + j];
        }
        L[n1] = INT_MAX;
        R[n2] = INT_MAX;
        int i = 0, j = 0;
        for (int k = p; k <= r; k++) {
            if (L[i] <= R[j]) {
                array[k] = L[i];
                i++;
            } else {
                array[k] = R[j];
                j++;
            }
        }
        delete[] L;
        delete[] R;
    }
}

void MaxHeapify(int* array, int heapSize, int i) {
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int largest = i;

    if (L < heapSize && array[L] > array[largest]) {
        largest = L;
    }
    if (R < heapSize && array[R] > array[largest]) {
        largest = R;
    }

    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        MaxHeapify(array, heapSize, largest);
    }
}

void BuildMaxHeap(int* array, int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        MaxHeapify(array, size, i);
    }
}

void HeapSort(int* array, int size) {
    BuildMaxHeap(array, size);
    for (int i = size - 1; i > 0; --i) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        MaxHeapify(array, i, 0);
    }
}

void QuickSort(int* array, int p, int r) {
    if (p < r) {
        int i = p;
        int j = r + 1;
        int x = array[p];
        do {
            do i++; while (i <= r && array[i] < x);
            do j--; while (j >= p && array[j] > x);
            if (i < j) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        } while (i < j);
        int temp = array[p];
        array[p] = array[j];
        array[j] = temp;
        QuickSort(array, p, j-1);
        QuickSort(array, j+1, r);
    }
}

void CocktailshakerSort(int* array, int size) {

}
void CombSort(int* array, int size) {

}
void LibrarySort(int* array, int size) {

}
void TimSort(int* array, int size) {

}
void TournamentSort(int* array, int size) {

}
void IntroSort(int* array, int size) {

}
