#include <iostream>
#include <chrono>
#include <random>
#include "SortCode.h"  // BubbleSort 함수 정의 포함

using namespace std;
using namespace chrono;

// 입력 생성기
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

// 테스트 함수
double testCocktailshakerSort(void (*inputGen)(int*, int), int size, int repeat) {
    double total_time = 0.0;
    for (int i = 0; i < repeat; ++i) {
        int* temp = new int[size];
        inputGen(temp, size);

        auto start = high_resolution_clock::now();
        CocktailshakerSort(temp, 0, size -1);
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

int main() {
    const int sizes[] = {1000, 10000, 100000, 1000000};
    const char* types[] = {"Sorted", "Reverse", "Random", "Partially Sorted"};
    void (*generators[])(int*, int) = {
        generateSorted, generateReverseSorted, generateRandom, generatePartiallySorted
    };

    for (int s = 0; s < 4; ++s) {
        int size = sizes[s];

        // repeat 설정: 크기별로 다르게
        int repeat = 10;
        if (size == 100000) repeat = 5;
        else if (size == 1000000) repeat = 1;

        cout << "\n===== CocktailshakerSort | Input Size: " << size << " | Repeat: " << repeat << " =====\n";

        for (int t = 0; t < 4; ++t) {
            double avg = testCocktailshakerSort(generators[t], size, repeat);
            cout << " - " << types[t] << ": " << avg << " ms (avg of " << repeat << " runs)\n";
        }
    }

    return 0;
}