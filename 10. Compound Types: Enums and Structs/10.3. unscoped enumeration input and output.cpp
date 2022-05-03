#include <iostream>

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

        std::cout << "Your shirt is " << shirt; // what does this do?

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                ============[ printig enumerator names ]=============
---------------------------------------------------------------------------------------*/

// as of C++20, C++ doesn't come with an easy way to do this.
// we'lle have to find a solution ourselves.



//=======================================================================================

int main()
{
    enumerations_implicit_conversion::main();
}