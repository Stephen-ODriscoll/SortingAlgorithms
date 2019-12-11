
#pragma once
#include <random>
#include <ctime>

namespace random
{
    static inline void initialize()
    {
        std::srand((unsigned int)std::time(NULL));
    }

    static inline int integer(const int range)
    {
        return std::rand() % (range + 1);
    }

    static inline int integer(const int rangeLower, const int rangeHigher)
    {
        if (rangeHigher <= rangeLower)
        {
            throw std::exception("higher end of range must be larger than lower end");
        }

        return (std::rand() % (rangeHigher - rangeLower + 1)) + rangeLower;
    }
}