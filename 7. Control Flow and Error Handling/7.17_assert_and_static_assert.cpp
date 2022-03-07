// #define NDEBUG       // uncomment to disable debug mode (disable assert macro)

#include <iostream>

//============[ preconditions, invariants, and postconditions ]============

// precondition is any condition that must always be true prior to the execution of component
// of code

    void printDivision(int x, int y)
    {
        if (y == 0)
        {
            std::cerr << "Error: Could not divide by zero\n";
            return;
        }

        std::cout << static_cast<double>(x) / y;
    }

// invariant is a condition that must be true while some component is executing

// postcondition is something that must be true after the execution of some component of
// code.




//============[ assertions ]============

// assertion is an expression that will be true unless there is a bug in the program.
// if the expression evaluates to true, it do nothing.
// if it evaluates to false, an error message is displayed and the program is terminated
// (via std::abort)

// in C++, runtime assertions are implemented via the assert preprocessor macro, which
// lives in the <cassert> header

    #include <cassert> // for assert()
    #include <cmath> // for std::sqrt

    double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
    {
        assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity.

        if (initialHeight <= 0.0)
        {
            // The object is already on the ground. Or buried.
            return 0.0;
        }

        return std::sqrt((2.0 * initialHeight) / gravity);
    }

    int main_grav()
    {
        std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";

        return 0;
    }

// when the program calls calculateTimeUntilObjectHitsGround(100.0, -9.8),
// assert(gravity > 0.0) will evaluate to false, which will trigger the assert:
// it will print something like this:

/*---------------------------------------------------------------------------------------------------------------------------------
    dropsimulator: src/main.cpp:6: double calculateTimeUntilObjectHitsGround(double, double): Assertion 'gravity > 0.0' failed.
---------------------------------------------------------------------------------------------------------------------------------*/




//============[ making your assert statements more descriptive ]============

// sometimes assert expression aren't very descriptive, consider following statement:

/*-------------------
    assert(found)
-------------------*/

// if this assert is triggered, the assert will say:

/*---------------------------------------------------------------------
    Assertion failed: found, file C:\\VCProjects\\Test.cpp, line 34
---------------------------------------------------------------------*/

// which is not helpful

// there's a little trick you can use to make your assert statements more descriptive.
// simply add a string literal joined by logical AND.
// string literal vill evaluate to true, so it will not interfere with assert

/*------------------------------------------------------------
    assert(found && "Car could not be found in database");
------------------------------------------------------------*/

// when this triggered:

/*-------------------------------------------------------------------------------------------------------------
    Assertion failed: found && "Car could not be found in database", file C:\\VCProjects\\Test.cpp, line 34
-------------------------------------------------------------------------------------------------------------*/

// which is more descriptive




//============[ asserts vs error handling ]============

// the goal of assertion is to catch programming errors by documenting something that should
// never happen.
// assertions do not allow recovery from errors.

// error handling is designed to gracefully handle cases that could happen in release configurations.
// this may not may not be recoverable.

/* best practice
    use assertions to document cases that should be logically impossible
*/




//============[ NDEBUG ]============

// assert macro comes with a smoll performance cost that is incurred each time assert condition
// is checked.
// asserts can be disabled if NDEBUG is defined.

/*--------------------
    #define NDEBUG
--------------------*/




//============[ some assert limitations and warnings ]============

// 1. the assert itself can have a bug
// 2. your asserts should have no side effects
// 3. also note that the abort() function terminates the program immediately, without a chance
//    to do any further cleanup




//==========[ static_assert ]==========

// a static_assert is an assertion that is checked at compile-time rather that at runtime,
// with failing static_assert causing a comile error.
// unlike assert, which is declared in the <cassert> header, static_assert is a keyword,
// so no header needs to be included to use it.

/*--------------------------------------------------
    static_assert(condition, diagnostic_message)
--------------------------------------------------*/

// if the condition is not true, the diagnostic message is printed.
// here's an example

    static_assert(sizeof(long) == 8, "long must be 8 bytes");
    static_assert(sizeof(int) == 4, "int must be 4 bytes");

    int main_idk()
    {
        return 0;
    }

// because static_assert is evaluated by the compiler, the condition must be able to be
// evaluated at compile time.


//=======================================================================================

int main()
{
    main_grav();
    main_idk();

    return 0;
}