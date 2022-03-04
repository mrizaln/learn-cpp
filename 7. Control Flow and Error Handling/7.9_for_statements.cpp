//============[  ]============

// the for statement is preferred when we have an obvious loop variable because it lets us
// easily and concisely define, initialize, test, and change the value of loop variables.

// as of C++11, there are two different kinds of for loops: 
    // 1) the classic for statement (current lesson)
    // 2) and range-based for statement (future lesson)

// syntax
    /*
        for (init-statement; condition; end-expression)
            statement;
    */
// above is equivalent to below
    /*
        { // note the block here
            init-statement;         // used to define variables used in the loop
            while (condition)
            {
                statement;
                end-expression;     //used to modify the loop variable prior to reassessment of the condition
            }
        } // variables defined inside the loop go out of scope
    */



//==========[ omitted expression ]============

// it is possible to write for loops that omit any or all of the statements or expressions.

#include <iostream>

    int main_omitted()
    {
        int count { 0 };
        for ( ; count < 10; )   // no init-statement or end-expression
        {
            std::cout << count << ' ';
            ++count;
        }
        std::cout << '\n';

        return 0;
    }



//============[ for loops with multiple counters ]============

// although for loops typically iterate over only one variable, sometimes for loops need to
// work with multiple variables.

    int main_for_multiple_variables()
    {
        for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
            std::cout << x << ' ' << y << '\n';

        return 0;
    }


/* best practice
    defining multiple variables (in the init-statement) and using the comma operator (in
    the and expression) is acceptable inside a for statement.
*/



//============[ nested for loops ]==========

    int main_nested_for()
    {
        for (char c{ 'a' }; c <= 'e'; ++c)      // outer loop on letters
        {
            std::cout << c;     // print out letter first
            
            for (int i{ 0 }; i < 3; i++)        // inner loops on all numbers
                std::cout << i;

            std::cout << '\n';
        }

        return 0;
    }

/* best practice
    prefer for loops over while loops when there is an obvious loop variable
    prefer while loops over for loops when there is no obvious loop variable
*/



//=======================================================================================

int main()
{
    main_omitted();
    main_for_multiple_variables();
    main_nested_for();

    return 0;
}