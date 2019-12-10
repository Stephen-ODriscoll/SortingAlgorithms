#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

#include "Random.h"
#include "MergeSort.h"
#include "BubbleSort.h"
#include "InsertionSort.h"


// Created by Stephen O Driscoll.
// This program demonstrates various sorting algorithms and my implementation of them.

// The requirements I've set out for myself are that each function takes in two generic constant iterators.
// Each algorithm must sort the lists using these iterators (pointers), one to the start and the other the end
// of the contiguous list.


const uint32_t m_size = 10000000U;

int m_unsorted[m_size];
int m_toSort[m_size];
const int m_min = 0;
const int m_max = 1000;


// Simple check to see if a list is sorted. Spoiler: it will be.
// I left this in for when I'm testing new variants.
bool isSorted()
{
    for (uint32_t i = 0; i < m_size - 1; ++i)
    {
        if (m_toSort[i] > m_toSort[i + 1])
        {
            return false;
        }
    }

    return true;
}


void generateUnsorted()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        m_unsorted[i] = random::integer(m_min, m_max);
    }
}


void copyUnsorted()
{
    for (uint32_t i = 0; i < m_size; ++i)
    {
        m_toSort[i] = m_unsorted[i];
    }
}


template<typename Iterator>
void evaluateAlgorithm(const std::string name, void (*function)(Iterator, Iterator))
{
    copyUnsorted();

    auto start = std::chrono::system_clock::now();
    function(m_toSort, m_toSort + m_size);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();

    if (isSorted())
    {
        std::wcout << name.c_str() << ": " << milliseconds << "ms" << std::endl;
    }
    else
    {
        std::wcout << name.c_str() << ": Failed to sort list" << std::endl;
    }
}


int main(int argc, char* argv[])
{
    random::initialize();
    generateUnsorted();

    evaluateAlgorithm("Merge Sort", mergeSort<int*>);
    evaluateAlgorithm("Bubble Sort", bubbleSort<int*>);
    evaluateAlgorithm("Insertion Sort", insertionSort<int*>);
    evaluateAlgorithm("Standard Sort", std::sort<int*>);
}
