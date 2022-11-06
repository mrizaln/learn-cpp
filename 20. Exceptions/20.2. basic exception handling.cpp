#include <iostream>


// exceptions in C++ are implemented using three keywords that work in conjunction with
// each other: [throw], [try], and [catch].

/*---------------------------------------------------------------------------------------
                    ============[ throwing exceptions ]============
---------------------------------------------------------------------------------------*/

/*
  - in C++, a [throw statement] is used to signal that an exception or error case has
    occurred.
  - signaling that an exception has occurred is also commonly called [raising] an
    exception

  - to use a throw statement, simply use the throw keyword, followed by a value of any
    data type you wish to use to signal that an error has occurred.
  - typically, this value will be an error code, a description of the problem, or a
    custom exception class.
*/

namespace throw_statement
{
    enum error
    {
        ENUM_INVALID_INDEX
        // etc
    };

    class MyException           // exception class
    {
    public:
        MyException(const std::string&)
        {
            // something
        }
    };

    void someFunction()
    {
        double dX{ 1.457e34 };

        throw -1;                                               // throw literal int
        throw ENUM_INVALID_INDEX;                               // throw an enum
        throw "Can not take square root of negative number";    // throw literal string
        throw dX;                                               // throw a variable
        throw MyException("Fatal Error");                       // throw an object of class MyException
    }
}




/*---------------------------------------------------------------------------------------
                   ============[ looking for exceptions ]============
---------------------------------------------------------------------------------------*/

/*
  - throwing exceptions in only one part of the exception handling process.

  - in C++ we use the [try] keyword to define a block of statements (called a [try block]).
  - the try block acts as an observer, looking for any exceptions that are thrown by any
    of the statements within the try block.
*/

// example after below section




/*---------------------------------------------------------------------------------------
                    ============[ handling exceptions ]============
---------------------------------------------------------------------------------------*/

/*
  - the [catch] keyword is used to define a block of code (called a [catch block]) that
    handles exceptions for a single data type.

  - try blocks and catch blocks work together -- a try block detects any exceptions that
    are thrown by statements within the try block, and routes them to a catch block with
    a matching type for handling.
  - a try block must have at least one catch block immediately following it, but may have
    multiple catch blocks listed in sequence.

  - once an exception has been caught by the try block and routed to a catch block for
    handling, the exception is considered handled, and execution will resume as normal
    after the catch block.

  - catch parameters work just like function parameters, with the parameter being available
    within the subsequent catch block.
  - exceptions of fundamental types can be caught by value, but exceptions of non-fundamental
    types should be caught by const reference to avoid making an unnecessary copy.

  - no type conversion is done for exception.
  - however, casts from a derived class to one of its parent classes will be performed.
*/

namespace try_catch_block
{
    void tryCatch()
    {
        try
        {
            throw_statement::someFunction();
            // statements that may throw exceptions you want to handle go here
        }
        catch (int x)
        {
            // handle an exception of type int here
            std::cerr << "We caught an int exception with value " << x << '\n';
        }
    }
}




//=======================================================================================

int main()
{
    try_catch_block::tryCatch();

    return 0;
}