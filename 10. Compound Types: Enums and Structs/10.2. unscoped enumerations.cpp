// #define ALLOW_ERROR

/*---------------------------------------------------------------------------------------
                       ============[ enumerations ]============
---------------------------------------------------------------------------------------*/

/*
  - an enumeration (an enumerated type or an enum) is a compund data type where every possible
    value is defined as a symbolic constant (called an enumerator).
  - C++ supports two kinds of enumerations: unscoped enumerations and scoped enumerations.
*/




/*---------------------------------------------------------------------------------------
                    ============[ unscoped enumerations ]============
---------------------------------------------------------------------------------------*/

// unscoped enumerations are defined via the [enum] keyword.

// an example: unscoped enumeration that can hold some color values

namespace unscoped_enumerations_example
{
    // define a new unscoped enumeration
    enum Color
    {
        // here are the enumerators
        // these symbolic constants define all the possible values this type xan hold
        // each enumerator is separated by a comma

        red,
        green,
        blue,
    };  // the enum definition must end with a semicolon

    int main()
    {
        Color apple { red };
        Color shirt { green };
        Color cup { blue };

    #ifdef ALLOW_ERROR
        Color socks { white };      // error: white is not an enumerator of Color
        Color hat { 2 };            // error: 2 is not an enumerator of Color
    #endif

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
            ============[ naming enumerations and enumerators ]============
---------------------------------------------------------------------------------------*/

// by convention, the names of enumerated types start with a capital letter.
// names your enumerators starting with a lower case letter




/*---------------------------------------------------------------------------------------
            ============[ enumerated types are distinct types ]============
---------------------------------------------------------------------------------------*/

// each enumerated type you create is considered to be a [distinct type], meaning the compiler
// can distinguish it from other types.

namespace enumerations_distinct_types
{
    enum Pet
    {
        cat,
        dog,
        pig,
        whale,
    };

    enum Color
    {
        black,
        red,
        blue,
    };

    int main()
    {
    #ifdef ALLOW_ERROR
        Pet myPet { black };    // compile error
        Color shirt { pig };    // compile error
    #endif
    }
}




/*---------------------------------------------------------------------------------------
                ============[ putting enumerations to use ]============
---------------------------------------------------------------------------------------*/

// enumerators are useful for enhancing code documentation and readability.
// enumerated types are best used when you have a smallish set of related constants, and objects
// only need to hold one of those values at a time.

namespace enumerations_use
{
    enum DaysOfWeek
    {
        sunday,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday,
        saturday,
    };

    enum CardinalDirections
    {
        north,
        east,
        south,
        west,
    };

    enum CardSuits
    {
        clubs,
        diamonds,
        hearts,
        spades,
    };
}

// sometimes functions will return a status code to the caller to indicate whether the function
// executed successfully or encountered an error.
// we can use enumerations for that.

namespace enumerations_status_code
{
    enum FileReadResult
    {
        readResultSuccess,
        readResultErrorFileOpen,
        readResultErrorFileRead,
        readResultErrorFileParse,
    };

    FileReadResult readFileContents()
    {
    #ifdef ALLOW_ERROR
        if (!openFile())
            return readResultErrorFileOpen;
        if (!readFile())
            return readResultErrorFileRead;
        if (!parseFile())
            return readResultErrorFileParse;
        
        return readResultSuccess;
    #endif
    }

    int main()
    {
        if (readFileContents() == readResultSuccess)
        {
            // do something
        }
        else
        {
            // print error message
        }
    }
}

// enumerated types can also make for useful function parameters when the user needs to make
// a choice between two or more options

namespace enumerations_choice_options
{
    enum SortOrder
    {
        alphabetical,
        alphabeticalReverse,
        numerical,
    };

    void sortData(SortOrder order)
    {
        if (order == alphabetical)
            ; // sort data in forwards alphabetical order
        else if (order == alphabeticalReverse)
            ; // sort data in backwards alphabetial order
        else if (order == numerical)
            ; // sort data numerically
    }
}




/*---------------------------------------------------------------------------------------
            ============[ the scope of unscoped enumerations ]============
---------------------------------------------------------------------------------------*/

// unscoped enumerations are named such because they put their enumerator names into the
// same scope as the enumeration definition itself.

// one consequences of this is that an enumerator name can't be used in multiple enumerations
// within the same scope:

namespace conflicting_enumerators   // pretend this is global namespace
{
    enum Color
    {
        red,
        green,
        blue,   // blue is put into global namespace
    };

    enum Feeling
    {
        happy,
        tired,
        // blue,   // error: naming collision with aboive blue
    };

    int main()
    {
        Color apple { red };
        Feeling me { tired };

        return 0;
    }
}

// unscoped enumerations also provide a named scope region for their enumerators (like namespace).

namespace unscoped_enumerations_named_scope
{
    enum Color
    {
        red,
        green,
        blue,
    };

    int main()
    {
        Color apple { red };                // ok
        Color raspberry { Color::red };     // also ok
    }
}




/*---------------------------------------------------------------------------------------
            ============[ avoiding enumerator naming collisions ]============
---------------------------------------------------------------------------------------*/

// there are quite a few common ways to prevent unscoped enumerator naming collisions.
// one option is to prefix each enumerator with the name of the enumeration itself:

namespace avoid_enumerator_naming_collision_prefix
{
    enum Color
    {
        color_red,
        color_blue,
        color_green,
    };

    enum Feeling
    {
        feeling_happy,
        feeling_tired,
        feeling_blue,       // no longer has a naming collision with color_blue
    };

    int main()
    {
        Color paint { color_blue };
        Feeling me { feeling_blue };
    }
}

// a better option is to put the enumeratoed type inside something that provides a separate
// scope region, such as namespace (or class):

namespace avoid_enumerator_naming_collision_namespace   // pretend this is global namespace
{
    namespace color
    {
        // The names Color, red, blue, and green are defined inside namespace color
        enum Color
        {
            red,
            green,
            blue,
        };
    }

    namespace feeling
    {
        enum Feeling
        {
            happy,
            tired,
            blue, // feeling::blue doesn't collide with color::blue
        };
    }

    int main()
    {
        color::Color paint { color::blue };
        feeling::Feeling me { feeling::blue };

        return 0;
    }
}

// a related option is to use a scoped enumeration




/*---------------------------------------------------------------------------------------
                ============[ comparing against enumerators ]============
---------------------------------------------------------------------------------------*/

// we can use the equality operators to test whether an enumeration has the value of a particular
// enumerator or not.