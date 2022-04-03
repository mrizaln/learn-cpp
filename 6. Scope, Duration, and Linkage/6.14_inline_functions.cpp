#include <iostream>

//---------------------------------------------------------------------------------------

/*
  - say, we need to write some code to perform some discrete task.
  - we can make a function.
  - but every time we call this function, there is a certain amount of performance overhead
    that occurs.
  - for large function, this overhead is insigneificant compared to the amounf of time the
    function takes to run.
  - but what if the function is small?
*/


// introducing:

/*---------------------------------------------------------------------------------------
                    ============[ inline expansion ]============
---------------------------------------------------------------------------------------*/

/*
  - inline expansion is a process where a function call is replaced by the code from the
    called function's definition
  - inline expansion can also allow the copmiler to optimize the resulting code more efficiently
*/

namespace example
{
    int min(int x, int y)
    {
        return (x < y) ? x : y;
    }

    int main()
    {
        std::cout << min(4, 6);
        // becomes:
        std::cout << (4 < 6) ? 4 : 6;

        std::cout << min(6, 1);
        // becomes:
        std::cout << (6 < 1) ? 6 : 1;

        return 0;
    }
}


/*
  - inline expansion has it own potential cost: if the body of the function being expanded takes
    more instructions that the function call being replaced, then each inline expansion will
    cause the executable to grow larger. larger executables tend to be slower

  - inline expansion could result in performance improvement, performance reductions or no
    change to performance at all.
  - inline expansion is best suited to simple, short functions (e.g. no more than a few statements)
*/




/*---------------------------------------------------------------------------------------
              ============[ when inline expansion occurs ]============
---------------------------------------------------------------------------------------*/

/*
  - every function fall into one of these category, where calls to the function:
        > must be expanded
        > may be expanded (most functions)
        > can't be expanded

  - a modern compiler will asess each function and each function call to make a determination
    about whether that particular function call would benefit from inline expansion.
  - a compiler might decide to expand none, some, or all of the function calls
*/




/*---------------------------------------------------------------------------------------
            =============[ the inline keyword, historically ]============
---------------------------------------------------------------------------------------*/

/*
  - historically, compilers either didn't have the capability to determine whether inline
    expansion would be beneficial or were not very good at it.
  - for that reason, C++ provide the keyword [inline], which was intended to be used as a
    hit to the compiler that a function would be benefit from being expanded inline.
*/

namespace inline_then
{
    inline int min(int x, int y)
    {
        return (x < y) ? x : y;
    }

    int main()
    {
        std::cout << min(4, 6);
        std::cout << min(9, 3);
        return 0;
    }
}

/*
  - modern optimizing compilers are typically very good at determining which functions should
    be makde inline -- better than humans in most cases.
  - the compiler will likely ignore or devalue any request to inline a function anyway.
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    do not use [inline] keyword to request inline expansion for your functions
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
        ============[ the inline keyword, modernly ]============
---------------------------------------------------------------------------------------*/

/*
  - in [./6.9_sharing_global_constants_across_multiple_files], the [inline] concept has evolved
    to have a new meaning: multiple difinitions are allowed in the program.
  - this is true for functions as well as variables.
  - if we mark a function as inline, then that function is allowd to have multiple definitions
    (in different files), as long as those definitions are identical.

  - in order to do inline expansion, the compiler needs to be able to see the full definition
    of an inline function wherever the function is called.
  - therefore, inline functions are typically defined in header files, where they can be
    [#include]d into any code file that need to see the full definition of the function
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    avoid the use of the [inline] keyword for functions unless you have a specific,
    compelling reason to do so.
---------------------------------------------------------------------------------------*/
