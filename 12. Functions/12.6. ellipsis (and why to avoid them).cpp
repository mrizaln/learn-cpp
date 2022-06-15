#include <iostream>

/*---------------------------------------------------------------------------------------
                            ============[  ]============
---------------------------------------------------------------------------------------*/

/*
  - in all of the functions we've seen so far, the number of parameters a function will
    take must be known in advance (even if they have default values).
  - however, there are certain cases where it can be useful to be able to pass a variable
    number of parameters to a functions.
  - C++ provides a special specifier known as ellipsis (aka ""..."") that allow us to do
    precisely this.
*/

// functions that use ellipsis take the form:
/*---------------------------------------------------
    return_type function_name(argument_list, ...)
---------------------------------------------------*/

/*
  - note that functions that use ellipsis must have at least one non-ellipsis parameter.
  - any arguments passed to the function must match the argument_list paramteres first.
  
  - the ellipsis must always be the last parameter in the function.
  - the ellipsis capture any additional arguments (if there are any).
*/




/*---------------------------------------------------------------------------------------
                    =============[ an ellipsis example ]============
---------------------------------------------------------------------------------------*/

#include <cstdarg>      // needed to use ellipsis

namespace example
{
    double findAverage(int count, ...)
    {
        int sum{ 0 };

        // we access the llipsis through a va_list
        std::va_list list;

        // we initialize the va_list using va_start.
        va_start(list, count);

        // loop though all the ellipsis arguments
        for (int arg{ 0 }; arg < count; ++arg)
        {
            // we use va_arg to get parameters out of our ellipsis
            sum += va_arg(list, int);
        }

        // cleanup the va_list when we're done.
        va_end(list);

        return static_cast<double>(sum) / count;
    }

    void main()
    {
        std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
        std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';
    }
}




/*---------------------------------------------------------------------------------------
    ============[ why ellipsis are dangerous: type checking is suspended ]============
---------------------------------------------------------------------------------------*/

/*
  - with regular function paramters, the compiler uses type checking to ensure the types
    of the function arguments match the types of the function parameters (or can be implicitly
    converted so they match).
  - however, note that ellipsis paramters have no type declarations.
  - when using ellipsis, the compiler completely suspends type checking for ellipsis parameters.
  - this means, it is possible to send arguments of any type to the ellipsis!
*/

namespace example
{
    void arbitrary_type()
    {
        int value{ 7 };
        std::cout << findAverage(6, 1.0f, "Hello World!", "4", &value, value, &findAverage) << '\n';
    }
}




/*---------------------------------------------------------------------------------------
===[ why ellipsis are dangerous: ellipsis don't know how many parameters were passed ]===
---------------------------------------------------------------------------------------*/

// don't only ellipsis throw away the type of the paramters, it also throws away the number
// of paramters in the ellipsis.

// this means we have to devise our own solution for keeping track of the number of parameters
// passed into the ellipsis


    //======[ method 1: pass a length parameter ]======
    /*
        we have done this one above
    */



    //======[ method 2: use a sentinel value ]======
    /*
      - a [sentinel] is a special value that is used to terminate a loop when it is encountered.
      - for example, with strings, the null terminator is used a a sentinel value to denote
        the end of the string.
      - with ellipsis, the sentinel is typically passed in as the last parameter.
    */

    namespace working_with_ellipsis
    {
        // sentinel value: -1
        double findAverage_using_sentinel_value(int first, ...)
        {
            int sum{ first };

            std::va_list list;
            va_start(list, first);

            int count{ 1 };
            while (true)
            {
                int arg{ va_arg(list, int) };

                if (arg == -1) break;

                sum += arg;
                ++count;
            }

            va_end(list);

            return static_cast<double>(sum) / count;
        }

        void sentinel_value()
        {
            std::cout << "\nusing sentinel value:\n";
            std::cout << findAverage_using_sentinel_value(1, 2, 3, 4, 5, -1) << '\n';
            std::cout << findAverage_using_sentinel_value(1, 2, 3, 4, 5, 6, -1) << '\n';
        }
    }

    /*
      - we've chosen -1 as our sentinel value, that is fine if we only want to average positive
        numbers, but what if we want to include negative numbers?
      - sentinel values only work well if there is a value that falls outside the valid set
        of values for the problem you are trying to solve.
    */



    //======[ method 3: using a decoder string ]======

    // this involves passing a "decoder string" that tells the program how to interpret the
    // parameters

    namespace working_with_ellipsis
    {
        double findAverage_using_decoder(std::string decoder, ...)
        {
            double sum{ 0 };

            std::va_list list;
            va_start(list, decoder);

            int count{ 0 };
            while (true)
            {
                char codetype{ decoder[count] };
                switch (codetype)
                {
                default:
                case '\0':
                    // cleanup the va_list when we're done.
                    va_end(list);
                    return sum / count;
                case 'i':
                    sum += va_arg(list, int);
                    ++count;
                    break;
                case 'd':
                    sum += va_arg(list, double);
                    ++count;
                    break;
                }
            }
        }

        void using_decoder()
        {
            std::cout << "\nusing decoder string\n";
            std::cout << findAverage_using_decoder("iiiii", 1, 2, 3, 4, 5) << '\n';
            std::cout << findAverage_using_decoder("iiiiii", 1, 2, 3, 4, 5, 6) << '\n';
            std::cout << findAverage_using_decoder("iiddi", 1, 2, 3.5, 4.5, 5) << '\n';
        }
    }

    // this method has downsides as well: the decoder string can be a bit cryptic, and if
    // the optional paramters don't match the decoder string precisely, bad things can happen.

    // if you know printf on C, this is what it does.




/*---------------------------------------------------------------------------------------
          ============[ recommendations for safer use of ellipsis ]============
---------------------------------------------------------------------------------------*/

/*
  - first, if possible, do not use ellipsis at all!
  - second, if you do use ellipsis, do not mix expected argument types within your ellipsis
    if possible.
  - third, using a count parameter or decoder string as part of the argument list is generally
    safer than using a sentinel as an ellipsis paramter.
*/




// [ for advanded readers ]
/*---------------------------------------------------------------------------------------
    to improve upon ellipses-like functionality, C++11 introduced  [parameter packs] and
    [variadic templates]. which offers functionality similart to ellipses, but with
    strong type checking. however, significant usability challenges impeded adoption of
    this feature.

    in C++17, [fold expressions] were added, which significantly improves the usability
    of parameter packs, to the point where they are now a viable option.
---------------------------------------------------------------------------------------*/




//=======================================================================================

int main()
{
    example::main();
    example::arbitrary_type();

    working_with_ellipsis::sentinel_value();
    working_with_ellipsis::using_decoder();

    return 0;
}