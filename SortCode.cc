#include "SortCode.h"
#include <climits> // 센티널 값때문에 사용
#include <iostream>
using namespace std;

void BubbleSort(int* array, int size) {
    for (int i = 0; i < size-1; i++) {
        bool swapped = false;
        for (int j = 0; j < size-i-1; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                swapped = true;
            }
        }
        if (swapped == false) {
            break;
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

void MergeProcedure(int* array, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int* L = new int[n1 + 1];
    int* R = new int[n2 + 1];

    for (int i = 0; i < n1; i++) {
        L[i] = array[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[q + 1 + j];
    }

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            array[k] = L[i++];
        } else {
            array[k] = R[j++];
        }
    }

    delete[] L;
    delete[] R;
}

void MergeSort(int* array, int p, int r) {
    if (p < r) {
        int q = (p + r)/2;
        MergeSort(array, p, q);
        MergeSort(array, q+1, r);
        MergeProcedure(array, p, q, r);
    }
}

void MaxHeapify(int* array, int heapSize, int i) {
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int largest = i;

    if (L < heapSize && array[L] > array[largest]) {
        largest = L;
    }
    if (R < heapSize && array[R] > array[largest]) {
        largest = R;
    }

    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        MaxHeapify(array, heapSize, largest);
    }
}

void BuildMaxHeap(int* array, int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        MaxHeapify(array, size, i);
    }
}

void HeapSort(int* array, int size) {
    BuildMaxHeap(array, size);
    for (int i = size - 1; i > 0; --i) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        MaxHeapify(array, i, 0);
    }
}

int Partition(int* array, int p, int r) {
    int i = p;
    int j = r + 1;
    int x = array[p];

    do {
        do i++; while (i <= r && array[i] < x);
        do j--; while (j >= p && array[j] > x);
        if (i < j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    } while (i < j);

    int temp = array[p];
    array[p] = array[j];
    array[j] = temp;

    return j;
}

void QuickSort(int* array, int p, int r) {
    if (p < r) {
        int q = Partition(array, p, r);
        QuickSort(array, p, q - 1);
        QuickSort(array, q + 1, r);
    }
}

void CocktailshakerSort(int* array, int p, int r) {
    bool swapped = true;
    while (swapped == true) {
        swapped = false;
        for (int i = p; i < r - 1; i++) {
            if (array[i] > array[i+1]) {
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                swapped = true;
            }
        }
        r--;
        for (int i = r; i > p; i--) {
            if (array[i] < array[i-1]) {
                int temp = array[i];
                array[i] = array[i-1];
                array[i-1] = temp;
                swapped = true;
            }
        }
        p++;
    }
}

void CombSort(int* array, int size) {
    int gap = size - 1;
    bool swapped = true;
    while (!(gap == 1 && swapped == false)) {
        swapped = false;
        for (int i = 0; i + gap < size; i++) {
            if (array[i] > array[i + gap]) {
                int temp = array[i];
                array[i] = array[i+gap];
                array[i+gap] = temp;
                swapped = true;
            }
        }
        gap = gap/1.3;
        if (gap < 1) {
            gap = 1;
        }
    }
}

void Rebalancing(int* S, int S_size, int* support_array, int &support_num, int &S_prefix, int &cur_round) {
    // 현재 prefix 내에서 support 요소들의 인덱스를 재수집
    support_num = 0;
    for (int i = 0; i < S_prefix; i++) {
        if (S[i] != -1) {
            support_array[support_num++] = i;
        }
    }
    cur_round++;
    int new_prefix = (1 << (cur_round + 1));
    if (new_prefix > S_size)
        new_prefix = S_size;
    
    // 현재 support 요소들의 값을 임시 저장
    int* temp = new int[support_num];
    int k = 0;
    for (int i = 0; i < S_prefix; i++) {
        if (S[i] != -1)
            temp[k++] = S[i];
    }
    
    // 새 prefix 구간 [0, new_prefix)를 모두 빈 공간(-1)으로 초기화
    for (int i = 0; i < new_prefix; i++) {
        S[i] = -1;
    }
    
    // support 요소들을 균등하게 새 위치에 배치함.
    // 각 요소의 새 위치: new_index = ((i+1)*new_prefix) / (support_num+1)
    int size_gap = new_prefix/(support_num+1);
    for (int i = 0; i < support_num; i++) {
        int new_index = (i+1)*size_gap;
        S[new_index] = temp[i];
        support_array[i] = new_index;
    }
    
    S_prefix = new_prefix;
    delete[] temp;
}

int BinarySearch(int x, int* support_array, int support_num, int* S) {
    int left = 0;
    int right = support_num - 1;
    while(left <= right) {
        int mid = (left + right) / 2;
        int mid_num = S[support_array[mid]];
        if (x > mid_num) {
            left = mid + 1;
        }
        else if (x < mid_num) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }   
    return left;
}

int FindGap(int x_insert_S_pos, int* S, int S_prefix) {
    int right_gap = -1;
    int left_gap = -1;
    for (int i = x_insert_S_pos; i < S_prefix; i++) {
        if (S[i] == -1) {
            right_gap = i;
            break;
        }
    }
    for (int i = x_insert_S_pos; i >= 0; i--) {
        if (S[i] == -1) {
            left_gap = i;
            break;
        }
    }

    if (right_gap - x_insert_S_pos > x_insert_S_pos - left_gap && left_gap != -1 && right_gap != -1) {
        return left_gap;
    }
    else if (right_gap - x_insert_S_pos <= x_insert_S_pos - left_gap && right_gap != -1 && left_gap != -1) {
        return right_gap;
    }
    else if (right_gap == -1 && left_gap != -1) {
        return left_gap;
    }
    else if (left_gap == -1 && right_gap != -1) {
        return right_gap;
    }
    else {
        cout << "Find Near Gap error" << endl;
        return -1;
    }
}

void LibrarySort(int* array, int size, double epsilon) {
    int S_size = size * (1 + epsilon);
    int* S = new int[S_size];
    for (int i = 0; i < S_size; i++) {
        S[i] = -1;
    }
    // round 초기화
    int cur_round = 0;
    int intercalated_num = 0;
    // round별 요소 개수 추적
    int support_num = 0;
    // 초기 round: S_prefix = 2^(round+1)
    int S_prefix = 2; 

    // 첫 원소 삽입
    int x = array[0];
    S[0] = x;
    int* support_array = new int[size];
    support_num = 1;
    support_array[0] = 0;
    
    Rebalancing(S, S_size, support_array, support_num, S_prefix, cur_round);
    intercalated_num = 0;

    // 나머지 원소 삽입
    for (int i = 1; i < size; i++) {
        int x = array[i];
        bool inserted = false;
        // 재시도 루프: rebalancing으로 영역을 확장한 후 재탐색
        int x_insert_sup_pos = BinarySearch(x, support_array, support_num, S);
        int x_insert_S_pos = -1;
        if (x_insert_sup_pos == 0) { // 맨 왼쪽 (x가 0번 보다 작은 경우)
            int find_k = 0;
            if (support_array[x_insert_sup_pos] == 0) {
                x_insert_S_pos = 0;
            }
            else {
                for (int k = 0; k < S_prefix; k++) {
                    if (S[k] >= x) {
                        x_insert_S_pos = k;
                        find_k = 1;
                        break;
                    }
                }
                if (find_k == 0) {
                    x_insert_S_pos = 0;
                }
            }
        }
        else if (x_insert_sup_pos == support_num) { // 맨 오른쪽 (x가 support_num - 1 인덱스 보다 큰 경우)
            int find_k = 0;
            if (support_array[x_insert_sup_pos - 1] == S_prefix - 1) {
                S[support_array[x_insert_sup_pos - 1] - 1] = S[support_array[x_insert_sup_pos - 1]];
                S[support_array[x_insert_sup_pos - 1]] = -1;
                x_insert_S_pos = support_array[x_insert_sup_pos - 1];
            }
            for (int k = support_array[x_insert_sup_pos - 1]; k < S_prefix; k++) {
                if (S[k] >= x) {
                    x_insert_S_pos = k;
                    find_k = 1;
                    break;
                }
            }
            if (find_k == 0) {
                x_insert_S_pos = S_prefix-1;
                S[S_prefix - 2] = S[S_prefix - 1];
                S[S_prefix - 1] = -1;
            }
        }
        else if (S[support_array[x_insert_sup_pos]] == x) { // mid를 반환한 경우
            x_insert_S_pos = support_array[x_insert_sup_pos];
        }
        else if (S[support_array[x_insert_sup_pos]] > x) { // right를 왼쪽으로 땡기고 끝난 경우 -> x가 더 작음
            int last_k = -1;
            for (int k = support_array[x_insert_sup_pos]; k >= 0; k--) {
                if (S[k] >= x) {
                    last_k = k;
                }
                if (S[k] < x && S[k] != -1) {
                    x_insert_S_pos = last_k;
                    break;
                }
            }
        }
        else  if (S[support_array[x_insert_sup_pos]] < x) { // left를 오른쪽으로 땡기고 끝난 경우우
            for (int k = support_array[x_insert_sup_pos]; k < S_prefix; k++) {
                if (S[k] >= x) {
                    x_insert_S_pos = k;
                    break;
                }
            }
        }
        else if (S[support_array[x_insert_sup_pos]] == -1 || x_insert_S_pos == -1) {
            for (int k = 0; k < S_prefix; k++) {
                if (S[k] >= x) {
                    x_insert_S_pos = k;
                    break;
                }
            }
        }
        
        if (x_insert_S_pos == -1) {
            cout << " cannot find x_insert_S_pos " << endl;
            Rebalancing(S, S_size, support_array, support_num, S_prefix, cur_round);
            intercalated_num = 0;
            continue;
        }
        // 삽입 위치를 찾았으므로, 값이 이미 존재하는 경우 빈 공간으로 밀어내기
        if (S[x_insert_S_pos] != -1) {
            int near_gap = -1;
            near_gap = FindGap(x_insert_S_pos, S, S_prefix);
            if (near_gap == -1) {
                cout << "cannot find near gap" << endl;
            }
            if (near_gap == x_insert_S_pos - 1) {
                S[x_insert_S_pos - 1] = x;
            }
            else if (near_gap > x_insert_S_pos) {
                for (int k = near_gap; k > x_insert_S_pos; k--) {
                    S[k] = S[k - 1];
                }
                S[x_insert_S_pos] = x;
            }
            else if (near_gap < x_insert_S_pos) {
                for (int k = near_gap; k < x_insert_S_pos - 1; k++) {
                    S[k] = S[k + 1];
                }
                S[x_insert_S_pos - 1] = x;
            }
        }
        else {
            S[x_insert_S_pos] = x;
        }

        intercalated_num++;

        // 디버깅: 현재 S 배열 전체 상태 출력
        // for (int k = 0; k < S_prefix; k++) {
        //     cout << S[k] << " ";
        // }
        // cout << endl;
        // 만약 이번 round에 정해진 수 만큼 원소를 삽입했으면 rebalancing 수행
        if (intercalated_num == (1 << (cur_round - 1))) {
            Rebalancing(S, S_size, support_array, support_num, S_prefix, cur_round);
            intercalated_num = 0;
        }
    }
    // cout << endl;
    // 최종 rebalancing
    Rebalancing(S, S_size, support_array, support_num, S_prefix, cur_round);

    int array_index = 0;
    // cout << endl;
    for (int j = 0; j < S_size && array_index < size; j++) {
        if (S[j] != -1) {
            array[array_index++] = S[j];
        }
    }

    delete[] support_array;
    delete[] S;
}

void BinaryInsertionSort(int* array, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = array[i];
        int low = left;
        int high = i - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (array[mid] > key)
                high = mid - 1;
            else
                low = mid + 1;
        }

        for (int j = i - 1; j >= low; j--)
            array[j + 1] = array[j];

        array[low] = key;
    }
}

int RUN = 32;

void TimSort(int* array, int size) {
    for (int i = 0; i < size; i += RUN) {
        int right;
        if (i + RUN - 1 < size)
            right = i + RUN - 1;
        else
            right = size - 1;

        BinaryInsertionSort(array, i, right);
    }

    for (int curr_size = RUN; curr_size < size; curr_size *= 2) {
        for (int left = 0; left < size; left += 2 * curr_size) {
            int mid = left + curr_size - 1;
            int right;
            if (left + 2 * curr_size - 1 < size)
                right = left + 2 * curr_size - 1;
            else
                right = size - 1;

            if (mid < right)
                MergeProcedure(array, left, mid, right);
        }
    }
}

int Log2(int n) {
    int result = 0;
    while (n > 1) {
        n >>= 1;
        result++;
    }
    return result;
}

void IntroSort(int* array, int size) {

}

void TournamentSort(int* array, int size) {

}
