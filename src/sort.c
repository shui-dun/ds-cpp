#include "sort.h"
#include <stdlib.h>
#include <string.h>

void selection_sort(int *array, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		int min_index = i;
		for (int x = i + 1; x < len; x++)
			if (array[min_index] > array[x])
				min_index = x;
		int temp = array[min_index];
		array[min_index] = array[i];
		array[i] = temp;
	}
}

void insertion_sort(int *array, int len)
{
	for (int x = 1; x < len; x++)
	{
		int temp = array[x], y;
		for (y = x - 1; y >= 0 && temp < array[y]; y--)
		{
			array[y + 1] = array[y];
		}
		array[y + 1] = temp;
	}
}

void bubble_sort(int * array, int len)
{
	int flag = FALSE;
	for (int i = 0; i < len - 1 && !flag; i++)
	{
		flag = TRUE;
		for (int x = 0; x < len - i - 1; x++)
		{
			if (array[x] > array[x + 1])
			{
				int temp = array[x];
				array[x] = array[x + 1];
				array[x + 1] = temp;
				flag = FALSE;
			}
		}
	}
}

void merge_sort(int * array, int len)
{
	if (len > 1)
	{
		int len1 = len / 2, len2 = len - len1;
		int *array1 = (int *)malloc(sizeof(int)*len1);
		int *array2 = (int *)malloc(sizeof(int)*len2);
		memcpy(array1, array, sizeof(int)*len1);
		memcpy(array2, array + len1, sizeof(int)*len2);
		merge_sort(array1, len1);
		merge_sort(array2, len2);
		int index = 0, index1 = 0, index2 = 0;
		while (index1 < len1 && index2 < len2)
		{
			if (array1[index1] > array2[index2])
				array[index++] = array2[index2++];
			else
				array[index++] = array1[index1++];
		}
		while (index1<len1)
			array[index++] = array1[index1++];
		while(index2<len2)
			array[index++] = array2[index2++];
		free(array1);
		free(array2);
	}
}

void quick_sort(int * array, int start_index, int end_index)
{
	if (end_index > start_index)
	{
		int len = end_index - start_index + 1, lpos = start_index, rpos = end_index;
		int *array1 = (int *)malloc(sizeof(int)*len);
		memcpy(array1, array + start_index, len * sizeof(int));
		for (int i = 1; i < len; i++)
		{
			if (array1[i] < array1[0])
				array[lpos++] = array1[i];
			else
				array[rpos--] = array1[i];
		}
		array[lpos] = array1[0];
		quick_sort(array, start_index, lpos-1);
		quick_sort(array, lpos + 1, end_index);
	}
}

void bucket_sort(int * array, int len)
{
	int array1[1000], n = sizeof(array1) / sizeof(int), pos = 0;
	memset(array1, 0, sizeof(array1));
	for (int i = 0; i < len; i++)
		array1[array[i]]++;
	for (int i = 0; i < n; i++)
		if (array1[i])
			for (int x = 0; x < array1[i]; x++)
				array[pos++] = i;
}
