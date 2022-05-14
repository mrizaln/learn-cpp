// [ Description ]
/*---------------------------------------------------------------------------------------
    Create a class template named Triad that has 3 members of the same template type. 
---------------------------------------------------------------------------------------*/

#include <iostream>

template <typename T>
struct Triad
{
    T first {};
    T second {};
    T third {};
};

// for C++17
template <typename T>
Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(Triad<T> t)
{
    std::cout << '[' << t.first << ", " << t.second << ", " << t.third << "]\n";   
}

int main()
{
    Triad t1 { 1, 2, 3 };
    print(t1);

    Triad t2 { 1.2, 3.4, 5.6 };
    print(t2);
}