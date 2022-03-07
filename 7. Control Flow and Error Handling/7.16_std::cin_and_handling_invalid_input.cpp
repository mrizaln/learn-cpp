#include <iostream>
#include <limits>


//============[ std::cin, buffers, and extraction ]============

// when we use operator>> to get user input and put it into a variable, this is called am
// "extraction", the operator>> is accordingly called extraction operator when used in this
// context.

// when the user enters input in response to an extraction operation, that data is placed
// in buffer inside of std::cin.
// a buffer (also called a data buffer) is simplu a piece of memory set aside for storing
// data temporarily while it's moved from one place to another.
// in this case, the biffer is used to hold user input while it's waiting to be extracted
// to variables.

// when the extraction operator is used, the following procedure happens:
    // 1. if there is data already in the input buffer, that data is used for extraction.
    
    // 2. if the input buffer contains no data, the user is asked to input data for extraction
    //    (this is the case most of the time)
    //    when the user hits enter, a '\n' char will be placed in the input buffer.
    
    // 3. operator>> extracts as much data from the input buffer as it can into the variable
    //    (ignoring any leading whitespace characters, such as spaces, tabs, or '\n').

    // 4. any data that can not be extracted is left in the input buffer for the next extraction.

// for example:

    int extract()
    {
        int x{};
        std::cin >> x;

        return x;
    }

// extraction succeeds if at least one character is extracted from the input buffer.
// any unextracted input is left in the input buffer for future extraction

// if the user enters "5a" (using above function), 5 will be extracted, converted to an
// integer, and assigned to variable x. "a\n" will be left in the input vuffer for the next
// extraction.

// extraction fails if the input data does not match the type of the variable being extracted
// to.



//============[ validating input ]============

// there are three basic ways to do input validation:
    // - inline (as the user types)
        // 1. prevent the user from typing invalid input in the first place

    // - post-entry (after the user types)
        // 2. let the user enter whatever they want into a string, then validate whether
        //    the string is correct, and if so, convert the string to the final variable
        //    format.

        // 3. let the user enter whatever they want, let std::cin and operator>> tru to
        //    extract it, and handle the error cases.



//============[ a sample program ]============

// consider the following calculator program that has no error handling

    double getDouble()
    {
        std::cout << "Enter a double value: ";
        double x {};
        std::cin >> x;
        return x;
    }

    char getOperator()
    {
        std::cout << "Enter one of the following: +, -. *, or /: ";
        char op {};
        std::cin >> op;
        return op;
    }

    void printResult(double x, char operation, double y)
    {
        switch (operation)
        {
        case '+':
            std::cout << x << " + " << y << " is " << x + y << '\n';
            break;
        case '-':
            std::cout << x << " - " << y << " is " << x - y << '\n';
            break;
        case '*':
            std::cout << x << " * " << y << " is " << x * y << '\n';
            break;
        case '/':
            std::cout << x << " / " << y << " is " << x / y << '\n';
            break;
        }
    }

    int main_operation()
    {
        double x { getDouble() };
        char operation { getOperator() };
        double y { getDouble() };

        printResult(x, operation, y);

        return 0;
    }



//============[ types of invalid text input ]============

// we can generally separate input text errors into four types:
    // 1. input extraction succeeds but the input is meaningless to the program (e.g entering
    //    'k' as your mathematical operator).

    // 2. input extraction succeeds but the user enters additional input (e.g. entering
    //    '*q hello' as your mathematical operator).

    // 3. input extraction fails (e.g. trying to enter 'q' inti a numeric input).

    // 4. input extraction succeeds but the user overflows a numeric value.



//============[ error case 1: extraction succeeds but input is meaningless ]============

// consider following execution of the above program:
/*----------------------------------------------
    Enter a double value: 5
    Enter one of the following: +, -, *, or /: k
    Enter a double value: 7
----------------------------------------------*/

// the user input 'k', and 'k' is a valid character, so it gets extracted.
// but our ptogram wasn't expecting this to happen, so it doesn't properly deal with this
// case.

// the solution is: do input validation.

// this usually consists of 3 steps:
    // 1. check whether the user's input was what you were expeccting.
    // 2. if so, return the value to the caller.
    // 3. if not, tell the user something went wring and have them try again.

    char getOperator_v2()
    {
        while (true)    // loop until user enters a valid input
        {
            std::cout << "Enter one of the following: +, -, *, or /: ";
            char operation{};
            std::cin >> operation;

            // check wheher the user entered meaningful input
            switch (operation)
            {
            case '+':
            case '-':
            case '*':
            case '/':
                return operation;   // return it to the caller
            default:    // otherwise tell the user what went wrong
                std::cerr << "Oops, that input is invalid, Please try again.\n";
            }
        } // and try again
    }



//============[ error case 2: extraction succeeds but with extraneous input ]============

// consider the following execution of the above program:
/*------------------------------
    Enter a double value: 5*7
------------------------------*/

// what happens next:
/*---------------------------------------------------------------------------------
    Enter a double value: 5*7
    Enter one of the following: +, -, *, or /: Enter a double value: 5 * 7 is 35
---------------------------------------------------------------------------------*/

// The program prints the right answer, but the formatting is all messed up. Let’s take a
// closer look at why.

// When the user enters “5*7” as input, that input goes into the buffer. Then operator>>
// extracts the 5 to variable x, leaving “*7\n” in the buffer. Next, the program prints
// “Enter one of the following: +, -, *, or /:”. However, when the extraction operator was
// called, it sees “*7\n” waiting in the buffer to be extracted, so it uses that instead
// of asking the user for more input. Consequently, it extracts the ‘*’ character, leaving
// “7\n” in the buffer.

// After asking the user to enter another double value, the “7” in the buffer gets extracted
// without asking the user. Since the user never had an opportunity to enter additional data
// and hit enter (causing a newline), the output prompts all run together on the same line.

// Fortunately, it’s easy to ignore characters:

    void to_ignore()
    {
        std::cin.ignore(100, '\n');     // clear up to 100 characters out of the buffer, or until a '\n' character is removed
    }

// to ignore all characters up to the next '\n', we can pass
//  std::numeric_limits<std::streamsize>::max() to std::cin.ignore()

// to ignore everything up to and including the next '\n' character we call:

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

// let's update getDouble()

    double getDouble_v2()
    {
        std::cout << "Enter a double value: ";
        double x{};
        std::cin >> x;
        ignoreLine();
        return x;
    }



//============[ error case 3: extraction fails ]============

// consider the following execution of our prgram:
/*----------------------------
    Enter a double value: a
----------------------------*/

// extraction will fails and something like this happens:
/*-----------------------------------------------------------------------------------------------
    Enter a double value: a
    Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
    Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
    Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
    ...
/*---------------------------------------------------------------------------------------------*/
// keeps printing until the program is closed

// When the user enters ‘a’, that character is placed in the buffer. Then operator>> tries
// to extract ‘a’ to variable x, which is of type double. Since ‘a’ can’t be converted to
// a double, operator>> can’t do the extraction. Two things happen at this point: ‘a’ is
// left in the buffer, and std::cin goes into “failure mode”.

// Once in “failure mode”, future requests for input extraction will silently fail. Thus
// in our calculator program, the output prompts still print, but any requests for further
// extraction are ignored. This means that instead waiting for us to enter an operation,
// the input prompt is skipped, and we get stuck in an infinite loop because there is no
// way to reach one of the valid cases.

// Fortunately, we can detect whether an extraction has failed and fix it:

    void extraction_fails()
    {
        if (std::cin.fail())     // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            std::cin.clear();
            ignoreLine();
        }
    }

// let's integrate it to our getDouble() function

    double getDouble_v3()
    {
        while (true)    // loop until user enters a valid input
        {
            std::cout << "Enter a double value: ";
            double x{};
            std::cin >> x;

            if (std::cin.fail())    // has a previous extraction failed?
            {
                // yep, so let's handle the failure
                std::cin.clear();   // put us back in 'normal' operation mode
                ignoreLine();       // and remove the bad input
            }
            else        // else our extraction succeeded
            {
                ignoreLine();
                return x;           // so return the value we extracted
            }
        }
    }



//============[ error case 4: extraction succeeds but the user overflows a numeric value ]============

    int main_overflow()
    {
        std::int16_t x{}; // x is 16 bits, holds from -32768 to 32767
        std::cout << "Enter a number between -32768 and 32767: ";
        std::cin >> x;

        std::int16_t y{}; // y is 16 bits, holds from -32768 to 32767
        std::cout << "Enter another number between -32768 and 32767: ";
        std::cin >> y;

        std::cout << "The sum is: " << x + y << '\n';
        return 0;
    }

// what happens if the user enters anumber that is too large?
/*---------------------------------------------------------------------
    Enter a number between -32768 and 32767: 40000
    Enter another number between -32768 and 32767: The sum is: 32767
---------------------------------------------------------------------*/

// In the above case, std::cin goes immediately into “failure mode”, but also assigns the
// closest in-range value to the variable. Consequently, x is left with the assigned value
// of 32767. Additional inputs are skipped, leaving y with the initialized value of 0. We
// can handle this kind of error in the same way as a failed extraction.



//============[ putting it all together ]============

    #include <iostream>
    #include <limits>

    void ignoreLine_fin()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    double getDouble_fin()
    {
        while (true)    // loop until user enters a valid input
        {
            std::cout << "Enter a double value: ";
            double x{};
            std::cin >> x;

            // check for failed extraction
            if (std::cin.fail())    // has a previous extraction failed?
            {
                // yep, so let's handle the failure
                std::cin.clear();   // put us back in 'normal' operation mode
                ignoreLine_fin();
                std::cerr << "Oops, that input is invalid. Please try again.\n";
            }
            else
            {
                ignoreLine_fin();       // remove any extraneous input
                return x;
            }
        }
    }

    char getOperator_fin()
    {
        while (true)    // loop until user enters a valid input
        {
            std::cout << "Enter one of the following: +, -, *, or /: ";
            char operation{};
            std::cin >> operation;
            ignoreLine_fin();       // remove any extraneous input

            // check whether the user entered meaningful input
            switch (operation)
            {
            case '+':
            case '-':
            case '*':
            case '/':
                return operation;       // return ot to the caller
            default:    // otherwise tell the user what went wrong
                std::cerr << "Oops, that input is invalid. Please try again.\n";
            }
        } // and try again
    }

    void printResult_fin(double x, char operation, double y)
    {
        switch (operation)
        {
        case '+':
            std::cout << x << " + " << y << " is " << x + y << '\n';
            break;
        case '-':
            std::cout << x << " - " << y << " is " << x - y << '\n';
            break;
        case '*':
            std::cout << x << " * " << y << " is " << x * y << '\n';
            break;
        case '/':
            std::cout << x << " / " << y << " is " << x / y << '\n';
            break;
        default:    // we handle unexpexted parameters, even though getOperator_fin() guarantees operation is valid in this particular program
            std::cerr << "Something went wrong; printResult_fin() got an invalid operator.\n";
        }
    }

    int main_operation_fin()
    {
        double x{ getDouble_fin() };
        char operation{ getOperator_fin() };
        double y{ getDouble_fin() };

        printResult_fin(x, operation, y);

        return 0;
    }



//============[ conclusion ]============

// as you write you program, consider how user will misuse your program, espeially around
// tesxt input.
// for each point of text input, consider:
    // > could extraction fail?
    // > could the user enter more input than expected?
    // > could the user enter meaningless input?
    // > coudl the user overflow in input?


//=======================================================================================

int main()
{
    // main_operation();
    main_operation_fin();

    return 0;
}