#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

#include "Random.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "IntroSort.h"
#include "TimSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"


// Created by Stephen O Driscoll.
// This program demonstrates various sorting algorithms and my implementation of them.

// The requirements I've set out for myself are that each algorithm takes in two generic constant iterators.
// Each algorithm must sort the lists using these iterators (pointers), one to the start and one to the end
// of the contiguous list. All algorithms should only require the < and = operators.


const uint32_t m_size = 100000U;

int m_list[m_size];
int m_toSort[m_size];
const int m_min = 0;
const int m_max = 1000;


// Simple check to see if a list is sorted. Spoiler: it will be.
// I left this in for when I'm testing new variants.
bool isSorted()
{
    for (uint32_t i = 0; i < m_size - 1; ++i)
    {
        if (m_toSort[i + 1] < m_toSort[i])
        {
            return false;
        }
    }

    return true;
}


void generateSorted()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        m_list[i] = i;
    }
}


void generateUnsorted()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        m_list[i] = random::integer(m_min, m_max);
    }
}


void resetToSort()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        m_toSort[i] = m_list[i];
    }
}


template<typename Iterator>
void evaluateAlgorithm(const std::string name, void (*function)(Iterator, Iterator))
{
    resetToSort();

    std::wcout << name.c_str() << ": ";
    auto start = std::chrono::system_clock::now();
    function(m_toSort, m_toSort + m_size);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();

    if (isSorted())
    {
        std::wcout << milliseconds << "ms" << std::endl;
    }
    else
    {
        std::wcout << "Failed to sort list" << std::endl;
    }
}


int main(int argc, char* argv[])
{
    random::initialize();
    generateUnsorted();

    // Divide and Conquer algorithms
    evaluateAlgorithm("Quick Sort", quickSort<int*>);
    evaluateAlgorithm("Merge Sort", mergeSort<int*>);
    evaluateAlgorithm("Heap Sort", heapSort<int*>);

    // Hybrid algorithms
    evaluateAlgorithm("Intro Sort", introSort<int*>);
    evaluateAlgorithm("Tim Sort", timSort<int*>);

    // Standard algorithms
    evaluateAlgorithm("Standard Sort", std::sort<int*>);
    evaluateAlgorithm("Standard Stable Sort", std::stable_sort<int*>);

    // Simple algorithms
    evaluateAlgorithm("Insertion Sort", insertionSort<int*>);
    evaluateAlgorithm("Bubble Sort", bubbleSort<int*>);
    evaluateAlgorithm("Selection Sort", selectionSort<int*>);
}
