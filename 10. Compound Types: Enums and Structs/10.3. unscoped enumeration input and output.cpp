#include <iostream>
#include <string>
#include <string_view>      // inexpensive version of std::string

/*---------------------------------------------------------------------------------------
                              ============[  ]============
---------------------------------------------------------------------------------------*/

// this is not mentioned in the las lesson but, enumerators are /integral/ symbolic constants.
// as a result, enumeraated types actually hold an integral value.

// when we define an enumerator, each enumerator is automatically assigned an integer value
// based on its position in the enumerator list.

// by default, the first enumerator is assigned the intagral value 0, and each subsequent 
// enumerator has a value greater than the previous enumerator

namespace unscoped_enumerations_are_integral
{
    enum Color
    {
        black,      // 0
        red,        // 1
        blue,       // 2
        green,      // 3
        white,      // 4
        cyan,       // 5
        yellow,     // 6
        magenta,    // 7
    };

    int main()
    {
        Color shirt { blue };       // this actually stores the integral value 2.

        return 0;
    }
}

// it is possible to explicitly define the value of enumerators.

namespace explicitly_define_the_value_of_enumerators
{
    enum Animal
    {
        cat = -3,
        dog,         // assigned -2
        pig,         // assigned -1
        horse = 5,
        giraffe = 5, // shares same value as horse
        chicken,      // assigned 6
    };
}

// note: in this case, [horse] and [girraffe] are non-distinct, they are interchangable

// [ best practice ]
/*---------------------------------------------------------------------------------------
    avoid assigning explicit value to your enumerators unless you have a compelling
    reasons to do so.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
===========[ unscoped enumerations will implicitly convert to integral values ]==========
---------------------------------------------------------------------------------------*/

namespace enumerations_implicit_conversion
{
    enum Color
    {
        black, // assigned 0
        red, // assigned 1
        blue, // assigned 2
        green, // assigned 3
        white, // assigned 4
        cyan, // assigned 5
        yellow, // assigned 6
        magenta, // assigned 7
    };

    int main()
    {
        Color shirt{ blue };

        std::cout << "Your shirt is " << shirt << '\n'; // what does this do?

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                ============[ printig enumerator names ]=============
---------------------------------------------------------------------------------------*/

// as of C++20, C++ doesn't come with an easy way to do this.
// we'll have to find a solution ourselves.

// the typical way to do this is to test our enumeration against every possible enumerator:

namespace printing_enumerator_names
{
    enum Color
    {
        black,
        red,
        blue,
    };

    std::string getColor(Color color)
    {
        switch (color)
        {
            case black: return "black";
            case red:   return "red";
            case blue:  return "blue";
            default:    return "???";
        }
    }

    // above function is not efficient because we need to create and return std::string (expensive)
    // below function is more efficient (using std::string_view)

    constexpr std::string_view getColor_efficient(Color color)
    {
        switch (color)
        {
            case black: return "black";
            case red:   return "red";
            case blue:  return "blue";
            default:    return "???";
        }
    }

    int main()
    {
        Color shirt { blue };
        std::cout << "Your shirt is " << getColor(shirt) << '\n';
        std::cout << "Your shirt is " << getColor_efficient(shirt) << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
        ============[ teaching std::cout how to print an enumerator ]=============  
---------------------------------------------------------------------------------------*/

// using operator overloading (similar to function overloading), we can actually teach std::cout
// how to print the value of a program-defined enumeration.

namespace teaching_std_cout
{
    enum Color
    {
        black,
        red,
        blue,
    };

    std::ostream& operator<<(std::ostream& out, Color color)
    {
        switch (color)
        {
            case black: out << "black"; break;
            case red:   out << "red";   break;
            case blue:  out << "blue";  break;
            default:    out << "???";   break;
        }

        return out;
    }

    int main()
    {
        Color shirt { blue };
        std::cout << "Your shirt is " << shirt << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                ============[ enumeration size and base ]============
---------------------------------------------------------------------------------------*/

// enumerated types are considered part of the integer family types.
// most often, the compiler will make enum variables the same size as a standard [int]

// however, it is possible to specify a different underlying type.

namespace enumeration_size
{
    enum Color : std::uint8_t
    {
        black,
        red,
        blue,
    };
}




/*---------------------------------------------------------------------------------------
          ============[ integer to unscoped enumerator conversion ]============
---------------------------------------------------------------------------------------*/

// the compiler won't implicitly convert an integer to an unscoped enumerator.

// there are two ways to work around this

namespace integer_to_unscoped_enumerator_conversion
{
    // first, you can force the conversion using [static_cast]
    enum Pet
    {
        cat,
        dog,
        pig,
        whale,
    };

    void force()
    {
        Pet pet { static_cast<Pet>(2) };    // pig
        pet = static_cast<Pet>(3);          // whale
    }

    // second, in C++17, if an unscoped enumeration has a specified base, then the compiler
    // will allow you to initialize an unscoped enumeration using an integral value.
    enum Pett : int
    {
        catt,
        dogg,
        pigg,
        whalee,
    };

    void base_specified()
    {
        Pett pett { 2 };    // ok; initialization
        // pett = 3;           // not ok; assignment
    }
}




/*---------------------------------------------------------------------------------------
                ============[ unscoped enumerator input ]============
---------------------------------------------------------------------------------------*/

// because Pet (for example) is a program-defined type, the languaege doesn't know how to
// input a Pet using [std::cin]

// to work around this, we can read in an integer, and use [static_cast] to convert the integer
// to an appropiate enumerator.



//=======================================================================================

int main()
{
    enumerations_implicit_conversion::main();
    printing_enumerator_names::main();
    teaching_std_cout::main();

    return 0;
}