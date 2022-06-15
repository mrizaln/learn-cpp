#include <iostream>
#include <string_view>
#include <array>
#include <functional>
#include <algorithm>
#include <vector>


/*---------------------------------------------------------------------------------------
            ============[ capture clause and capture by value ]============
---------------------------------------------------------------------------------------*/

/*
  - unlike nested blocks, where any identifier defined in outer block is accessible in the
    scope of the nested block, lambdas can only access specific kinds of identifiers: global
    identifiers, entities that are known at compile time, and entities with static duration.
*/




/*---------------------------------------------------------------------------------------
                    ============[ how captures work ]============
---------------------------------------------------------------------------------------*/

/*
  - when a lambda definition is executed, for each variable that the lambda captures, a
    clone of that variable is made (with identical name) inside the lambda.
  - each captured variables becomes a data member of the lambda.
*/




/*---------------------------------------------------------------------------------------
                    ============[ the capture clause ]============
---------------------------------------------------------------------------------------*/

/*
  - the [capture clause] is used to (indirectly) give a lambda access to variables available
    in the surrounding scope that it normally would not have access to.
*/

namespace the_capture_clause
{
    void main()
    {
        std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

        std::cout << "search for: ";
        
        std::string search{};
        std::cin >> search;

        // capture @search                                vvvvvv
        auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
                                                            return (str.find(search) != std::string_view::npos);
                                                        }) };
        if (found == arr.end())
            std::cout << "Not found\n";
        else
            std::cout << "Found " << *found << '\n';
    }
}




/*---------------------------------------------------------------------------------------
               ============[ captures default to const value ]============
---------------------------------------------------------------------------------------*/

// by default variables are captured by const value.

namespace captures_default_to_const_value
{
    void main()
    {
        int ammo{ 10 };

        // Define a lambda and store it in a variable called "shoot".
        auto shoot{
            [ammo]() {
                // // Illegal, ammo was captured as a const copy.
                // --ammo;

                std::cout << "Pew! " << ammo << " shot(s) left.\n";
            }
        };

        // Call the lambda
        shoot();

        std::cout << ammo << " shot(s) left\n";
    }
}




/*---------------------------------------------------------------------------------------
                  ============[ mutable capture by value ]============
---------------------------------------------------------------------------------------*/

// to allow modifications of variables that were captured by value, we can mark the lambdas
// as [mutable], it will removes the const qualification from all variables captured by value.

namespace mutable_capture
{
    void main()
    {
    int ammo{ 10 };

    auto shoot{
        // Added mutable after the parameter list.
        [ammo]() mutable {
            // We're allowed to modify ammo now
            --ammo;

            std::cout << "Pew! " << ammo << " shot(s) left.\n";
        }
    };

    shoot();
    shoot();

    std::cout << ammo << " shot(s) left\n";
    }
}

// since ammo inside the lambda is a copy, any modification to that ammo won't reflect outside
// the lambda.


// [ warning ]
/*---------------------------------------------------------------------------------------
    because captured variables are members of the lambda object, their values are
    persisted accross multiple calls to the lambda.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                    ============[ capture by reference ]============
---------------------------------------------------------------------------------------*/

/*
  - to capture a variable by reference, we prepend an ampersand (&) to the variable name
    in the capture.
  - variables that are captured by reference are non-const, unless the variable they're
    capturing is const.
*/

namespace capture_by_reference
{
    void main()
    {
        int ammo{ 10 };

        auto shoot{
            // we don't need mutable anymore
            [&ammo]() {
                --ammo;
                std::cout << "Pew! " << ammo << " shot(s) left.\n";
            }
        };

        shoot();

        std::cout << ammo << " shot(s) left.\n";
    }
}




/*---------------------------------------------------------------------------------------
                ============[ capturing multiple variables ]============
---------------------------------------------------------------------------------------*/

// multiples variables can be captured by separating them with a comma.




/*---------------------------------------------------------------------------------------
                      ============[ default captures ]============
---------------------------------------------------------------------------------------*/

/*
  - having to explicitly list the variables is burdensome.
  - fortunately, we can enlist the compiler's help to auto-generate a list of variables
    we need to capture.

  - a [default capture] (also capture-default) captures all variables that are mentioned
    in the lambda.

  - to capture all used variables by value use a capture value of [=]
  - to capture all used variables by reference use  a capture value of [&]
*/

namespace default_captures
{
    void main()
    {
        std::array areas{ 100, 25, 121, 40, 56 };

        int width{};
        int height{};

        std::cout << "Enter width and height: ";
        std::cin >> width >> height;

        auto found{ std::find_if(areas.begin(), areas.end(),
                                    [=](int knownArea) {
                                        return (width * height == knownArea);
                                    }) };

        if (found == areas.end())
            std::cout << "I don't know this area :(\n";
        else
            std::cout << "Area found :)\n";
    }
}

// default captures can be mixed with normal captures.
// we can capture some variables by value and others by reference.




/*---------------------------------------------------------------------------------------
        ============[ defining new variables in the lambda-capture ]============
---------------------------------------------------------------------------------------*/

// we can declare a new variable that is only visible in the scope of the lambda by defining
// a variable in the lambda-capture without specifying its type.

namespace declaring_new_variable_in_the_captures
{
    void main()
    {
        std::array areas{ 100, 25, 121, 40, 56 };

        int width{};
        int height{};

        std::cout << "Enter width and height: ";
        std::cin >> width >> height;

        // We store areas, but the user entered width and height.
        // We need to calculate the area before we can search for it.
        auto found{ std::find_if(areas.begin(), areas.end(),
                                // Declare a new variable that's visible only to the lambda.
                                // The type of userArea is automatically deduced to int.
                                [userArea{ width * height }](int knownArea) {
                                    return (userArea == knownArea);
                                }) };

        if (found == areas.end())
            std::cout << "I don't know this area :(\n";
        else
            std::cout << "Area found :)\n";
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    only initialize variables in the capture if their value is short and their type is
    obvious. otherwise it's best to define the variable outside of the lambda and capture
    it.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                ============[ dangling captured variables ]============
---------------------------------------------------------------------------------------*/

// variables are captured at the point where the lambda is defined.
// if a variable captured by reference dies before the lambda, the lambda will be left
// holding a dangling reference.




/*---------------------------------------------------------------------------------------
            ============[ unintended copies of mutable lambdas ]============
---------------------------------------------------------------------------------------*/

namespace unintended_copies_of_mutable_lambdas
{
    void main()
    {
        int i{ 0 };

        // create a new lambda named count
        auto count{ [i]() mutable {
            std::cout << ++i << '\n';
        } };

        count();        // prints: 1

        auto otherCount{ count };   // create a copy of count at current state (i = 1)

        count();        // prints: 2
        otherCount();   // prints: 2
    }
}

// when we created otherCOunt as a copy of count, we created a copy of count in its current
// state.

// take a look at less obvious ecample:

namespace unintended_copies_of_mutable_lambdas
{
    void myInvoke(const std::function<void()>& fn)
    {
        fn();
    }

    void main_()
    {
        int i{ 0 };

        // increments and prints its local copy of @i
        auto count{ [i]() mutable {
            std::cout << ++i << '\n';
        } };

        myInvoke(count);    // prints 1   
        myInvoke(count);    // prints 1   
        myInvoke(count);    // prints 1   
    }
}

// in the above code, when myInvoke is called, the std::function on the parameter internally
// makes a copy of the lambda object.

/*
  - if we need to pass a mutable lambda, and want to avoid the possibility of copies being
    made, there are two options.
  - first is to not use the capture.
  - a better option is to prevent copies of lambda from being made in the first place.

  - C++ provides a convenient type (part of <functional>) called [std::reference_wrapper]
    that allows us to pass a normal type as if it was a reference.
  - an [std::reference_wrapper] can be created using the [std::ref()] function.
*/

namespace unintended_copies_of_mutable_lambdas
{
    void main__()
    {
        int i{ 0 };

        auto count{ [i]() mutable {
            std::cout << ++i << '\n';
        } };

        // std::ref(count) ensures count is treated like a reference
        // thus, anything that tries to copy count will actually copy the reference
        // ensuring that only one count exists
        myInvoke(std::ref(count));      // prints: 1
        myInvoke(std::ref(count));      // prints: 2
        myInvoke(std::ref(count));      // prints: 3
    }
}


// [ rule ]
/*---------------------------------------------------------------------------------------
    standard library functions may copy function objects. if you want to provide lambdas
    with mutable captured variables, pass them by reference using [std::ref()].
---------------------------------------------------------------------------------------*/


// [ best practice ]
/*---------------------------------------------------------------------------------------
    try to avoid mutable lambdas. non-mutable lambdas are easier to understand and don't
    suffer from the above issues, as well as more dangerous issued that arise when you
    add parallel execution.
---------------------------------------------------------------------------------------*/




//=======================================================================================

#include <cmath>
#include <ctime>
#include <random>

namespace quiz_1
{
    constexpr int g_maxNearestDelta{ 4 };

    int getRandomInt(int min, int max)
    {
        static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
        return std::uniform_int_distribution{ min, max }(mt);
    }

    void main()
    {
        std::cout << "Start where? ";
        int start{};
        std::cin >> start;

        std::cout << "How many? ";
        int howMany{};
        std::cin >> howMany;

        int multiplier{ getRandomInt(2, 4) };

        std::vector<int> numbers(howMany);
        std::for_each(numbers.begin(), numbers.end(),
                        [&](int& a) {
                            a = multiplier * start*start;
                            ++start;
                        } );
        
        std::cout << "I generated " << howMany << " square numbers.\n"
                  << "Do you know what each number is after multiplying it by " << multiplier << "?\n";
        
        for (int i{ 0 }; i < howMany; ++i)
        {
            std::cout << "> ";      // prompt
            int guess{};
            std::cin >> guess;

            auto found{ std::ranges::find(numbers, guess) };
            if (found != numbers.end())
            {
                numbers.erase(found);

                if (numbers.size() != 0)
                    std::cout << "Nice! " << numbers.size() << " number(s) left.\n";
                else
                {
                    std::cout << "Nice! you found all numbers, good job!\n";
                    break;
                }
            }
            else
            {
                std::cout << guess << " is wrong!";

                auto nearest{ std::ranges::min_element(numbers,
                                                        [guess](int a, int b) {
                                                            return (std::abs(a - guess) < std::abs(b - guess));
                                                        }) };
                if (std::abs(guess - *nearest) <= g_maxNearestDelta )
                    std::cout << " Try " << *nearest << " next time.";
                std::cout << '\n';

                break;
            }
        }
    }
}




//=======================================================================================

int main()
{
    // the_capture_clause::main();
    // captures_default_to_const_value::main();
    // mutable_capture::main();
    // capture_by_reference::main();
    // default_captures::main();
    // declaring_new_variable_in_the_captures::main();
    // unintended_copies_of_mutable_lambdas::main();
    // unintended_copies_of_mutable_lambdas::main_();
    // unintended_copies_of_mutable_lambdas::main__();

    quiz_1::main();

    return 0;
}