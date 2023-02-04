/*------------------------------------------------------------------------------
               ============[ function try blocks ]============
------------------------------------------------------------------------------*/

// function try blocks are designed to allow you to establish an exception handler
// around the body of an entire function, rather than around a block of code.

#include <iostream>

class A
{
private:
    int m_x;

public:
    A(int x)
        : m_x{ x }
    {
        if (x <= 0) {
            throw 1;    // Exception thrown here
        }
    }
};

class B : public A
{
public:
    B(int x) try : A{ x }    // note addition of try keyword here
    {
        // if we have exception here, it will be caught by below too
    } catch (...) {    // note this is at same level of indentation as the function itself
                       // Exceptions from member initializer list or constructor body are caught here

        std::cerr << "Exception caught\n";

        throw;    // rethrow the existing exception
    }
};

int main()
{
    try {
        B b{ 0 };
    } catch (int) {
        std::cout << "Oops\n";
    }
}




/*------------------------------------------------------------------------------
         ============[ limitations on function catch blocks ]============
------------------------------------------------------------------------------*/

/*
  - a function-level catch block for a constructor must either throw a new exception
    or rethrowing the existing exception -- they are not allowed to resolve exceptions
  - return statements are also not allowed, and reaching the end of the catch block
    will implicitly rethrow.

  - a function-level catch block for a destructor can throw, rethrow, or resolve
    the current exception via a return statement.
  - reaching the end of the catch block will implicitly rethrow.

| function type       | can resolve?   | behavior at end of catch block |
|---------------------|----------------|--------------------------------|
| constructor         | no             | implicit rethrow               |
| destructor          | yes via return | implicit rethrow               |
| non-value returning | yes via return | resolve exception              |
| value-returning     | yes via return | [undefined behavior]           |
*/
