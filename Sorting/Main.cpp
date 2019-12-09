#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

#include "MergeSort.h"
#include "BubbleSort.h"
#include "InsertionSort.h"


// Created by Stephen O Driscoll.
// This program demonstrates various sorting algorithms and my implementation of them.

// The requirements I've set out for myself is that each function takes in two generic constant iterators.
// Each algorithm must sort the lists using these iterators (pointers), one to the start and the other the end
// of the contiguous list.

// Allocation for copying is slowing the divide and conquer algorithms down but I can't see a solution
// without hard-coding lengths for the compiler (which I don't want to do). Thus, these algorithms may perform
// worse than normal. If you have a problem with this... fight me.




// Simple check to see if a list is sorted. Spoiler: it will be.
// I left this in for when I'm testing new variants.
template<typename Iterator>
bool isSorted(const Iterator begin, const Iterator end)
{
    for (Iterator it = begin; it < end - 1; ++it)
    {
        if (it > it + 1)
        {
            return false;
        }
    }

    return true;
}


template<typename Iterator>
void evaluateAlgorithm(const std::string name, void (*function)(Iterator, Iterator))
{
    int toSort[] = { 5, 4, 3, 2, 1 };
    int size = sizeof(toSort) / sizeof(int);

    auto start = std::chrono::system_clock::now();
    function(toSort, toSort + size);
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - start).count();

    if (isSorted(toSort, toSort + size))
    {
        std::wcout << name.c_str() << ": " << nanoseconds << "ns" << std::endl;
    }
    else
    {
        std::wcout << name.c_str() << ": Failed to sort list" << std::endl;
    }
}


int main(int argc, char* argv[])
{
    evaluateAlgorithm("Merge Sort", mergeSort<int*>);
    evaluateAlgorithm("Bubble Sort", bubbleSort<int*>);
    evaluateAlgorithm("Insertion Sort", insertionSort<int*>);
    evaluateAlgorithm("Standard Sort", std::sort<int*>);
}
