#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
#include "SortCode.h"  // BubbleSort 함수 선언

using namespace std;
using namespace chrono;

// ? 정렬된 배열 생성
void generateSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = i;
}

// ? 역정렬된 배열 생성
void generateReverseSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = size - i;
}

// ? 진짜 무작위 배열 생성 (매번 다른 시드)
void generateRandom(int* arr, int size) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 1'000'000'000);
    for (int i = 0; i < size; ++i)
        arr[i] = dist(rng);
}

// ? 일반적인 "부분 정렬된 배열" 생성
void generatePartiallySorted(int* arr, int size) {
    int sorted_part = size * 3 / 10;  // 앞쪽 30% 정렬

    for (int i = 0; i < sorted_part; ++i)
        arr[i] = i;

    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 1'000'000'000);
    for (int i = sorted_part; i < size; ++i)
        arr[i] = dist(rng);
}

// ? 평균 실행 시간 측정 함수 (랜덤 배열 매번 새로 생성)
double testSort(
    void (*inputGen)(int*, int),
    void (*sortFunc)(int*, int),
    int size,
    int repeat
) {
    double total_time = 0.0;

    for (int i = 0; i < repeat; ++i) {
        int* temp = new int[size];
        inputGen(temp, size);  // 매번 새로운 입력 생성

        auto start = high_resolution_clock::now();
        sortFunc(temp, size);
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
        int repeat = (size == 1000000) ? 1 : 10;

        cout << "===== Input Size: " << size << ", Repeats: " << repeat << " =====" << endl;

        for (int t = 0; t < 4; ++t) {
            double avg_time = testSort(generators[t], BubbleSort, size, repeat);
            cout << " - " << types[t] << ": " << avg_time << " ms (avg of " << repeat << " runs)" << endl;
        }

        cout << endl;
    }

    return 0;
}
