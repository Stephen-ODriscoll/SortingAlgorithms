#pragma once

// Example showing splits and merges:
//      left copy | list(5, 4, 3, 2, 1)
//      -------------------------------
//             -  |  [5, 4] [3, 2, 1]
//             -  |  [4, 5] [1, 2, 3]    (recursively sorted)
//             -  |  4, 5, 1, 2, 3
//         [4, 5] |  1, 5, 1, 2, 3
//          ^     |  "     ^
//         [4, 5] |  1, 2, 1, 2, 3
//          ^     |     "     ^
//         [4, 5] |  1, 2, 3, 2, 3       (We're done with right side, insert the rest of left side)
//          ^     |        "     ^
//         [4, 5] |  1, 2, 3, 4, 3
//          ^     |           "
//         [4, 5] |  1, 2, 3, 4, 5
//          ^                    "
//
// Note: I've seen other merge sort algorithms copy both left and right halves. This isn't necessary.
//       We can use the right side directly in the list we're sorting. If we get to the end of the left list copy
//       before the end of the right list we're done as the rest of the right elements are in the list already sorted.
//       If we get to the end of the right list first we can override the rest of the right list with the left copy.
template<typename Iterator>
void mergeSort(const Iterator begin, const Iterator end)
{
    if (begin < end - 1)
    {
        const uint32_t size = (end - begin) / 2;
        const Iterator split = begin + size;
        mergeSort(begin, split);
        mergeSort(split, end);

        const Iterator beginLeft = new typename std::iterator_traits<Iterator>::value_type[size];
        const Iterator endLeft = beginLeft + size;
        for (Iterator next = begin, it = beginLeft; it < endLeft; ++it, ++next)
        {
            *it = *next;
        }

        Iterator itLeft = beginLeft;
        Iterator itRight = split;
        Iterator next = begin;
        for (; itLeft < endLeft; ++next)
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

        delete[] beginLeft;
    }
}
