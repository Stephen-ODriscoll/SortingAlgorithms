#pragma once

// Example showing swapped elements:
//      temp | list(5, 4, 3, 2, 1)
//      --------------------------
//        4  |  5 -> 5, 3, 2, 1
//        -> |  4, 5, 3, 2, 1
//        3  |  4, 5 -> 5, 2, 1
//        3  |  4 -> 4, 5, 2, 1
//        -> |  3, 4, 5, 2, 1
//        2  |  3, 4, 5 -> 5, 1
//        2  |  3, 4 -> 4, 5, 1
//        2  |  3 -> 3, 4, 5, 1
//        -> |  2, 3, 4, 5, 1
//        1  |  2, 3, 4, 5 -> 5
//        1  |  2, 3, 4 -> 4, 5
//        1  |  2, 3 -> 3, 4, 5
//        1  |  2 -> 2, 3, 4, 5
//        -> |  1, 2, 3, 4, 5
template<typename Iterator>
void insertionSort(const Iterator begin, const Iterator end)
{
    // Everything left of next is already sorted
    for (Iterator next = begin + 1; next < end; ++next)
    {
        Iterator it = next;
        auto temp = *it;
        for (; begin < it && temp < *(it - 1); --it)
        {
            *it = *(it - 1);
        }

        *it = temp;
    }
}
