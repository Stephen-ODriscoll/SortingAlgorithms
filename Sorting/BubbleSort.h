#pragma once

// Example showing swapped elements:
//      temp | list(5, 4, 3, 2, 1)
//      --------------------------
//        5  |  4 <-> 5, 3, 2, 1
//        5  |  4, 3 <-> 5, 2, 1
//        5  |  4, 3, 2 <-> 5, 1
//        5  |  4, 3, 2, 1 <-> 5
//        4  |  3 <-> 4, 2, 1, 5
//        4  |  3, 2 <-> 4, 1, 5
//        4  |  3, 2, 1 <-> 4, 5
//        3  |  2 <-> 3, 1, 4, 5
//        3  |  2, 1 <-> 3, 4, 5
//        2  |  1 <-> 2, 3, 4, 5
//        -  |  1, 2, 3, 4, 5
template<typename Iterator>
void bubbleSort(const Iterator begin, const Iterator end)
{
    // Everything right of done is sorted and won't be moved again
    Iterator done = end;
    for (bool swapOcccured = true; swapOcccured; --done)
    {
        swapOcccured = false;

        for (Iterator it = (begin + 1); it < done; ++it)
        {
            if (*it < *(it - 1))
            {
                swapOcccured = true;
                auto temp = *(it - 1);
                *(it - 1) = *it;
                *it = temp;
            }
        }
    }
}
