#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

// Генерация чисел Леонардо, не превышающих количество элементов массива
vector<int> leonardo_numbers(int hi) {
    int a = 1, b = 1;
    vector<int> numbers;
    while (a <= hi) {
        numbers.push_back(a);
        int temp = a;
        a = b;
        b = temp + b + 1;
    }
    return numbers;
}

// Восстановление кучи после слияния куч или удаления корня
void restore_heap(vector<int>& lst, int i, vector<int>& heap, const vector<int>& leo_nums) {
    int current = heap.size() - 1;
    int k = heap[current];

    while (current > 0) {
        int j = i - leo_nums[k];
        if (lst[j] > lst[i] && (k < 2 || (lst[j] > lst[i - 1] && lst[j] > lst[i - 2]))) {
            swap(lst[i], lst[j]);
            i = j;
            current--;
            k = heap[current];
        }
        else {
            break;
        }
    }

    while (k >= 2) {
        int t_r = i - 1, k_r = k - 2;
        int t_l = t_r - leo_nums[k_r], k_l = k - 1;
        if (lst[i] < lst[t_r] || lst[i] < lst[t_l]) {
            if (lst[t_r] > lst[t_l]) {
                swap(lst[i], lst[t_r]);
                i = t_r;
                k = k_r;
            }
            else {
                swap(lst[i], lst[t_l]);
                i = t_l;
                k = k_l;
            }
        }
        else {
            break;
        }
    }
}

// Основная процедура сортировки
void smoothsort(vector<int>& lst) {
    int n = lst.size();
    vector<int> leo_nums = leonardo_numbers(n);

    vector<int> heap;

    for (int i = 0; i < n; ++i) {
        if (heap.size() >= 2 && heap[heap.size() - 2] == heap.back() + 1) {
            heap.pop_back();
            heap.back()++;
        }
        else {
            if (heap.size() >= 1 && heap.back() == 1) {
                heap.push_back(0);
            }
            else {
                heap.push_back(1);
            }
        }
        restore_heap(lst, i, heap, leo_nums);
    }

    for (int i = n - 1; i >= 0; --i) {
        if (heap.back() < 2) {
            heap.pop_back();
        }
        else {
            int k = heap.back();
            heap.pop_back();
            int t_r = i - 1, k_r = k - 2;
            int t_l = t_r - leo_nums[k_r], k_l = k - 1;
            heap.push_back(k_l);
            restore_heap(lst, t_l, heap, leo_nums);
            heap.push_back(k_r);
            restore_heap(lst, t_r, heap, leo_nums);
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int n = 10;
    vector<int> lst(n);
    iota(lst.begin(), lst.end(), 0);
    random_device rd;
    mt19937 g(rd());
    shuffle(lst.begin(), lst.end(), g);
    cout << "Початковий масив: ";
    for (int num : lst) {
        cout << num << " ";
    }
    cout << endl;

    smoothsort(lst);
    cout << "Змiненний масив: ";
    for (int num : lst) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
