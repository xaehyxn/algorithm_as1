#include <iostream>
#include <chrono>
#include <random>
#include "SortCode.h"  // BubbleSort 함수 정의 포함

using namespace std;
using namespace chrono;

// ***** 실행 시간 측정 ***** //
void generateSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i) arr[i] = i;
}

void generateReverseSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i) arr[i] = size - i;
}

void generateRandom(int* arr, int size) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 1'000'000'000);
    for (int i = 0; i < size; ++i) arr[i] = dist(rng);
}

void generatePartiallySorted(int* arr, int size) {
    int sorted_part = size * 3 / 10;
    for (int i = 0; i < sorted_part; ++i) arr[i] = i;
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 1'000'000'000);
    for (int i = sorted_part; i < size; ++i) arr[i] = dist(rng);
}

double testBubbleSort(void (*inputGen)(int*, int), int size, int repeat) {
    double total_time = 0.0;
    for (int i = 0; i < repeat; ++i) {
        int* temp = new int[size];
        inputGen(temp, size);

        auto start = high_resolution_clock::now();
        BubbleSort(temp, size);
        auto end = high_resolution_clock::now();

        total_time += duration<double, milli>(end - start).count();

        for (int j = 0; j < size - 1; ++j) {
            if (temp[j] > temp[j + 1]) {
                cout << "array is not sorted\n";
                break;
            }
        }

        delete[] temp;
    }
    return total_time / repeat;
}

void testBubbleSortStability(void (*inputGen)(int*, int), int size, const string& input_type) {
    int* temp = new int[size];
    inputGen(temp, size);

    BubbleSort(temp, size);

    bool isSorted = true;
    for (int i = 0; i < size - 1; ++i) {
        if (temp[i] > temp[i + 1]) {
            isSorted = false;
            break;
        }
    }

    cout << "[" << input_type << "] ";
    if (isSorted) cout << "array is sorted\n";
    else cout << "array is NOT sorted\n";

    delete[] temp;
}

int main() {
    const int sizes[] = {1000, 10000, 100000, 1000000};
    const char* types[] = {"Sorted", "Reverse", "Random", "Partially Sorted"};
    void (*generators[])(int*, int) = {
        generateSorted, generateReverseSorted, generateRandom, generatePartiallySorted
    };

    for (int s = 0; s < 4; ++s) {
        int size = sizes[s];

        int repeat = 10;
        if (size == 100000) repeat = 5;
        else if (size == 1000000) repeat = 1;

        cout << "\n===== BubbleSort | Input Size: " << size << " | Repeat: " << repeat << " =====\n";

        for (int t = 0; t < 4; ++t) {
            double avg = testBubbleSort(generators[t], size, repeat);
            cout << " - " << types[t] << ": " << avg << " ms (avg of " << repeat << " runs)\n";
        }
    }

    return 0;
}