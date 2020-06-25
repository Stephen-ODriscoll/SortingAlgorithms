#pragma once

template<typename Iterator>
void merge(const Iterator begin, const Iterator median, const Iterator end, const Iterator beginCopy)
{
    const Iterator endCopy = beginCopy + (median - begin);
    for (Iterator next = begin, it = beginCopy; it < endCopy; ++it, ++next)
    {
        *it = *next;
    }

    Iterator itLeft = beginCopy;
    Iterator itRight = median;
    for (Iterator next = begin; itLeft < endCopy; ++next)
    {
        if (itRight < end && *itRight < *itLeft)
        {
            *next = *itRight;
            ++itRight;
        }
        else
        {
            *next = *itLeft;
            ++itLeft;
        }
    }
}


// Example showing splits and merges:
//      left copy | list(5, 4, 3, 2, 1)
//      -------------------------------
//            -   |  [5, 4] [3, 2, 1]    (recursively sorted)
//                |
//            -   |  [4, 5] [1, 2, 3]
//                |
//          4, 5  |  1, 5, 1, 2, 3
//          ^     |  "     ^
//          4, 5  |  1, 2, 1, 2, 3
//          ^     |     "     ^
//          4, 5  |  1, 2, 3, 2, 3       (We're done with right side, insert the rest of left side)
//          ^     |        "     ^
//          4, 5  |  1, 2, 3, 4, 3
//          ^     |           "
//          4, 5  |  1, 2, 3, 4, 5
//             ^  |              "
//          4, 5  |  1, 2, 3, 4, 5
//
// Note: I've seen other merge sort algorithms copy both left and right halves. This isn't necessary.
//       We can use the right side directly in the list we're sorting. If we get to the end of the copied left list
//       before the end of the right list we're done as the rest of the right elements are in the list already sorted.
//       If we get to the end of the right list first we can override the rest of the right list with the left copy.

template<typename Iterator>
void mergeSort(const Iterator begin, const Iterator end, const Iterator beginCopy)
{
    if (begin < end - 1)
    {
        const Iterator median = begin + ((end - begin) / 2);

        mergeSort(begin, median, beginCopy);
        mergeSort(median, end, beginCopy);

        merge(begin, median, end, beginCopy);
    }
}

// Entry point that creates temporary memory and calls the above mergeSort
template<typename Iterator>
void mergeSort(const Iterator begin, const Iterator end)
{
    if (begin < end - 1)
    {
        const Iterator beginCopy = new typename std::iterator_traits<Iterator>::value_type[(end - begin) / 2];

        mergeSort(begin, end, beginCopy);

        delete[] beginCopy;
    }
}
