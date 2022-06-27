#include <iostream>
#include <vector>

/*---------------------------------------------------------------------------------------
                          ============[ classes ]============
---------------------------------------------------------------------------------------*/

/*
  - in the world of object-oriented programming, we often want our types to not only hold
    data, but provide functions that work with the data as well.
  - in C++ this is typically done via the [class] keyword.
  - the [class] keyword defines a new user-defined type called a class.

  - classes are similar to structs.
  - class (and struct) definitiions are like a blueprint -- they describe what the resulting
    object will look like, but they do not actually create the object.

  - by convention, class names should begin with an upper-case letter.
*/




/*---------------------------------------------------------------------------------------
                    ============[ member functions ]============
---------------------------------------------------------------------------------------*/
/*
  - in addition to holding data, classes (and structs) can also contain functions!
  - functions defined inside of a class are called [member functions] (or sometimes [methods]).
  - member functions can be defined inside or outside of the class definition.
*/

namespace class_example
{
    class DateClass
    {
    public:
        int m_year{};
        int m_month{};
        int m_day{};

        void print()
        {
            std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
        }
    };

    void main()
    {
        DateClass today{ 2022, 6, 23 };

        // use member selection operator (.) to select a member variable
        today.m_day = 24;

        // use member selection operator (.) to call a member function
        today.print();
    }
}

/*
  - with member functions, the associated object is essentially implicitly passed to the
    member function.
  - for this reason, it is often called [the implicit object].

  - using the "m_" prefix for member variables helps distinguish member veriables from function
    parameters or local variables inside member functions.
*/




/*---------------------------------------------------------------------------------------
                        ============[ member types ]============
---------------------------------------------------------------------------------------*/

/*
  - in addition to member variables and member functions, classes can have [member types]
    or [nested types] (including type aliases).
*/

namespace class_member_types
{
    class Calculator
    {
    public:
        using number_type = int;        // nested type alias

        std::vector<number_type> m_resultHistory{};

        number_type add(number_type a, number_type b)
        {
            auto result{ a + b };
            m_resultHistory.push_back(result);
            return result;
        }
    };

    void main()
    {
        Calculator calculator;

        std::cout << calculator.add(3, 4) << '\n';      // 7
        std::cout << calculator.add(99, 24) << '\n';    // 123

        for (Calculator::number_type result: calculator.m_resultHistory)
            std::cout << result << '\n';
    }
}

/*
  - type alias members make code easier to maintain and can reduce typing.
  - template classes, which we'll cover later, often make use of type alias members.

  - up to now, we used a "_t" suffix for type aliases.
  - for member type aliases, a "_type" or no suffix at all is more common.
*/




/*---------------------------------------------------------------------------------------
                ============[ a note baout structs in C++ ]============
---------------------------------------------------------------------------------------*/

/*
  - in C, structs only have data members, not member functions.
  - in C++, after designing classes, Bjarne Stroustrup spent some amount of time whether
    structs should be granted the ability to have member functions.
  - upon consideration, he determined that they should, in part to have a unified ruleset
    for both.
  - so although we wrote the above programs using the class keyword, we could have used the
    struct keyword instead.

  - this can lead to a dangerous assumptions.
  - for example, it's fair to assume a xlass will clean up after itself, but it's not safe
    to assume a struct will.
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    use the struct keyword for data-only structures. use the class keyword for objects
    that have both data and functions.
---------------------------------------------------------------------------------------*/




//=======================================================================================

namespace quiz
{
    /*
        create a class called IntPair that holds two integers. this class should have two
        member variables to hold the integers. you should also create two member functions:
        one named "set" that will let you assign values to the integers, and one named
        "print" that will print the values of the variables.
    */

    class IntPair
    {
    public:
        int m_x{};
        int m_y{};

        void set(int x, int y)
        {
            m_x = x;
            m_y = y;
        }

        void print()
        {
            std::cout << "Pair(" << m_x << ", " << m_y << ")\n";
        }
    };

    void main()
    {
        IntPair p1; 
        p1.set(1, 1);

        IntPair p2{ 2, 2 };

        p1.print();
        p2.print();
    }
}


//=======================================================================================

int main()
{
    class_example::main();
    class_member_types::main();
    quiz::main();

    return 0;
}