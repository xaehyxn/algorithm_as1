#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
#include <algorithm>
#include "SortCode.h" // BubbleSort 함수 포함

using namespace std;
using namespace chrono;

// --- 입력 생성기 생략 가능 시 별도 헤더로 분리해도 OK (여기선 포함)
void generateSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = i;
}

void generateReverseSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = size - i;
}

void generateRandom(int* arr, int size) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 1'000'000'000);
    for (int i = 0; i < size; ++i)
        arr[i] = dist(rng);
}

void generatePartiallySorted(int* arr, int size) {
    int sorted_part = size * 3 / 10;
    for (int i = 0; i < sorted_part; ++i)
        arr[i] = i;
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 1'000'000'000);
    for (int i = sorted_part; i < size; ++i)
        arr[i] = dist(rng);
}

double testSort(void (*inputGen)(int*, int), void (*sortFunc)(int*, int), int size, int repeat) {
    double total_time = 0.0;
    for (int i = 0; i < repeat; ++i) {
        int* temp = new int[size];
        inputGen(temp, size);

        auto start = high_resolution_clock::now();
        sortFunc(temp, size);
        auto end = high_resolution_clock::now();

        total_time += duration<double, milli>(end - start).count();
        delete[] temp;
    }
    return total_time / repeat;
}

int main() {
    const int sizes[] = {1000, 10000, 100000, 1000000};
    const char* types[] = {"Sorted", "Reverse", "Random", "Partially Sorted"};
    void (*generators[])(int*, int) = {
        generateSorted, generateReverseSorted, generateRandom, generatePartiallySorted
    };

    for (int s = 0; s < sizeof(sizes) / sizeof(int); ++s) {
        int size = sizes[s];
        int repeat = (size == 1000000) ? 1 : 10;

        cout << "\n===== BubbleSort | Input Size: " << size << " =====" << endl;

        for (int t = 0; t < 4; ++t) {
            double avg_time = testSort(generators[t], InsertionSort, size, repeat);
            cout << " - " << types[t] << ": " << avg_time << " ms (avg of " << repeat << " runs)" << endl;
        }
        cout << endl;
    }

    return 0;
}
