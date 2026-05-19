#pragma once

template <typename T>
void bubbleSort(T* begin, T* end);

template <typename T>
void selectionSort(T* begin, T* end);

template <typename T>
void insertionSort(T* begin, T* end);

template <typename T>
void mergeSort(T* begin, T* end);

template <typename T>
void quickSort(T* begin, T* end);

template <typename T>
void countSort(T* begin, T* end);

template <typename T>
void radixSort(T* begin, T* end);

template <typename T>
void heapSort(T* begin, T* end);

#include "sorting/Sort.tpp"