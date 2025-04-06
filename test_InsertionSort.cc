#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
#include <algorithm>  // sort ���
#include "SortCode.h"  // BubbleSort() �Լ� ���� ����

using namespace std;
using namespace chrono;

// ���� ���� ������
mt19937 rng(time(0));
uniform_int_distribution<int> dist(0, 1'000'000'000);

// ���ĵ� �迭 ����
void generateSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = i;
}

// �����ĵ� �迭 ����
void generateReverseSorted(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = size - i;
}

// ���� ������ �迭 ����
void generateRandom(int* arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = dist(rng);
}

// "�Ϻθ� ���ĵ� ������" ���� �� ���� ���ǿ� ��Ȯ�� �°� ����
void generatePartiallySorted(int* arr, int size) {
    // ��ü�� �������� ä���
    for (int i = 0; i < size; ++i)
        arr[i] = dist(rng);

    // 10% ������ ��� ����
    int sorted_portion_size = size / 10;
    int start_index = rng() % (size - sorted_portion_size);
    sort(arr + start_index, arr + start_index + sorted_portion_size);
}

// ��� ���� �ð� ����
double testSort(void (*inputGen)(int*, int), void (*sortFunc)(int*, int), int size, int repeat) {
    int* base = new int[size];
    int* temp = new int[size];
    inputGen(base, size);  // �Է� 1ȸ ����

    double total_time = 0.0;
    for (int i = 0; i < repeat; ++i) {
        memcpy(temp, base, sizeof(int) * size);  // ���纻 ����
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
