#include "sorting/Sort.h"
#include <cstddef>
#include <algorithm>

template <typename T>
void bubbleSort(T* begin, T* end) {
    if (begin >= end) return;
    for (T* i = end - 1; i != begin; --i) {
        bool swapped = false;

        for (T* j = begin; j != i; ++j) {
            if (*j > *(j + 1)) {
                swapped = true;
                std::swap(*j, *(j + 1));
            }
        }

        if (!swapped)
            break;
    }
}

template <typename T>
void selectionSort(T* begin, T* end) {
    if (begin >= end) return;
    for (T* i = begin; i != end - 1; ++i) {
        T* mn = i;
        for (T* j = i + 1; j != end; ++j) {
            if (*j < *mn) {
                mn = j;
            }
        }

        std::swap(*i, *mn);
    }
}

template <typename T>
void insertionSort(T* begin, T* end, int move) {
    if (begin >= end) return;
    for (T* i = begin + 1; i < end; i += move) {
        T temp = *i;
        T* j = i;
        for (; j >= begin + move && temp < *(j - move); j -= move) {
            *j = *(j - move);
        }

        *j = temp;
    }
}

template <typename T>
void shellSort(T* begin, T* end) {
    if (begin >= end) return;

    for (int i = ((end - begin) >> 1); i > 0; i >>= 1) {
        insertionSort(begin, end, i);
    }
}

template <typename T>
void merge(T* begin, T* mid, T* end) {
    int size1 = mid - begin;
    int size2 = end - mid;
    T* temp1 = new T[size1];
    T* temp2 = new T[size2];

    for (int i = 0; i < size1; ++i)
        temp1[i] = begin[i];

    for (int i = 0; i < size2; ++i)
        temp2[i] = mid[i];

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (temp1[i] > temp2[j])
            begin[k++] = temp2[j++];
        else
            begin[k++] = temp1[i++];
    }

    while (i < size1)
        begin[k++] = temp1[i++];

    while (j < size2)
        begin[k++] = temp2[j++];

    delete[] temp1;
    delete[] temp2;
}

template <typename T>
void mergeSort(T* begin, T* end) {
    if (end - begin <= 1)
        return;

    T* mid = begin + (end - begin) / 2;
    mergeSort(begin, mid);
    mergeSort(mid, end);
    merge(begin, mid, end);
}

template <typename T>
T* partition(T* begin, T* end) {
    T pivot = *(end - 1);
    T* i = begin;

    for (T* j = begin; j != end - 1; ++j) {
        if (*j < pivot) {
            std::swap(*i, *j);
            ++i;
        }
    }

    std::swap(*i, *(end - 1));
    return i;
}

template <typename T>
void quickSort(T* begin, T* end) {
    if (end - begin <= 1)
        return;

    T* p = partition(begin, end);
    quickSort(begin, p);
    quickSort(p + 1, end);
}

template <typename T>
void countSort(T* begin, T* end) {
    if (begin >= end)
        return;

    T min = *begin, max = *begin;
    for (T* p = begin + 1; p != end; ++p) {
        if (*p < min) min = *p;
        if (*p > max) max = *p;
    }

    int range = max - min + 1;
    int n = end - begin;
    int* count = new int[range]();
    T* output = new T[n];

    for (T* p = begin; p != end; ++p)
        count[*p - min]++;

    for (int i = 1; i < range; ++i)
        count[i] += count[i - 1];

    for (T* p = end - 1; p >= begin; --p) {
        int idx = *p - min;
        output[count[idx] - 1] = *p;
        count[idx]--;
    }

    for (int i = 0; i < n; ++i)
        begin[i] = output[i];

    delete[] count;
    delete[] output;
}

template <typename T>
void radixSort(T* begin, T* end) {
    if (begin >= end)
        return;

    T min = *begin, max = *begin;
    for (T* p = begin + 1; p != end; ++p) {
        if (*p < min) min = *p;
        if (*p > max) max = *p;
    }

    // Shift all values to be non-negative so digit extraction works
    for (T* p = begin; p != end; ++p)
        *p -= min;
    max -= min;

    int n = end - begin;
    for (int exp = 1; max / exp > 0; exp *= 10) {
        int count[10] = {};
        T* output = new T[n];

        for (T* p = begin; p != end; ++p)
            count[(*p / exp) % 10]++;

        for (int i = 1; i < 10; ++i)
            count[i] += count[i - 1];

        for (T* p = end - 1; p >= begin; --p) {
            int digit = (*p / exp) % 10;
            output[count[digit] - 1] = *p;
            count[digit]--;
        }

        for (int i = 0; i < n; ++i)
            begin[i] = output[i];

        delete[] output;
    }

    // Shift back to original range
    for (T* p = begin; p != end; ++p)
        *p += min;
}

template <typename T>
void heapSort(T* begin, T* end) {
    int n = end - begin;
    if (n <= 1) return;

    auto shiftDown = [begin](int i, int size) {
        while (true) {
            int largest = i;
            int l = 2 * i + 1;
            int r = 2 * i + 2;

            if (l < size && begin[largest] < begin[l])
                largest = l;

            if (r < size && begin[largest] < begin[r])
                largest = r;

            if (largest == i) break;

            std::swap(begin[i], begin[largest]);
            i = largest;
        }
    };

    // Build max-heap
    for (int i = n / 2 - 1; i >= 0; --i)
        shiftDown(i, n);

    // Extract sorted order
    for (int i = n - 1; i > 0; --i) {
        std::swap(begin[0], begin[i]);
        shiftDown(0, i);
    }
}
