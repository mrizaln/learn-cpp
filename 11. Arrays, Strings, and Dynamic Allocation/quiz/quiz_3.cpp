#include <iostream>

// [ description ]
/*---------------------------------------------------------------------------------------
    write your own function to swap the value of two integer variables
---------------------------------------------------------------------------------------*/

template <typename T>
void swap(T& a, T& b)
{
    T temp{ a };
    a = b;
    b = temp;
}

int main()
{
    int num1{ 215 };
    int num2{ 32532567 };

    std::cout << num1 << ' ' << num2 << '\n';

    swap(num1, num2);

    std::cout << num1 << ' ' << num2 << '\n';

    return 0;
}