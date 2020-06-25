#pragma once

#include "InsertionSort.h"
#include "MergeSort.h"

// Hybrid algorithm of Intersection Sort and Merge Sort
template<typename Iterator>
void timSort(const Iterator begin, const Iterator end)
{
    for (Iterator it = begin; it < end; it += 32)
    {
        insertionSort(it, std::min((it + 32), end));
    }

    const Iterator beginCopy = new typename std::iterator_traits<Iterator>::value_type[end - begin];
    for (uint64_t changeBy = 32; changeBy < (uint64_t) (end - begin); changeBy *= 2)
    {
        for (Iterator it = begin; it < end; it += (2 * changeBy))
        {
            merge(it, (it + changeBy), std::min(it + (2 * changeBy), end), beginCopy);
        }
    }

    delete[] beginCopy;
}