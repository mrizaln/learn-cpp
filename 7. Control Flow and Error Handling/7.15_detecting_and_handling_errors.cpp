//============[  ]============

// most errors in a program occur due to faulty assumptions made by the programmer.

// there are three key places where assumption errors typically occur:
    // 1. when a function returns, the programmer may have assumed the called functions was
    //    successful when it was not.

    // 2. when a program receives input (either from the user, or a file), the programmer
    //    may have assumed the input was in the correct format and semantically valid when
    //    it was not.

    // 3. when a function has been called, the programmer may have assumed the arguments
    //    would be semantically valid when they were not.



//============[ handling errors in functions ]============

// there are 4 general strategies that can be used:
    // - handle the error within the function
    // - pass the error back to the caller to deal with
    // - halt the program
    // - throw an exception



//============[ handling the error within the function ]============

// if the error has occured due to something outside of the program's control, the program
// can retry until success is achieved.
// an alternate strategy is just to ignore the eorr and/or cancel the operation.

#include <iostream>

    void printDivision(int x, int y)
    {
        if (y != 0)
            std::cout << static_cast<double>(x) / y;
    }

// in the above, if the user passed in an invalid value for y (y = 0, div by zero), we just
// ignore the request to print the result of the division operation.

    void printDivision_with_warning(int x, int y)
    {
        if (y != 0)
            std::cout << static_cast<double>(x) / y;
        else
            std::cerr << "Error: Could not divide by zero\n";
    }



//============[ passing errors back to the caller ]============

// in many cases, the error can't reasonably be handled in the function that detects the
// error.

// if the function has a void return type, it can be changed to return a boolean that indicates
// success or failure.

    //instead of printDivision_with_warning() above, we can do something like this

    bool printDivision_bool(int x, int y)
    {
        if (y == 0)
        {
            std::cerr << "Error: could not divide by zero\n";
            return false;
        }

        std::cout << static_cast<double>(x) / y;

        return true;
    }

// if the function returns a normal value, things are a little more complicated.
// in some cases, the full range of return values isn't used.
// in such cases, we can use areturn value that wouldn't otherwise be possible to occur
// normally to indicate an error

    // the reciprocal if x is 1/x, return 0.0 if x = 0
    double reciprocal(double x)
    {
        if (x == 0.0)       // idv by zero
            return 0.0;     // 0 would never be returned by 1/x

        return 1.0 / x;
    }

// however, if the full range of return values are needed, then using the return value to
// indicate an error will not be possible.
// in such a case, an   out parameter  (lesson 9.5) might be a viable choice.



//============[ fatal errors ]============

// if the error is so bad that the program can not continue to operate properly, this is
// called a non-recoverable error (fatal error).
// in such cases, the best thing to do is terminate the program.

// if your code is in main() or a function called directly from main(), the best thing to
// do is let main() return a non-zero status code.

// if you're deep in some nested subfunction, it may not be convenient or possible to propagate
// the error all the way back to main().
// in such case, a halt statement (such as std::exit()) can be used.

    double doDivision(int x, int y)
    {
        if (y == 0)
        {
            std::cerr << "Error: Could not divide by zero\n";
            std::exit(1);
        }
        return static_cast<double>(x) / y;
    }



//============[ exceptions ]============

// because returning an error from a function back to the caller is complicated, C++ offers
// an entirely separate way to pass errors back to the caller: exceptions

// the basic idea is that when an error occurs, an exception is "thrown".
// if the current function does not "catch" the error, the caller of the function has a
// chance to catch the error.
// if the caller does not catch the error, the caller's caller has a chance to catch the
// error.
// the error progressively moves up the call stack until it is either caught and handled or
// until main() fails to handle the error.

// exception handling is in chapter 20



//=======================================================================================
