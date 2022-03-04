#include <iostream>

int main()
{
    int outerCount { 1 };
    while (outerCount <= 5)
    {
        int innerCount { 5 };
        while (innerCount > 0)
        {
            if (innerCount <= outerCount)
                std::cout << innerCount << ' ';
            else
                std::cout << "  ";

            --innerCount;
        }

        std::cout << '\n';
        ++outerCount;
    }

    return 0;
}