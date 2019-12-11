#pragma once

// Example showing swapped elements:
//      lowest | list(5, 4, 3, 2, 1)
//      ----------------------------
//          4  |  5, 4, 3, 2, 1
//             |  "  ^
//          3  |  5, 4, 3, 2, 1
//             |  "     ^
//          2  |  5, 4, 3, 2, 1
//             |  "        ^
//          1  |  5, 4, 3, 2, 1
//             |  "           ^
//          3  |  1, 4, 3, 2, 5
//             |     "  ^
//          2  |  1, 4, 3, 2, 5
//             |     "     ^
//          2  |  1, 4, 3, 2, 5
//             |     "        ^
//          3  |  1, 2, 3, 4, 5
//             |        "  ^
//          3  |  1, 2, 3, 4, 5
//             |        "     ^
//          4  |  1, 2, 3, 4, 5
//             |           "  ^
//          -  |  1, 2, 3, 4, 5
template<typename Iterator>
void selectionSort(const Iterator begin, const Iterator end)
{
    // Everything left of next is already sorted
    for (Iterator next = begin; next < (end - 1); ++next)
    {
        Iterator lowest = next;

        for (Iterator it = (next + 1); it < end; ++it)
        {
            if (*it < *lowest)
            {
                lowest = it;
            }
        }

        auto temp = *lowest;
        *lowest = *next;
        *next = temp;
    }
}
