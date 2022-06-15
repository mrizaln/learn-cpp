#include <iostream>
#include <array>
#include <algorithm>
#include <string_view>
#include <functional>

/*
  - in chapter 11.19, we used std::sort() to sort an array, but we need to pass a function
    to the third parameter of std::sort() so that we can use custom sort.
  - thus, we forced to define a function to do that first.
  - but, if it only needed to be passed in once, it is a waste.
  - we have an alternative to that: lambdas.
*/


/*---------------------------------------------------------------------------------------
                    ============[ lambdas to the rescue ]============
---------------------------------------------------------------------------------------*/

/*
  - a [lambda expression] (also called a lambda or closure) allows us to define an anonymous
    function inside another function.
  - the nesting is important, as it allows us both to avoid namespace naming pollution,
    and to define the function as close to where it is used as possible.
*/

// [ the syntax ]
/*----------------------------------------------------
    [ captureClause ] ( parameters ) -> returnType
    {
        statements;
    }
----------------------------------------------------*/

/*
  - the capture caluse can be empty if no captures are needed.
  - the parameter list can be either empty or omitted if no parameters are required.
  - the return type is optional, and if omitted, auto will be assumed.
*/

namespace using_lambda
{
    void check_contains_nut()
    {
        constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

        const auto found{ std::find_if(arr.begin(), arr.end(), 
                                [](std::string_view str)
                                {
                                    return (str.find("nut") != std::string_view::npos);
                                }) };

        if (found == arr.end())
            std::cout << "No nuts\n";
        else
            std::cout << "Found " << *found << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                       ============[ type of lambda ]============
---------------------------------------------------------------------------------------*/

/*
  - in the above example, we defined a lambda right where it was needed.
  - this use of lambda is sometimes called a [function literal].

  - however, writing a lambda in the same line as it's used can sometimes make code harder
    to read.
  - we can initialize a lambda variable with a lambda function to use later.
*/

namespace type_of_lambda
{
    void check_is_even()
    {
        std::array arr{ 4, 2, 4, 6, 8, 0, 5, 4 };

        // lambda variable
        auto isEven{
            [](int i)
            {
                return ((i % 2) == 0);
            }
        };
        std::cout << "array is all even: "
                  << std::boolalpha
                  << std::all_of(arr.begin(), arr.end(), isEven) << '\n';
    }
}

/*
  - as it turns out, lambdas don't have a type that we can explicitly use.
  - when we write a lambda, the compiler generates a unique type just for the lambda that
    is not exposed to us.

  - although we don't know the type of lambda, there are several ways of storing a lambda
    for use post-definition.
  - if the lambda has an empty capture clause, we can use a regular function pointer.
  - std::function or type deduction via auto keyword will also work (even if non-empty
    capture clause).
*/

namespace type_of_lambda
{
    void lambda_type()
    {
        // A regular function pointer. Only works with an empty capture clause (empty []).
        double (*addNumbers1)(double, double){
            [](double a, double b) {
            return (a + b);
            }
        };

        addNumbers1(1, 2);

        // Using std::function. The lambda could have a non-empty capture clause (discussed next lesson).
        std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
            [](double a, double b) {
            return (a + b);
            }
        };

        addNumbers2(3, 4);

        // Using auto. Stores the lambda with its real type.
        auto addNumbers3{
            [](double a, double b) {
            return (a + b);
            }
        };

        addNumbers3(5, 6);
    }
}

/*
  - the only way of using the lambda's actual type is by means of [auto].
  - auto also has the benefit of having no overhead compared to std::function.

  - prior to C++20 though, we can't always use auto.
  - in cases where the actual lambda is unknown, we can't use auto without compromises.
  - in such cases, [std::function] can be used instead.
*/

namespace type_of_lambda
{
    void repeat(int repetitions, const std::function<void(int)>& fn)
    {
        for (int i{ 0 }; i < repetitions; ++i)
            fn(i);
    }

    void using_repeat()
    {
        repeat(3, [](int i) {
            std::cout << i << '\n';
        });
    }
}

/*
  - if we used auto for the type fn, the caller wouldn't know what parameters and return
    type fn need to have.
  - this limitation was lifted in C++20 when abbreviated function templates were added.

  - furthermore, functions with auto parameters cannot be separated into a header and source
    file.
*/


// [ rule ]
/*---------------------------------------------------------------------------------------
    use [auto] when initializing variables with lambdas, and [std::functions] if you can
    not initialize the variable with the lambda.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                      ============[ generic lambdas ]============
---------------------------------------------------------------------------------------*/

/*
  - since C++14, lambdas were allowed to use [auto] for parameters (one or more).
  - when a lambda has one or more auto parameter, the compiler will infer what parameter
    types are needed from the calls to the lambda.

  - because lambdas with one or more auto parameter can potentially work with a wide variety
    of types, they are called [generic lambdas].
*/

namespace generic_lambdas
{
    void main()
    {
        constexpr std::array months{
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December",
        };

        // search for two consecutive month that start with the same letter
        const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                                            [](const auto& a, const auto& b) {
                                                return (a[0] == b[0]);
                                            })};

        if (sameLetter != months.end())
        {
            std::cout << *sameLetter << " and " << *std::next(sameLetter)
                      << " start with the same letter\n";
        }
    }
}




/*---------------------------------------------------------------------------------------
            ============[ generic lambdas and static variables ]============
---------------------------------------------------------------------------------------*/

// one thing to aware of is that a unique lambda will be generated for each different type
// that [auto] resolves to.

namespace generic_lambdas_and_static_variables
{
    void main()
    {
        // Print a value and count how many times @print has been called.
        auto print{
            [](auto value) {
                static int callCount{ 0 };
                std::cout << callCount++ << ": " << value << '\n';
            }
        };

        print("hello"); // 0: hello
        print("world"); // 1: world

        print(1); // 0: 1
        print(2); // 1: 2

        print("ding dong"); // 2: ding dong
    }
}

/*
  - in the above code, we call the lambda with two different parameters.
  - this generates two different versions of the lambda with its own static variable.

  - if we want to define a shared static variable, we need to define a global variable or
    a static variable outside of the lambda.
  - we'll be able to avoid tose variables after talking about lambda captures in the next
    lesson.
*/




/*---------------------------------------------------------------------------------------
       ============[ return type deduction and trailing return types ]============
---------------------------------------------------------------------------------------*/

/*
  - if return type deduction is used, a lambda's return type is deduced from the [return]
    statements inside the lambda.
  - if return type inference is used, all return statements in the lambda must return the
    same type.
  - in case where we're returning different types, we have two options:
      > do explicit casts to make all the return types match, or
      > explicitly specify a return type for the lambda, and let the compiler do implicit
        conversions.
*/

namespace lambda_return_type_inference
{
    void main()
    {
        auto divide{ [](int x, int y, bool bInteger) -> double {
            if (bInteger)
                return x / y;       // will do implicit conversions to double
            else
                return static_cast<double>(x) / y;
        } };

        std::cout << divide(3, 2, true) << '\n';
        std::cout << divide(3, 2, false) << '\n';
    }
}




/*---------------------------------------------------------------------------------------
               ============[ standard library function objects ]============
---------------------------------------------------------------------------------------*/

// for common operations (e.g. addition, negation, or comparison) you don't need to write
// your own lambdas, because the STL comes with many basic callable objects that can be used
// instad.
// these are defined in the   <functional>   header.




//=======================================================================================

namespace quiz_1
{
    /*
        Create a struct Student that stores the name and points of a student. Create an
        array of students and use std::max_element to find the student with the most
        points, then print that student’s name. std::max_element takes the begin and end
        of a list, and a function that takes 2 parameters and returns true if the first
        argument is less than the second.
    */

    struct Student
    {
        std::string name{};
        int points{};
    };

    void main()
    {
        std::array<Student, 8> arr{
            { { "Albert", 3 },
              { "Ben", 5 },
              { "Christine", 2 },
              { "Dan", 8 },         // Dan has the most points (8).
              { "Enchilada", 4 },
              { "Francis", 1 },
              { "Greg", 3 },
              { "Hagrid", 5 } }
        };

        auto highest{ std::max_element(arr.begin(), arr.end(),
                                [](const Student& s1, const Student& s2) {
                                    return (s1.points < s2.points);
                                }) };
        if (highest != arr.end())
            std::cout << highest->name << " is the best student\n";
    }
}




namespace quiz_2
{
    /*
        use [std::sort] and a lambda in the following code to sort the seasons by ascending
        average temparature
    */

    struct Season
    {
        std::string_view name{};
        double averageTemperature{};
    };

    void main()
    {
        std::array<Season, 4> seasons{
            { { "Spring", 285.0 },
              { "Summer", 296.0 },
              { "Fall", 288.0 },
              { "Winter", 263.0 } }
        };

        /*
        * Use std::sort here
        */
        std::sort(seasons.begin(), seasons.end(),
                [](const Season& s1, const Season& s2) {
                    return (s1.averageTemperature < s2.averageTemperature);
                });

        for (const auto& season : seasons)
            std::cout << season.name << '\n';
    }
}




//=======================================================================================

int main()
{
    using_lambda::check_contains_nut();

    type_of_lambda::check_is_even();
    type_of_lambda::lambda_type();
    type_of_lambda::using_repeat();
    
    generic_lambdas::main();

    generic_lambdas_and_static_variables::main();

    lambda_return_type_inference::main();

    quiz_1::main();
    quiz_2::main();

    return 0;
}