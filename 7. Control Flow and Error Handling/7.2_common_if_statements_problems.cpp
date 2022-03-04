//============[ quick recap ]============

// if statement takes the form
/*
    if (condition)
        true_statement;
    else
        false_statement;
*/


// to use multiple line of conditional staements, make use of block
/*
    if (condition)
    {
        true_statement_1;
        true_statement_2;
        true_statement_3;
    }
    else
    {
        false_statement_1;
        false_statement_2;
        false_statement_3;
    }
*/

/* best practice
    consider putting single statemnets associated with an  if  or  else  in blocks
*/



//============[ nested if statements and the dangling else problem ]============

#include <iostream>

    int main_dangling_else()
    {
        std::cout << "Enter a number";
        int x {};
        std::cin >> x;

        if (x >= 0)     // outer if statement
            // it is bad coding style to nest if statement this way
            if (x <= 20)
                std::cout << x << " is between 0 and 20\n";

        // which if statement does this else belong to?
        else
            std::cout << x << " is negative\n";

        return 0;
    }

// the above program intruduces a source of potential ambiguity called a dangly else problem
// else statement in the above program matched up with the last unmatched f statement (i.e. the inner)



//============[ flattening nested if statements ]============

    int main_flatten()
    {
        std::cout << "Enter a number: ";
        int x {};
        std::cin >> x;

        if (x < 0)
            std::cout << x << " is negative\n";
        else if (x <= 20)           // only execute if x >= 0
            std::cout << x << " is between 0 and 20\n";
        else                        // only execute if x > 20
            std::cout << x << " greater than 20\n";

        return 0;
    }



//============[ null statements ]============

// a null statements is a statement that consists of just a semicolon
// null statement do nothing

    int main_null_statement()
    {
        std::cout << "Enter a number: ";
        int x {};
        std::cin >> x;

        if (x > 10)
            ;           // this is a null statement

        return 0;
    }

/* warning
    be careful not to "terminate" your if statement with a semicolon. otherwise your
    conditional statement(s) will execute unxonditionally
*/


//=======================================================================================

int main()
{
    // main_dangling_else();
    main_flatten();
    main_null_statement();
}