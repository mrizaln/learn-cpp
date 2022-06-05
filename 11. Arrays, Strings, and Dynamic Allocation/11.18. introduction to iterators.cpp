#include <iostream>
#include <array>
#include <vector>

/*---------------------------------------------------------------------------------------
                        ============[ iterators ]============
---------------------------------------------------------------------------------------*/

/*
  - an iterator is an object designed to traverse through a container (e.g. the values in
    an array), providing access to each element along the way.
  - a container may provide different kinds of iterators.
  - once the appropiate type of iterator is created, the programmer can then use the interface
    provided by the iterator to traverse and access elements without having to worry about
    what kind of traversal is being done or how the data is being stored in the container.
  - iterators typically use the same interface for traversal (operator++ and operator*).
*/




/*---------------------------------------------------------------------------------------
                  ============[ pointers as an iterator ]============
---------------------------------------------------------------------------------------*/

// the simplest kind of iterator is a pointer, which works for data stored sequentially in
// memory.

namespace pointer_iterators
{
    void main()
    {
        std::array data{ 0, 1, 2, 3, 4, 5, 6};

        auto begin{ &data[0] };
        auto end{ begin + std::size(data) };

        for (auto ptr{ begin }; ptr != end; ++ptr)
            std::cout << *ptr << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                ============[ standard library iterators ]============
---------------------------------------------------------------------------------------*/

// instead of calculating our own begin and end points, we can simply as the container for
// the begin and end points via functions (begin() and end()).

namespace stl_iterators
{
    void main()
    {
        std::array array{ 1, 2, 3 };
        
        auto begin{ array.begin() };
        auto end{ array.end() };

        for (auto p{ begin }; p != end; ++p)
            std::cout << *p << ' ';
        std::cout << '\n';
    }
}

// the <iterator> header also contains two generic functions std::begin and std::end that
// can be used




/*---------------------------------------------------------------------------------------
                ============[ back to range-based for loops ]=============
---------------------------------------------------------------------------------------*/

// all types that have both begin() and end() member functions, or that can be used with
// std::begin() and std::end(), are usable in range-based for-loops.

// range-based for-loops aren't the only thing that makes use of iterators.
// they're alos used in std::sort and other algorithms.




/*---------------------------------------------------------------------------------------
          ============[ iterator invalidation (dangling iterators) ]============
---------------------------------------------------------------------------------------*/

// much like references and pointers, iterators can be left "dangling" if the elements being
// iterated over change address or are destroyed.
// when this happends, we say the iterator has been invalidated.
// accessing an invalidated iterator produces undefined behavior.

// some operations that modify containers (such as adding an element to a std::vector) can
// have the side effect of causing the elements in the container to change addresses.
// when this happens, existing iterators to those elements will be invalidated.

namespace iterator_invalidation
{
    void main()
    {
        std::vector v{ 1, 2, 3, 4, 5, 6, 7 };

        auto it{ v.begin() };

        ++it;
        std::cout << *it << '\n';       // ok: prints 2

        v.erase(it);    // erase the element currently being iterated over

        // erase() invalidates iterators to the erased element (and subsequent elements)
        // iterator ir is now invalidated

        ++it;
        std::cout << *it << '\n';       // undefined behavior

        // for (auto i : v)
        //     std::cout << i << ' ';
        // std::cout << '\n';
    }
}




//=======================================================================================

int main()
{
    pointer_iterators::main();

    stl_iterators::main();

    iterator_invalidation::main();

    return 0;
}