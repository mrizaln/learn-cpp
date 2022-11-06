#include <iostream>


/*---------------------------------------------------------------------------------------
          ============[ throwing exceptions from a called function ]============
---------------------------------------------------------------------------------------*/

/*
  - one of the most useful properties of exception handling is that the throw statements
    do not have to be placed directly inside a try block.
  - instead, exceptions can be thrown from anywhere in a function, and those exceptions
    can be caught by the try block of the caller (or the caller's caller, etc...).
  - when an exception is caught in this manner, execution jumps from the point where the
    exception in thrown to the catch block handling the exception.
*/

namespace example
{
    void D()    // called by C()
    {
        std::cout << "start D\n";
        std::cout << "D throwing int exception\n";

        throw -1;

        std::cout << "end D\n";     // skipped over
    }

    void C()    // called by B()
    {
        std::cout << "start C\n";
        D();
        std::cout << "end C\n";
    }

    void B()    // called by A()
    {
        std::cout << "start B\n";

        try
        {
            C();
        }
        catch(double)   // not caught: exception type mismatch
        {
            std::cerr << "B caught double exception\n";
        }

        try
        {
        }
        catch(int)      // not caught: exception not thrown within try
        {
            std::cerr << "B caught int exception\n";
        }
        
        std::cout << "end B\n";
    }

    void A()    // called by main()
    {
        std::cout << "start A\n";

        try
        {
            B();
        }
        catch(int)      // exception caught here and handled
        {
            std::cerr << "A caught int exception\n";
        }

        std::cout << "end A\n";
    }

    void main()
    {
        std::cout << "start main\n";

        try
        {
            A();
        }
        catch(int)      // not called because exception was handled by A
        {
            std::cerr << "main caught int exception\n";
        }

        std::cout << "end main\n";
    }
}




//=======================================================================================

int main()
{
    example::main();

    return 0;
}