#pragma once

#include <math.h>

#include "InsertionSort.h"
#include "HeapSort.h"
#include "QuickSort.h"

// Hybrid algorithm of Intersection Sort, Heap Sort and Quick Sort
template<typename Iterator>
void introSort(const Iterator begin, const Iterator end, int64_t depthLimit)
{
    if ((end - begin) < 32)
    {
        insertionSort(begin, end);
    }
    else if (depthLimit == 0)
    {
        heapSort(begin, end);
    }
    else
    {
        Iterator split = partition(begin, end);

        introSort(begin, split, (depthLimit - 1));
        introSort((split + 1), end, (depthLimit - 1));
    }
}


template<typename Iterator>
void introSort(const Iterator begin, const Iterator end)
{
    int64_t depthLimit = 2 * (int64_t) std::floor(log(end - begin));

    introSort(begin, end, depthLimit);
}
