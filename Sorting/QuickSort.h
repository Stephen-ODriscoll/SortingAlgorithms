#pragma once

template<typename Iterator>
Iterator partition(const Iterator begin, const Iterator end)
{
    const Iterator last = (end - 1);
    const Iterator median = begin + ((end - begin) / 2);

    auto pivot = *median;
    *median = *last;
    *last = pivot;

    Iterator itLeft = begin;
    Iterator itRight = (last - 1);
    while (itLeft <= itRight)
    {
        while (*itLeft < pivot)
        {
            ++itLeft;

            if (itRight < itLeft)
            {
                goto done;
            }
        }

        while (pivot < *itRight)
        {
            --itRight;

            if (itRight < itLeft)
            {
                goto done;
            }
        }

        auto temp = *itRight;
        *itRight = *itLeft;
        *itLeft = temp;

        ++itLeft, --itRight;
    }

done:
    *last = *itLeft;
    *itLeft = pivot;

    return itLeft;
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
void quickSort(const Iterator begin, const Iterator end)
{
    if (begin < (end - 1))
    {
        Iterator split = partition(begin, end);

        quickSort(begin, split);
        quickSort((split + 1), end);
    }
}
