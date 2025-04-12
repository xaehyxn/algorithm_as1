#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
#include "SortCode.h"  // CocktailshakerSort 함수 선언

using namespace std;
using namespace chrono;

// --- 입력 생성기들 ---
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

// --- CocktailshakerSort 테스트 함수 ---
double testCocktailshakerSort(void (*inputGen)(int*, int), int size, int repeat) {
    double total_time = 0.0;

    for (int i = 0; i < repeat; ++i) {
        int* temp = new int[size];
        inputGen(temp, size);

        auto start = high_resolution_clock::now();
        CocktailshakerSort(temp, 0, size - 1);  // ? 인덱스 기반 호출
        auto end = high_resolution_clock::now();

        total_time += duration<double, milli>(end - start).count();
        for (i = 0; i < size-1; i++) {
            if (temp[i] > temp[i+1]) {
                cout << "array is not sorted" <<endl;
            }
        }
        delete[] temp;
    }

    return total_time / repeat;
}

// --- 메인 ---
int main() {
    const int sizes[] = {1000, 10000, 100000, 1000000};

    const char* types[] = {"Sorted", "Reverse", "Random", "Partially Sorted"};
    void (*generators[])(int*, int) = {
        generateSorted,
        generateReverseSorted,
        generateRandom,
        generatePartiallySorted
    };

    for (int s = 0; s < sizeof(sizes) / sizeof(int); ++s) {
        int size = sizes[s];
        int repeat = (size == 1000000) ? 1 : 10;  // ? 크기에 따라 실행 횟수 조절

        cout << "\n===== CocktailshakerSort | Input Size: " << size << ", Repeats: " << repeat << " =====\n";

        for (int t = 0; t < 4; ++t) {
            double avg_time = testCocktailshakerSort(generators[t], size, repeat);
            cout << " - " << types[t] << ": " << avg_time << " ms (avg of " << repeat << " runs)\n";
        }

        cout << endl;
    }

    return 0;
}
