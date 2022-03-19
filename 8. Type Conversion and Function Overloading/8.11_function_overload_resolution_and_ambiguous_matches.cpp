// #define ALLOW_ERROR_AMBIGUOUS_MATCH

#include <iostream>
#include <string>

/*---------------------------------------------------------------------------------------
            ============[ resolving overloaded function calls ]============
---------------------------------------------------------------------------------------*/

// when a function call is made to an overloaded function, the compiler steps through a sequence
// of rules to determine which (if any) of the overloaded functions is the best match.

// at each step, the compiler applies a bunch of different type conversions to the argument(s)
// in the function call.
// for each conversion applied, the compiler chechks if any of the overloaded functions are
// now a match

// the result will be one of three possible outcomes:
    // > no matching functions were found; the compiler moves to the next step in the sequence.

    // > a single matching function was found; the matching is complete.

    // > more than one matching function was found; the compiler will issue an ambiguous
    //   match compile error.

// if the compiler reaches the end of the entire sequence without finding a match, it will
// generate a compile error that no matching overloaded function could be found for the function
// call.




/*---------------------------------------------------------------------------------------
               ============[ the argument matching sequence ]============
---------------------------------------------------------------------------------------*/

// step 1: [ exact match ]

    // this happens in two phases

    // first, the compiler will see if there is an overloaded function where the type of the
    // arguments in te function call exectly matches the type of the parameters in the overloaded
    // function


    namespace exact
    {
        void print(int)
        {
        }

        void print(double)
        {
        }

        int main()
        {
            print(0);       // exact match with print(int)
            print(4.3);     // exact match with print(double)

            return 0;
        }
    }

    // second, the compiler will apply a number of trivial conversions to the arguments in
    // the function call.

    namespace exact_trivial_conversion
    {
        void print(const int)
        {
        }

        void print(double)
        {
        }

        int main()
        {
            int x { 0 };
            print(x);       // x trivially converted to const int

            return 0;
        }
    }


// step 2: [ numeric promotion ]

    // if no exact match is found, the compiler tries to promote the argument(s) to find matching
    // function

    namespace numeric_promotion
    {
        void print(int)
        {
        }

        void print(double)
        {
        }

        int main()
        {
            print('a');       // promoted to match print(int)
            print(4.5f);      // promoted to match print_e(double)

            return 0;
        }
    }


// step 3: [ numeric conversion ]

    // if no match find by above, the compiler tries to find a match by applying conversions

    namespace numeric_conversion
    {
        void print(double)
        {
        }

        void print(std::string)
        {
        }

        int main()
        {
            print('a');     // 'a' converted to match print(double)

            return 0;
        }
    }


// step 4: [ user-defined type conversion ]

    // if no match found by above, the compiler tries to match through any user-defined conversions.

    namespace user_defined_type_conversion
    {
        // we haven't covered classses yet
        class XYZ     // this defines a new type called X
        {
        public:
            operator int() { return 0; }    // here's a user-defined conversion from X to int
        };

        void print(int)
        {
        }

        void print(double)
        {
        }

        int main()
        {
            XYZ x;      // here, we're creating an object of type XYZ
            print(x);   // x converted from XYZ to int

            return 0;
        }
    }


// step 5: [ elipsis ]

    // if no match is found by above, the compiler will look for amatching function that uses
    // elipsis

    // [ see lesson 11.7 for elipsis ]


// step 6: [ compile error ]

    // if no match found at this point, the compiler will issue a compile error about not
    // being able to find a matching function




/*---------------------------------------------------------------------------------------
                    ============[ ambiguous matches ]============
---------------------------------------------------------------------------------------*/

// an ambiguous match occurs when the compiler find two or more functions that can be made
// to match in the same step.
// when this occurs, the compiler will issue a compile error.

#ifdef ALLOW_ERROR_AMBIGUOUS_MATCH
namespace ambiguous_match
{
    void print(int x)
    {
    }

    void print(double d)
    {
    }

    int main()
    {
        print(5l);      // 5l is type long

        return 0;
    }
}
#endif

// step 1 can't be done, since no exact match.
// step 2 can't be done also, because long can't be promoted

// at step 3 however, the argument (type long) will be converted to other types.
// in the process of checking all the numeric conversion rules, the compiler will find two
// potential matches:
    // > if long is converted to int, it will match print(int)
    // > if long is converted to double, it will match print(double)

// [ key insight ]
/*---------------------------------------------------------------------------------------
    if the compiler finds multiple matches in a given step, an ambiguous function call
    will result. this means no match from a given step is considered to be better than
    any other match from the same step.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                ============[ resolving ambiguous matches ]============
---------------------------------------------------------------------------------------*/

// ambiguous matches are compile-time error, so it needs to be disambiguated before it compiled.

// there are a few ways to resolve ambiguous matches:
    // 1. simply define a new overloaded function that takes parameters of exactly the type
    //    you are trying to call the function with.

    // 2. alternatively, explicitly cast the ambiguous arguments(s) to match the type of the
    //    function you want to call.

namespace resolving_ambiguous_match
{
    void print(unsigned int x)
    {
    }

    void print(float y)
    {
    }

    int main()
    {
        print(static_cast<unsigned int>(0));    // cast int to unsigned int
        print(static_cast<float>(3.14159));     // cast double to float

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
       ============[ matching for functions with multiple arguments ]============
---------------------------------------------------------------------------------------*/

// if there are multiple arguments, the ompiler applies the matching rules to each argument
// in turn.
// the function chosen is the one for which each argument matches at elast as well as the
// other functions, with at least one argumet matching better thatn all the other functions.

// in other words, the function chosen must provide a better match than any other candidate
// functions for at least one parameter, and no worse for all other parameters.

namespace multiple_parameter_match
{
    void print(char c, int x)
    {
        std::cout << 'a';
    }

    void print(char c, double x)
    {
        std::cout << 'b';
    }

    void print(char c, float x)
    {
        std::cout << 'c';
    }

    int main()
    {
        print('x', 'a');        // will match print(char, int)

        return 0;
    }
}



//=======================================================================================

int main()
{
    exact::main();
    exact_trivial_conversion::main();
    numeric_promotion::main();
    numeric_conversion::main();    // int can be numerically converted to unsigned int or to float
    user_defined_type_conversion::main();
#ifdef ALLOW_ERROR_AMBIGUOUS_MATCH
    ambiguous_match::main();
#endif
    resolving_ambiguous_match::main();
    multiple_parameter_match::main();

    return 0;
}