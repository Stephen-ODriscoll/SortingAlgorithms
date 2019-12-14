#pragma once

template<typename Iterator>
void siftDown(const Iterator begin, const Iterator end, int64_t index = 0)
{
    Iterator it = begin + index;
    Iterator itLeft = it + (index + 1);
    Iterator itRight = it + (index + 2);
    while (itLeft < end)
    {
        auto temp = *it;
        if (*itLeft < *itRight && itRight < end)
        {
            if (*itRight < *it)
            {
                break;
            }

            index = (index * 2) + 2;
            *it = *itRight;
            it = itRight;
        }
        else
        {
            if (*itLeft < *it)
            {
                break;
            }

            index = (index * 2) + 1;
            *it = *itLeft;
            it = itLeft;
        }

        *it = temp;
        itLeft = it + (index + 1);
        itRight = it + (index + 2);
    }
}


// Example showing heap and extracted values (sorted):
//           heap      |  sorted
//      -------------------------------
//      5, 4, 3, 2, 1  |
//                     |
//         1, 4 ,3, 2  |  5
//         4, 1, 3, 2  |  5
//         4, 2, 3, 1  |  5
//                     |
//            1, 2, 3  |  4, 5
//            3, 2, 1  |  4, 5
//                     |
//               1, 2  |  3, 4, 5
//               2, 1  |  3, 4, 5
//                     |
//                  1  |  2, 3, 4, 5
//                     |
//                     |  1, 2, 3, 4, 5
//
//               5              4              3              2              1
//              / \            / \            / \            /
//             4   3    ->    2   3    ->    2   1    ->    1        ->
//            / \            /
//           2   1          1
template<typename Iterator>
void heapSort(const Iterator begin, const Iterator end)
{
    Iterator last = (end - 1);
    if (begin < last)
    {
        for (int64_t index = ((last - begin) / 2); -1 < index; --index)
        {
            siftDown(begin, end, index);
        }

        for (; begin < last; --last)
        {
            auto temp = *last;
            *last = *begin;
            *begin = temp;

            siftDown(begin, last);
        }
    }
}
