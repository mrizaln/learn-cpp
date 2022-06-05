#include <iostream>
#include <algorithm>            //<< this chapter topic
#include <string_view>
#include <array>


// searching, counting, and sorting are such common operations to do, the C++ standard library
// comes with a bunch of functions to do these things in just a few lines of code.
// additionally, the STL come pre-tested, are efficient, work on a variety of different container
// types, and may support parallelization.

// the functionality provided in the algorithms library generally fall into one of three
// categories:
    // 1. inspectors    : used to view (butnot modify) data in a container
    // 2. mutators      : used to modify data in a container
    // 3. facilitators  : used to generate a result based on values of the data members.




/*---------------------------------------------------------------------------------------
         ============[ using std::find to find an element by value ]============
---------------------------------------------------------------------------------------*/

// std::find searches for the first occurence of a value in a container.
// std::find takes 3 parameters: an iterator to the starting element in the sequence, an
// iterator to the ending element, and a value to search for.
// it returns an iterator pointing to the element or the end of the container.

namespace using_std_find
{
    void main()
    {
        std::array arr{ 13, 90, 99, 5, 40, 80 };

        std::cout << "Enter a value to search for and replace with: ";
        int search{};
        int replace{};

        std::cin >> search >> replace;
        // input validation omitted

        // find
        auto found{ std::find(arr.begin(), arr.end(), search) };    // return end pointer if not found

        // replace
        if (found == arr.end())
            std::cout << "Could not find " << search << '\n';
        else
            *found = replace;
        
        // print
        for (int i : arr)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
==========[ using std::find_if to find an element that matches some condition ]==========
---------------------------------------------------------------------------------------*/

// the std::find_if function works similarly to std::find, but instead of passing a value
// to search for, we pass in a callable object, such as a function pointer (or a lambda)
// that checks to see if a match is found.
// std::find_if will call this function for every element until a matching element is found
// (or no more elements remain in the container to check).

namespace using_std_find_if
{
    bool containsNut(std::string_view str)
    {
        // std::string_view::find returns std::string_view::npos if it doesn't find the
        // substring. otherwise it returns the index where the substring occurs in str.
        return (str.find("nut") != std::string_view::npos);
    }

    void main()
    {
        std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

        // find_if
        auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };

        if (found == arr.end())
            std::cout << "No nuts\n";
        else
            std::cout << "Found " << *found << '\n';
    }
}




/*---------------------------------------------------------------------------------------
======[ using std::count and std::count_if to count how many occurences there are ]======
---------------------------------------------------------------------------------------*/

namespace using_std_count_and_count_if
{
    using using_std_find_if::containsNut;

    void main()
    {
        std::array<std::string_view, 5> arr{ "apple", "banana", "walnut", "lemon", "peanut" };

        // count strings that contain nut
        auto nuts{ std::count_if(arr.begin(), arr.end(), containsNut) };

        std::cout << "Counted " << nuts << " nut(s)\n";
    }
}




/*---------------------------------------------------------------------------------------
              ============[ using std::sort to custom sort ]============
---------------------------------------------------------------------------------------*/

// there's a version of std::sort that takes a function as its third parameter that allows
// us to sort however we like.
// the function takes two parameters to compare, and returns true if the first argument should
// be ordered before the second.
// by default, std::sort sorts the elements in ascending order.

namespace using_std_sort_to_custom_sort
{
    bool greater(int a, int b)
    {
        // order of @a before @b, if @a is greater than @b
        return (a > b);
    }

    void main()
    {
        std::array arr{ 13, 90, 99, 5, 40, 80 };

        std::sort(arr.begin(), arr.end(), greater);

        for (int i : arr)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}

// [ tip ]
//---------------------------------------------------------------------------------------
    // because sorting in descending order is common, C++ provides a custom type for that
    // named std::greater

    namespace using_std_sort_to_custom_sort
    {
        void using_std_greater()
        {
            std::array arr{ 13, 90, 99, 5, 40, 80 };

            // using std::greater
            std::sort(arr.begin(), arr.end(), std::greater{});

            for (int i : arr)
                std::cout << i << ' ';
            std::cout << '\n';
        }
    }

    // std::greater is a type, so we need the curly braces to instantiate a callable object
    // of that type.
//---------------------------------------------------------------------------------------




/*---------------------------------------------------------------------------------------
==========[ using std::for_each to do something to all elements of a container ]=========
---------------------------------------------------------------------------------------*/

// std::for_each takes a list as input and applies a custom function to every element.
// this is useful when we want to perform the same operation to every element in a list.

namespace using_std_for_each
{
    void doubleNumber(int & i)
    {
        i *= 2;
    }

    void main()
    {
        std::array arr{ 1, 2, 3, 4 };

        std::for_each(arr.begin(), arr.end(), doubleNumber);

        for (int i : arr)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ order of execution ]============
---------------------------------------------------------------------------------------*/

// most the algorithms in the algorithms library do not guarantee a particular order of
// executoin.
// for such algorithms, take care to ensure any functions you pass do not assume a particular
// ordering, as the order of invocation may not be the same on every compiler.

// guatanteed sequential execution: std::for_each, std::copy, std::copy_backward, std::move,
//                                  and std::move_backward.




/*---------------------------------------------------------------------------------------
                      ============[ ranges in C++20 ]============
---------------------------------------------------------------------------------------*/

// Having to explicitly pass arr.begin() and arr.end() to every algorithm is a bit annoying.
// But fear not -- C++20 adds ranges, which allow us to simply pass arr.
// This will make our code even shorter and more readable.

namespace ranges
{
    void main()
    {
        std::array arr{ 3, 30, 623, 23, 67, 34, 32 };

        std::ranges::sort(arr, std::greater{});
        std::ranges::for_each(arr, [](int i){std::cout << i << ' ';});    // using lambda (discussed in future chapter)

        std::cout << '\n';
    }
}




// [ best practice ]
/*---------------------------------------------------------------------------------------
    favor using functions from the algorithms library over writing your own functionality
    to do the same thing.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                    ============[ other algorithms ]============
---------------------------------------------------------------------------------------*/

/*
    std::find(begin, end, value)        -- find the first element that matches [value]

    std::find_if(begin, end, fctptr)    -- find the first element for which [fcnptr()] returns
                                           true, (returns end if none if found)

    std::max_element(begin, end, comp)  -- find the largest element ([comp] is equivalent to
                                           std::less by default)

    std::min_element(begin, end, comp)  -- find the smallest element ([comp] is equivalent to
                                           std::less by default)

    std::iota(begin, end, value)        -- fill the container with sequentially increasing
                                           values, starting with [value]

    std::accumulate(begin, end, op)     -- add up all elements in the container, optionally
                                           using [op] instead of [operator+]
*/




//=======================================================================================

int main()
{
    using_std_find::main();
    using_std_find_if::main();
    using_std_count_and_count_if::main();
    using_std_sort_to_custom_sort::main();
    using_std_for_each::main();
    ranges::main();

    return 0;
}