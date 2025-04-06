#include "SortCode.h"

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
void MergeSort(int* array, int size) {

}
void HeapSort(int* array, int size) {

}
void QuickSort(int* array, int size) {

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
