#include <iostream>
#include <string>
#include "SortCode.h"

using namespace std;

// ======= 구조체 =======
struct Element {
    int value;
    int original;
};

// ======= 안정성 판단 =======
bool isStable(Element* array, int size) {
    for (int i = 1; i < size; ++i) {
        if (array[i - 1].value == array[i].value &&
            array[i - 1].original > array[i].original) {
            return false;
        }
    }
    return true;
}

// ======= 래퍼 함수들 =======
void BubbleStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    BubbleSort(temp, size);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void InsertionStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    InsertionSort(temp, size);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void SelectionStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    SelectionSort(temp, size);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void HeapStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    HeapSort(temp, size);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void MergeStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    MergeSort(temp, 0, size - 1);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void QuickStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    QuickSort(temp, 0, size - 1);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void CocktailStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    CocktailshakerSort(temp, 0, size - 1);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void CombStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    CombSort(temp, size);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void IntroStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    IntroSort(temp, 0, size - 1);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void TimStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    TimSort(temp, size);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void LibraryStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    LibrarySort(temp, size, 1);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

void TournamentStableSort(Element* array, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) temp[i] = array[i].value;
    TournamentSort(temp, size);

    bool* used = new bool[size]();
    Element* sorted = new Element[size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!used[j] && array[j].value == temp[i]) {
                sorted[i] = array[j];
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) array[i] = sorted[i];
    delete[] temp; delete[] used; delete[] sorted;
}

// ======= 테스트 함수 =======
void testStability(void (*sort)(Element*, int), const string& name) {
    const int size = 1000;
    Element* arr = new Element[size];

    for (int i = 0; i < size; ++i) {
        arr[i].value = i / 10;
        arr[i].original = i;
    }

    sort(arr, size);

    cout << "[" << name << "] " << (isStable(arr, size) ? "Stable" : "NOT Stable") << endl;

    delete[] arr;
}

// ======= main() =======
int main() {
    testStability(BubbleStableSort, "BubbleSort");
    testStability(InsertionStableSort, "InsertionSort");
    testStability(SelectionStableSort, "SelectionSort");
    testStability(HeapStableSort, "HeapSort");
    testStability(MergeStableSort, "MergeSort");
    testStability(QuickStableSort, "QuickSort");
    testStability(CocktailStableSort, "CocktailShakerSort");
    testStability(CombStableSort, "CombSort");
    testStability(IntroStableSort, "IntroSort");
    testStability(TimStableSort, "TimSort");
    testStability(LibraryStableSort, "LibrarySort");
    testStability(TournamentStableSort, "TournamentSort");

    return 0;
}
