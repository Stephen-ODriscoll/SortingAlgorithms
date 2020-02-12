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

// The requirements I've set out for myself are that each algorithm takes in two constant template iterators;
// one to the start and one to the end of the contiguous list.
// Each algorithm must sort the list using these iterators.
// Algorithms should only require the < and = operators to sort.


const uint32_t m_size = 100000U;

int m_list[m_size];
int m_toSort[m_size];
int m_sorted[m_size];
const int m_min = 0;
const int m_max = 1000;


// Simple check to see if a list is sorted. Spoiler: it will be.
// I left this in for when I'm testing new variants.
bool isSorted()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        if (m_toSort[i] != m_sorted[i])
        {
            return false;
        }
    }

    return true;
}


// Generate sorted list of length m_size. List will look like: 0, 1, 2, 3, 4, ect. 
void generateSorted()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        m_list[i] = i;
        m_sorted[i] = i;
    }
}


// Generate unsorted list of length m_size using m_min and m_max
void generateUnsorted()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        m_list[i] = random::integer(m_min, m_max);
        m_sorted[i] = m_list[i];
    }

    std::sort(m_sorted, m_sorted + m_size);
}


// Copy original unsorted list into buffer for algorithm to sort
void resetToSort()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        m_toSort[i] = m_list[i];
    }
}


// Takes in function name and method signature and evaluates how long it takes to sort
template<typename Iterator>
void evaluateAlgorithm(const std::string name, void (*function)(Iterator, Iterator))
{
    resetToSort();

    std::cout << name.c_str() << ": ";
    auto start = std::chrono::system_clock::now();
    function(m_toSort, m_toSort + m_size);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();

    if (isSorted())
    {
        std::cout << milliseconds << "ms" << std::endl;
    }
    else
    {
        std::cout << "Failed to sort list" << std::endl;

         for(uint32_t i = 0; i < m_size; ++i)
         {
             std::cout << m_toSort[i] << " ";
         }

         std::cout << std::endl;
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

    // Standard C++ algorithms
    evaluateAlgorithm("Standard Sort", std::sort<int*>);
    evaluateAlgorithm("Standard Stable Sort", std::stable_sort<int*>);

    // Simple algorithms
    evaluateAlgorithm("Insertion Sort", insertionSort<int*>);
    evaluateAlgorithm("Bubble Sort", bubbleSort<int*>);
    evaluateAlgorithm("Selection Sort", selectionSort<int*>);
}
