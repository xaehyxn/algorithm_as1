#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
#include <algorithm>  // sort 사용
#include "SortCode.h"  // BubbleSort() 함수 선언 포함

using namespace std;
using namespace chrono;

// 고성능 난수 생성기
mt19937 rng(time(0));
uniform_int_distribution<int> dist(0, 1'000'000'000);

// 정렬된 배열 생성
void generateSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = i;
}

// 역정렬된 배열 생성
void generateReverseSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = size - i;
}

// 완전 무작위 배열 생성
void generateRandom(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = dist(rng);
}

// "일부만 정렬된 시퀀스" 생성 → 과제 정의에 정확히 맞게 수정
void generatePartiallySorted(int* arr, int size) {
    // 전체를 무작위로 채우고
    for (int i = 0; i < size; ++i)
        arr[i] = dist(rng);

    // 10% 범위만 골라서 정렬
    int sorted_portion_size = size / 10;
    int start_index = rng() % (size - sorted_portion_size);
    sort(arr + start_index, arr + start_index + sorted_portion_size);
}

// 평균 실행 시간 측정
double testSort(void (*inputGen)(int*, int), void (*sortFunc)(int*, int), int size, int repeat) {
    int* base = new int[size];
    int* temp = new int[size];
    inputGen(base, size);  // 입력 1회 생성

    double total_time = 0.0;
    for (int i = 0; i < repeat; ++i) {
        memcpy(temp, base, sizeof(int) * size);  // 복사본 정렬
        auto start = high_resolution_clock::now();
        sortFunc(temp, size);
        auto end = high_resolution_clock::now();
        total_time += duration<double, milli>(end - start).count();
    }

    delete[] base;
    delete[] temp;
    return total_time / repeat;
}

int main() {
    const int repeats = 10;
    const int sizes[] = {1000, 10000, 100000, 1000000};

    const char* types[] = {"Sorted", "Reverse", "Random", "Partially Sorted"};
    void (*generators[])(int*, int) = {
        generateSorted, generateReverseSorted, generateRandom, generatePartiallySorted
    };

    for (int s = 0; s < sizeof(sizes) / sizeof(int); ++s) {
        int size = sizes[s];
        cout << "===== Input Size: " << size << " =====" << endl;

        for (int t = 0; t < 4; ++t) {
            double avg_time = testSort(generators[t], InsertionSort, size, repeats);
            cout << " - " << types[t] << ": " << avg_time << " ms (avg of " << repeats << " runs)" << endl;
        }

        cout << endl;
    }

    return 0;
}
