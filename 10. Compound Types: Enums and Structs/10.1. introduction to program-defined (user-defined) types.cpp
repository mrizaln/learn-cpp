#include <iostream>

/*---------------------------------------------------------------------------------------
        ============[ what are user-defined/program-defined types ]============
---------------------------------------------------------------------------------------*/

/*
  - C++ allows us to create entirely new, custom types for use in our programs.
  - such types are often called [user-defined types] (or program-defined types).
  - C++ has two categories of compound types that allow for this:
        1. enumerated types : unscoped and scoped enumerations
        2. class types      : structs, classes, and unions
*/




/*---------------------------------------------------------------------------------------
              ============[ defining program-defined types ]============
---------------------------------------------------------------------------------------*/

// just type aliases, program-defined types must also be defined before they can be used.
// the definition for a program-defined type is called [type definition].

// example: a Fraction type 

namespace example_defining_struct
{
    // define Fraction type
    struct Fraction
    {
        int numerator {};
        int denominator {};
    };

    // we can use Fraction now
    int main()
    {
        Fraction f { 3, 4 };    // instantiates a Fraction object named f

        return 0;
    }
}

// program-defined type definitions always end in a semicolon.




/*---------------------------------------------------------------------------------------
               ============[ naming program-define types ]============
---------------------------------------------------------------------------------------*/

/*
  - by convention program-defined types are named starting with a capital letter and don't
    use a "_t" suffix.
  - this nomenclature helps differentiate program-defined type names from the type aliases
    (which often uses a "_t" or "_type" suffix) and variable names (which start with a lower
    case letter).
*/




/*---------------------------------------------------------------------------------------
 ============[ using program-defined types throughout a multi-file program ]============
---------------------------------------------------------------------------------------*/

/*
  - every code that uses a program-defined type needs to see the full type definition before
    it is used; a forward declaration is not sufficient.
  - to propagate type definitions into the code files that need them, program-defined types
    are typically defined in header files, and then #included into a ny code file that requires
    that type definition.
  - these header files are typically given the same name as the program-defined type.
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    a program-defined type used in only one code file should be defined in that code file
    as close to the first point of use as possible.

    a program-defined type used in multiple code files should be defined in a header file
    with the same name as the program-defined type and then #included into each code file
    as needed
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
  ============[ Type definitions are exempt from the one-definition rule ]============
---------------------------------------------------------------------------------------*/

/*
  - we have discussed how the one-definition rule required us to define functions (and variables)
    in code files (not headers), and propagate only the forward declarations via header files.

  - If type definitions were subject to the same limitations, we would only be able to propagate
    forward declarations for types, not the full type definitions.
  - This isn’t sufficient for us to be able to use those type definitions (since the compiler
    needs to see the full type definition).

  - Consequently, types have been exempted from the one-definition rule, so that full type
    definitions can be propagated to multiple files, even if that results in a duplicate definition.

  - All type definitions for a given type must be identical, otherwise undefined behavior
    will result.
*/




/*---------------------------------------------------------------------------------------
  ============[ Nomenclature: user-defined types vs program-defined types ]============
---------------------------------------------------------------------------------------*/

/*
  - The term user-defined type sometimes comes up in casual conversation, as well as being
    mentioned (but not defined) in the C++ language standard.
  - In casual conversation, the term tends to mean “a type that you defined yourself” (such
    as the Fraction type example above).
  - Sometimes this also includes type aliases.

  - However, as used in the C++ language standard, a user-defined type is intended to be any
    type not defined as part of the core C++ language.
  - This means that types defined in the C++ standard library (such as std::string) are technically
    considered to be user-defined types.

  - Because of mismatch in casual vs technical meaning, we’ll prefer the term program-defined
    type when talking about types that are defined by a programmer for use in their own programs.
*/