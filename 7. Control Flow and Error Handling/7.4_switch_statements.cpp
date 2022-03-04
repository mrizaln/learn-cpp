//============[  ]============

// switch statement specialized in testing a variable against a set of different values

#include <iostream>

    void printDigitName(int x)
    {
        switch (x)
        {
        case 1:
            std::cout << "One";
            break;
        case 2:
            std::cout << "Two";
            break;
        case 3:
            std::cout << "Three";
            break;
        default:
            std::cout << "Unknown";
            break;
        }
        std::cout << '\n';
    }

    int main_switch()
    {
        printDigitName(2);

        return 0;
    }

// there is a restriction on switch, that is the condition must evaluate to an integral type

/* best practice
    prefer switch statements over if-else xhains when there is a choice
*/



//============[ switch fallthrough ]============

// when a switch expression matches acase label or optional default label, execution begins
// at the first statement following the matching label.
// execution will continue sequentially until:
    // 1. the end of the switch block is reached
    // 2. break or return
    // 3. something else interrupts the normal flow of the program

    int main_fallthrough()
    {
        switch(2)
        {
        case 1:     // doesn't match
            std::cout << 1 << '\n';     // skipped
        case 2:     // match!
            std::cout << 2 << '\n';     // execution begins here
        case 3:
            std::cout << 3 << '\n';     // this is also executed
        case 4:
            std::cout << 4 << '\n';     // this is also executed
        default:
            std::cout << 5 << '\n';     // this is also executed
        }

        return 0;
    }

// since fallthrough is rarely desired or intentional, many compilers and code analysis
// tools will flag fallthrough as a warning.



//============[ the [[fallthrough]] attribute ]===========

// attributes are a modern C++ feature that allows the programmer to provide the compiler
// with some additional data about the code.
// to specify an attribute, the attribute name is placed between double hard braces.
// attributes are not statements -- rather, they can be used almost anywhere where they are
// contextually relevant

// the [[fallthrough]] attribute modifies a null statement to indicate that fallthrough is
// intentional (and no warning should be triggered)

    int main_intentional_fallthrough()
    {
        switch(2)
        {
        case 1:
            std::cout << 1 << '\n';
            break;
        case 2:
            std::cout << 2 << '\n';     // execution begins here
            [[fallthrough]];            // intentiional fallthrough -- note the semicolon to indicate the null statement
        case 3:
            std::cout << 3 << '\n';     // this is also executed
            break;
        }

        return 0;
    }

/* best practice
    use the [[fallthrough]] attribute (along with a null statement) to indicate intentional
    fallthrough
*/



//============[ sequential case labels ]============

// you can use the logical OR operator to combine multiple tests into a single statement
// you can do something similar using switch statements

    bool isVowel(char c)
    {
        switch (c)
        {
            case 'a':   // if c is 'a'
            case 'e':   // or if c is 'e'
            case 'i':   // or if c is 'i'
            case 'o':   // or if c is 'o'
            case 'u':   // or if c is 'u'
            case 'A':   // or if c is 'A'
            case 'E':   // or if c is 'E'
            case 'I':   // or if c is 'I'
            case 'O':   // or if c is 'O'
            case 'U':   // or if c is 'U'
                return true;
            default:
                return false;
        }
    }



//============[ switch case scoping ]============

// the statements after labels are all scoped to the switch block

    void switch_scope()
    {
        switch (1)
        {
            case 1:         // does not create an implicit block
                std::cout << "foo";     // this is part of the switch scope not an implicit block to cese 1
                break;                  // this is part of the switch scope not an implicit block to cese 1
            default:
                std::cout << "default case";
                break;
        }
    }



//============[ variable declaration and initialization inside case statements ]============

// you can declare (but not initialize) variables inside the switch, both before and after
// the case labels.

    void switch_variable_declaration()
    {
        switch (1)
        {
            int a;          // okay: declaratoin is allowed before the case label
            // int b { 5 };    // illegal: initialization is not allowd before the case label

            case 1:
                int y;      // okay but bad practice: declaration is allowd within a case
                y = 4;      // okay: assignment is allowed
                break;
            case 2:
                // int z { 4 };    // illegal: initialization is not allowd if subsequent cases exist
                y = 5;          // okay: y was declared above, so we can use it here too
                break;
            case 3:
                break;
        }
    }

// if a case needs to define and/or initialize a new variable, best practice is to do so
// inside an explicit block underneath the case statement.

    void switch_variable_need_initialization()
    {
        switch (1)
            case 1:
            {   // note addition of explicit block here
                int x { 4 };    // okay, variables can be initialized inside a block inside a case
                std::cout << x;
                break;
            }
            default:
                std::cout << "default case\n";
                break;
    }



//=======================================================================================

int main()
{
    main_switch();
    main_fallthrough();
    main_intentional_fallthrough();

    return 0;
}