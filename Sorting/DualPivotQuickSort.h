#pragma once

template<typename Iterator>
void partition(const Iterator begin, const Iterator end, Iterator &splitLeft, Iterator &splitRight)
{
    const Iterator last = (end - 1);

    if (*last < *begin)
    {
        auto temp = *last;
        *last = *begin;
        *begin = temp;
    }

    auto leftPivot = *begin;
    auto rightPivot = *last;

    splitLeft = begin;
    splitRight = last;
    Iterator it = (begin + 1);
    while (it < splitRight)
    {
        if (*it < leftPivot)
        {
            ++splitLeft;

            auto temp = *it;
            *it = *splitLeft;
            *splitLeft = temp;

            ++it;
        }
        else if (rightPivot < *it)
        {
            --splitRight;

            auto temp = *it;
            *it = *splitRight;
            *splitRight = temp;
        }
        else
        {
            ++it;
        }
    }

    *begin = *splitLeft;
    *splitLeft = leftPivot;

    *last = *splitRight;
    *splitRight = rightPivot;
}


// Example showing splits and merges:
//      pivot | list(5, 4, 3, 2, 1)
//      ---------------------------
//         3  |  5, 4, 3, 2, 1       (Move the pivot to the side)
//            |        "
//         3  |  5, 4, 1, 2, 3
//            |  ^        ^
//         3  |  2, 4, 1, 5, 3
//            |     ^  ^
//         3  |  2, 1, 4, 5, 3       (The iterators have crossed)
//            |     ^  ^
//         3  |  2, 1, 3, 5, 4       (Reinsert the pivot)
//            |        "
//         3  |  [2, 1] 3 [5, 4]     (recursively sorted)
//            |
//         3  |  [1, 2] 3 [4, 5]
//            |
//         3  |  1, 2, 3, 4, 5
template<typename Iterator>
void dualPivotQuickSort(const Iterator begin, const Iterator end)
{
    if (begin < (end - 1))
    {
        Iterator splitLeft, splitRight;
        partition(begin, end, splitLeft, splitRight);

        dualPivotQuickSort(begin, splitLeft);
        dualPivotQuickSort((splitLeft + 1), splitRight);
        dualPivotQuickSort((splitRight + 1), end);
    }
}
