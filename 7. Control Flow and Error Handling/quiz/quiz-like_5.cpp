#include <iostream>

// question #1
int main_even()
{
    for (int i{ 0 }; i <= 20; i += 2)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}


// question #2
int sumTo(int num)
{
    int sum { 0 };
    for (int i { 1 }; i <= num; ++i)
        sum += i;
    return sum;
}


int main()
{
    main_even();
    std::cout << "sumTo(5) = " << sumTo(5) << '\n';

    return 0;
}