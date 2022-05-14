// #define ALLOW_ERROR_EQUALITY

#include <iostream>
#include <string>
#include <string_view>

/*---------------------------------------------------------------------------------------
                              ============[  ]============
---------------------------------------------------------------------------------------*/

// unscoped enumerations are not type safe, in some cases they will allow you to do things
// that don't make sense:

namespace do_not_make_sense
{
    int main()
    {
        enum Color
        {
            red,
            blue,
        };

        enum Fruit
        {
            banana,
            apple,
        };

        Color color { red };
        Fruit fruit { banana };

        if (color == fruit)     // The compiler will compare color and fruit as integers
            std::cout << "color and fruit are equal\n"; // and find they are equal!
        else
            std::cout << "color and fruit are not equal\n";

        return 0;
    }
}

// because of such challenges, as well as the namespace pollution problem, the C++ designers
// determined that a cleaner solution for enumerations would be of use.




/*---------------------------------------------------------------------------------------
                    ============[ scoped enumerations ]============
---------------------------------------------------------------------------------------*/

// scoped enumerations work similarly to unscoped enumerations.
// they have two primary differences, they are:
//  1. strongly typed  (no implicit conversion to int)
//  2. strongly scoped (the enumerators are only placed into the scope region of the enumeration.)

// to make a scoped enumeration, we use the keywords [enum class].
// the rest of the scoped enumeration definition is the same as an unscoped enumeration definition.

namespace scoped_enumeration_type_definition
{
    enum class Color
    {
        red,
        blue,
    };

    enum class Fruit
    {
        banana,
        apple,
    };

    int main()
    {
        Color color { Color::red };         // red is not directly accessible
        Fruit fruit { Fruit::banana };

    #ifdef ALLOW_ERROR_EQUALITY
        if (color == fruit)     // compile error: the compiler doen't know how to compare different types Color and Fruit
            std::cout << "color and fruit are equal\n";
        else
            std::cout << "color and fruit are not equal\n";
    #endif

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
     ============[ scoped enumerations define their own scope regions ]============
---------------------------------------------------------------------------------------*/

// scoped enumerations place thier enumerators /only/ in the scope region of the enumeration.
// scoped enumerations acl like a namespace for their enumerators.




/*---------------------------------------------------------------------------------------
   ============[ scoped enumerations don't implicitly convert to integers ]===========
---------------------------------------------------------------------------------------*/

// note that you can still compare enumerators from within the same scoped enumerations.

namespace compare_same_scoped_enumeration
{
    enum class Color
    {
        red,
        blue,
    };

    int main()
    {
        Color shirt { Color::red };

        if (shirt == Color::red)
            std::cout << "The shirt is red!\n";
        else if (shirt == Color::blue)
            std::cout << "The shirt is blue!\n";

        return 0;
    }
}

// in the case when you want to treat a scoped enumerator as an integer, you can explicitly
// convert a scoped enumeration to an integer by using a [static_cast] to int.

// conversely, you can also [static_cast] an integer to a scoped enumerator.

// as of C++17, you can initialize a scoped enumeration using an integral value without the
// static_cast.


// [ best pracice]
/*---------------------------------------------------------------------------------------
    favor scoped enumerations over unscoped enumerations unless there's a compelling
    reason to do otherwise.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
   ============[ easing the conversion of scoped enumerators to integers ]============
---------------------------------------------------------------------------------------*/

// scoped enumerations are great, but the lack of implicit conversion to integers can sometimes
// be a pain point.

// a useful hack to do that easily convert it to integer is to overload the unary [operator+]
// top perform the conversion.

namespace easing_scoped_enumerators_to_integer_conversion
{
    enum class Animals
    {
        chicken,    // 0
        dog,        // 1
        cat,        // 2
        elephant,   // 3
        duck,       // 4
        snake,      // 5

        maxAnimals,
    };

    // overload the unary operator+
    constexpr auto operator+(Animals a) noexcept
    {
        return static_cast<std::underlying_type_t<Animals>>(a);
    }

    int main()
    {
        std::cout << +Animals::elephant << '\n';        // convert Animals::elephant to an integer

        return 0;
    }
}




//=======================================================================================

/*----------
    Quiz
----------*/
/*
    Define an enum class named Animal that contains the following animals: pig, chicken,
    goat, cat, dog, duck. Write a function named getAnimalName() that takes an Animal
    parameter and uses a switch statement to return the name for that animal as a
    std::string_view (or std::string if you’re using C++14). Write another function named
    printNumberOfLegs() that uses a switch statement to print the number of legs each
    animal walks on. Make sure both functions have a default case that prints an error
    message. Call printNumberOfLegs() from main() with a cat and a chicken.
*/

namespace quiz
{
    enum class Animal
    {
        pig,
        chicken,
        goat,
        cat,
        dog,
        duck,
    };

    constexpr std::string_view getAnimalName(Animal animal)
    {
        switch (animal)
        {
            case Animal::pig:       return "pig";
            case Animal::chicken:   return "chicken";
            case Animal::goat:      return "goat";
            case Animal::cat:       return "cat";
            case Animal::dog:       return "dog";
            case Animal::duck:      return "duck";
            default:                return "???";
        }
    }

    void printNumberOfLegs(Animal animal)
    {
        std::cout << "A " << getAnimalName(animal) << " has ";
        switch (animal)
        {
            case Animal::pig:
            case Animal::goat:
            case Animal::cat:
            case Animal::dog:
                std::cout << 4;
                break;

            case Animal::chicken:
            case Animal::duck:
                std::cout << 2;
                break;

            default:
                std::cout << "???";     
                break;
        }
        std::cout << " legs\n";
    }

    int main()
    {
        printNumberOfLegs(Animal::cat);
        printNumberOfLegs(Animal::chicken);

        return 0;
    }
}



//=======================================================================================

int main()
{
    do_not_make_sense::main();
    compare_same_scoped_enumeration::main();
    easing_scoped_enumerators_to_integer_conversion::main();

    quiz::main();

    return 0;
}