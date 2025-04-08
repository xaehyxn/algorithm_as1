#ifndef SORTCODE_H
#define SORTCODE_H

void BubbleSort(int* array, int size);
void InsertionSort(int* array, int size);
void SelectionSort(int* array, int size);
void MergeSort(int* array, int p, int r);
void MaxHeapify(int* array, int heapSize, int i);
void BuildMaxHeap(int* array, int size);
void HeapSort(int* array, int size);
void Partition(int* array, int size, int p);
void QuickSort(int* array, int size);

void CocktailshakerSort(int* array, int size);
void CombSort(int* array, int size);
void LibrarySort(int* array, int size);
void TimSort(int* array, int size);
void TournamentSort(int* array, int size);
void IntroSort(int* array, int size);

#endif // SORTCODE_H