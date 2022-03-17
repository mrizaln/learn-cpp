#include <iostream>

//============[ typedefs and type aliases ]============

// in C++, [using] is a keyword that create an alias for an exesting data type.

    int main_using_an_alias()
    {
        using distance_t = double;      // define distance_t as an alias for type double

        // many type alias names use a "_t" or "_type" suffic to help decrease the chance
        // of naming collisions with other identifiers.

        distance_t kilometersToDestination { 3.4 };
        
        std::cout << kilometersToDestination << '\n';

        return 0;
    }




//============[ type aliases are not new types ]============

// an alias does not actually define a new type -- it just introduce a new identifier for
// an existing type.
// an alias is completely interchangable with the aliased type.

    int main_interchangable()
    {
        using kilometers_t = long;
        using speed_t = long;

        kilometers_t distance { 5 };
        speed_t mhz { 3200 };

        // the following is sytactically valid (but semantically meaningless)
        distance = mhz;

        return 0;
    }

// when such semantic error happens, the compiler will not complain.
// because the compiler does not prevent these kinds of semantic errors for type aliases,
// we say that aliases are not [type safe].
// in spite of that, they still useful.

// [ warning ]
/*---------------------------------------------------------------------------------------
    care must be taken not to mix values of aliases that are intended to be semantically
    distinct.
---------------------------------------------------------------------------------------*/




//============[ the scope of type alias ]============

// because scope is a property of an identifier, type alias identifers follow the same scoping
// as variable identifier.
// a type alias defined inside a block has block scope and is usable only within that block.
// whereas a type alias defined in the global namespace has file scope and is usable to the
// end of the file.

// if you need to use one or more type aliases accross multiple files, they can be defined
// in a header file and #included into any code files that need is

    // [ mytypes.h ]
    //-----------------------------------------------------------------------------------
        #ifndef MYTYPES
        #define MYTYPES

            using kilometers_t = long;
            using speed_t = long;
        
        #endif
    //-----------------------------------------------------------------------------------




//============[ typedef ]============

// [typedef] (type definition) is a keyword with the same semantics as [using], but reverse
// syntax

    int main_typedef()
    {
        // the following aliases are identical
        typedef long kilometers_t;
        using kilometers_t = long;

    // the syntax for typedefs can get ugly with more complex types:
        typedef int (*fcn_t)(double, char);     // fcn_t hard to find
        using fcn_t = int(*)(double, char);     // fcn_t easier to find

        return 0;
    }

// typedef are still in C++ for historical reasons, but their use is discouraged

// [ best practice ]
/*---------------------------------------------------------------------------------------
    when creating alias types, prefer the type alias syntax over the typedef syntax
---------------------------------------------------------------------------------------*/




//============[ using type aliases for platform independent coding ]============

// one of the uses for type aliases is that they can be used to hide platforms specific details.
// on some platforms, an [int] is 2 bytes, and on others, it is 4 bytes.
// thus, using [int] to store more than 2 bytes of information can be potentially dangerous
// when writing platform independent code.

// becasue [char], [short], [int], and [long] give no indication of their size, it is fairly
// common for cross-platform programs to use type aliases to define aliases that include the
// type's size in bits.

// in order to make sure each aliased type resolves to a type of the right size, type aliases
// of this kind are typically used in conjunction with preprocessor directives:

    #ifdef INT_2_BYTES
        using int8_t = char;
        using int16_t = int;
        using int32_t = long;
    #elif INT_4_BYTES
        using int8_t = char;
        using int16_t = short;
        using int32_t = int;
    #endif

// on machines where integers are only 2 bytes, [INT_2_BYTES] can be [#defined], and the
// program will be compiled with the top set of type aliases.

// the fixed-width integers (such as [std::int_fast16_t] and [std::int_least32_t]) and
// [size_t] type are actually just type aliases to various fundamental types.

// this is also why when you print an 8-bit fixed-width integer using [std::cout], you'll
// likely to get a character value:

    int main_8_bit_fixed_length()
    {
        std::int_least8_t x { 97 };     // typedef signed char int_least8_t
        std::cout << x << '\n';

        return 0;
    }




//============[ using type aliases to make complex types simple ]============

// in advanced C++, types can be complicated and lengthy to manually enter on your keyboard.
// for example:

    #include <string>   // for std::string
    #include <vector>   // for std::vector
    #include <utility>  // for std::pair

    using pairlist_t = std::vector<std::pair<std::string, int>>;      // make pairlist_t an alias for this crazy type

    bool hasDuplicate(pairlist_t pairlist)      // use pairlist_t in a function paramater
    {
        // some code here
        return false;
    }

    int main_pairlist()
    {
        pairlist_t pairlist;        // instantiate a pairlist_t variable

        return 0;
    }




//============[ using type aliases for legibility ]============

// type aliases can also help with code documentation and comprehension
// for example:

    // given a following function
    int gradeTest();
    
    // what does this mean by returning an int type, is it returning student ID number? an
    // error code? idk.

    // now let's do an equivalent using a type alias:
    using testScore_t = int;
    testScore_t gradeTest();

    // the return type of testScore_t makes it a little more obvious what the function returning

// creating a type alias just to document the return type of single function isn't worth it.
// but if you have already created a type alias for other reasons, this can be a nice additional
// benefit.




//============[ using type aliases for easier code maintenance ]============

// type aliases also allow you to change the underlying type of an objet without having to
// change lots of code.

// while this seems like a nice benefit, caution is necessary whenever a type is changed,
// as the behaviour of the program may also change.




//============[ downsides and conclusion ]============

// while type aliases offer some benefits, they also introduce yet another identifier into
// your code that needs to be understood.
// if this isn't offset by some benefit to readability or comprehension, then the type alias
// is doing more harm than good.

// type aliases should be used primarily is cases where ther is a clear benefit to code readability
// or code maintenace.
// this is as much of an art as a science.
// type aliases are most useful when they can be used in many places throughout your code,
// rather than in fewer places

// [ best practice ]
/*---------------------------------------------------------------------------------------
    use type aliases judiciously, when they provide a clear benefit to code readability
    and code maintenance
---------------------------------------------------------------------------------------*/




//=======================================================================================
int main()
{
    main_using_an_alias();
    main_8_bit_fixed_length();

    return 0;
}