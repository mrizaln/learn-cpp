#include <iostream>

int main()
{
    int outerCount { 5 };
    while (outerCount > 0)
    {
        int innerCount { 5 };
        while (innerCount > 0)
        {
            if (innerCount <= outerCount)
                std::cout << innerCount <<' ';

            --innerCount;
        }
        std::cout << '\n';
        --outerCount;
    }

    return 0;
}