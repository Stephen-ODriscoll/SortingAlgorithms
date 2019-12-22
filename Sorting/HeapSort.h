#pragma once

// This optimized variant of sift down assumes the top number belongs somewhere at the bottom
template<typename Iterator>
void siftDown(const Iterator begin, const Iterator end)
{
    int64_t index = 0;
    Iterator it = begin;
    Iterator itLeft = begin + 1;
    Iterator itRight = begin + 2;
    while (itLeft < end)
    {
        auto temp = *it;
        if (itRight < end && *itLeft < *itRight)
        {
            index = (index * 2) + 1;
            *it = *itRight;
            it = itRight;
        }
        else
        {
            index = (index * 2) + 1;
            *it = *itLeft;
            it = itLeft;
        }

        *it = temp;
        itLeft = it + (index + 1);
        itRight = it + (index + 2);
    }
}


template<typename Iterator>
void heapify(const Iterator begin, const Iterator end)
{
    int64_t indexUp = (((end - begin) - 2) / 2);
    Iterator itUp = begin + indexUp;
    Iterator itLeftUp = itUp + (indexUp + 1);
    Iterator itRightUp = itLeftUp + 1;
    while (begin <= itUp)
    {
        int64_t indexDown = indexUp;
        Iterator itDown = itUp;
        Iterator itLeftDown = itLeftUp;
        Iterator itRightDown = itRightUp;
        while (itLeftDown < end)
        {
            auto temp = *itDown;
            if (itRightDown < end && *itLeftDown < *itRightDown)
            {
                if (*itRightDown < *itDown)
                {
                    break;
                }

                indexDown = (indexDown * 2) + 1;
                *itDown = *itRightDown;
                itDown = itRightDown;
            }
            else
            {
                if (*itLeftDown < *itDown)
                {
                    break;
                }

                indexDown = (indexDown * 2) + 1;
                *itDown = *itLeftDown;
                itDown = itLeftDown;
            }

            *itDown = temp;
            itLeftDown = itDown + (indexDown + 1);
            itRightDown = itDown + (indexDown + 2);
        }

        --indexUp;
        --itUp;
        itLeftUp -= 2;
        itRightUp -= 2;
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
        heapify(begin, end);

        for (; (begin + 2) < last; --last)
        {
            auto temp = *last;
            *last = *begin;
            *begin = temp;

            siftDown(begin, last);
        }
    }
}
