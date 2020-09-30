#pragma once

#define	TRUE 1
#define FALSE 0

void selection_sort(int *array, int len);

void insertion_sort(int *array, int len);

void bubble_sort(int *array, int len);

void merge_sort(int *array, int len);

void quick_sort(int *array, int start_index, int end_index);

void heap_sort(int *array, int len);

void bucket_sort(int *array, int len);