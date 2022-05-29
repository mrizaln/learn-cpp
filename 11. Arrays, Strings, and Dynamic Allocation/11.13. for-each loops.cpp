#include <iostream>

// we already know how to iterate through an array using for loop.
// but we do that manually by specifying an index that is increasing.
// this is error prone.

// there's a sompler and safer type of loop called a [for-each] loop (also called a [range-
// based for-loop] for cases where we want to iterate through every elememnt in an array.


/*---------------------------------------------------------------------------------------
                       ============[ for-each loops ]============
---------------------------------------------------------------------------------------*/

// the for each statement has a syntax that looks like this:
/*------------------------------------------
    for (element_declaratoin : array)
        statement;
------------------------------------------*/

// when this statement is encountered, the loop will iterate through each element in array,
// assigning the value of the current array element to the variable declared in element_declaration.

// example
namespace for_each_loops
{
    void main()
    {
        constexpr int fibonacci[] { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

        for (int number : fibonacci)
            std::cout << number << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
            ============[ for-each loops and the auto keyword ]============
---------------------------------------------------------------------------------------*/

namespace for_each_loops_and_auto_keyword
{
    void main()
    {
        constexpr int fibonacci[] { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

        for (auto number : fibonacci)       // using auto here helps
            std::cout << number << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                ============[ for-each loop and references ]============
---------------------------------------------------------------------------------------*/

// on the above example, we copy the value from the array to the variable number, this can
// be expensive.
// fortunately, we can use references

namespace for_each_loops_and_references
{
    void main()
    {
        std::string array[] { "peter", "likes", "frozem", "yogurt" };

        for (const auto& element : array)    // it's a good idea to make your reference const
            std::cout << element << ' ';
        std::cout << '\n';
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    in for-each loops element declarations, if your elements are non-fundamental types,
    use references or const references for performance reasons.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                ============[ for-each loops and non-arrays ]============
---------------------------------------------------------------------------------------*/

// for-each loops work with many kinds of list-like structures, such as vectors, linked lists,
// trees, and maps.

#include <vector>

namespace for_each_loops_and_non_array
{
    void main()
    {
        std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
        // before C++17:
        // std::vector<int>  fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };;

        for (auto number : fibonacci)
            std::cout << number << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
       ============[ for-each doesn't work with pointers to an array ]============
---------------------------------------------------------------------------------------*/

// in order to iterate through the array, for-each needs to know how big the array is, which
// means knowing the array size.
// because arrays that have decayed into a pointer do not know their size, for-each loop will
// not work with them.

// dynamic arrays won't work with for-each loops for the same reason.




/*---------------------------------------------------------------------------------------
        ============[ can i get the index of the current element? ]============
---------------------------------------------------------------------------------------*/

// for-each loops do not provide a direct way to get the array index of the current element.

// since C++20, range-based for-loops can be used with an [init-statement].
// we can use this to create a manual index.

// syntax:
/*-------------------------------------------------------
    for (init_statement; element_declaration : array)
        statement;
-------------------------------------------------------*/

namespace for_each_loops_with_init_statement
{
    void main()
    {
        std::string names[] { "Alex", "Betty", "Caroline", "Dave", "Emily" };
        constexpr int scores[] { 84, 92, 76, 81, 56 };

        int maxScore { 0 };

        for (int i { 0 }; auto score : scores)
        {
            if (score > maxScore)
            {
                std::cout << names[i]
                          << " beat the previous best score of "
                          << maxScore
                          << " by "
                          << (score - maxScore)
                          << " points!\n";
                
                maxScore = score;
            }
            ++i;
        }
    }
}



//=======================================================================================

int main()
{
    for_each_loops::main();
    for_each_loops_and_references::main();
    for_each_loops_and_non_array::main();
    for_each_loops_with_init_statement::main();

    return 0;
}