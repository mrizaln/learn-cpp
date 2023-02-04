// [exception specifications] are a language mechanism that was originally designed
// to document what kind of exceptions a function might throw as part of a function
// specification

/*------------------------------------------------------------------------------
              ============[ the noexcept specifier ]============
------------------------------------------------------------------------------*/

/*
  - in C++, all functions are classified as either /non-throwing/ or /potentially
    throwing/.
  - a [non-throwing function] is one that promises not to throw exceptions that
    are visible to the caller.
  - a [potentially throwing function] may throw exceptions that are visible to the
    caller.

  - to define a functino as non-throwing, we can use the [noexcept specifier]
  - to do se, we use the [noexcept] keyword in the function declarationo

  - note that [noexcept] doesn't actually prevent the function from throwing exceptions
    or calling other functions that are potentially thrwing.
  - this is allowed so long as the noexcept function catches and handles those
    exceptions internally, and those exceptions do not exit the noexcept

  - if a noexcept funcion throws an exception that would exit the function, [std::terminate]
    will be called

  - the noexcept specifier has an optional boolean parameter
  - noexcept(true) is equivalent to noexcept
  - these parameters are typically only used in template functions, so that a
    template function can be dynamically created as non-throwing or potentially
    throwing
*/




/*------------------------------------------------------------------------------
=======[ illustrating the behavior of noexcept functions and exceptions ]=======
------------------------------------------------------------------------------*/

#include <ios>
#include <iostream>
#include <stdexcept>

namespace noexcept_specifier
{
    class Doomed
    {
    public:
        ~Doomed()
        {
            std::cout << "Doomed destructed\n";
        }
    };

    void thrower()
    {
        std::cout << "Throwing exception\n";
        throw 1;
    }

    void pt()
    {
        std::cout << "pt (potentially throwing) called\n";
        // This object will be destroyed during stack unwinding (if it occurs)
        Doomed doomed{};
        thrower();
        std::cout << "this never prints\n";
    }

    void nt() noexcept
    {
        std::cout << "nt (noexcept) called\n";
        // This object will be destroyed during stack unwinding (if it occurs)
        Doomed doomed{};
        thrower();
        std::cout << "This never prints\n";
    }

    void tester(int c) noexcept
    {
        std::cout << "tester (noexcept) case " << c << " called\n";
        try {
            (c == 1) ? pt() : nt();
        } catch (...)
        {
            std::cout << "tester caught exception\n";
        }
    }

    void main()
    {
        std::cout << std::unitbuf;      // flush buffer after each insertion
        std::cout << std::boolalpha;    // print boolean as true/false
        tester(1);
        std::cout << "Test successful\n\n";
        tester(2);
        std::cout << "Test successful\n";
    }
}




/*------------------------------------------------------------------------------
==========[ which functions are non-throwing and potentially throwing ]=========
------------------------------------------------------------------------------*/

/*
  - functions that are implicitly non-throwing:
      1. destructors

  - functions that are non-throwing by default for implicitly-declared or defaulted
    functions:
      1. constructors: default, copy, move
      2. assignments : copy, move
      3. comparison operators (as of C++20)

  - functions that are potentially throwing (if not implicitly-declared or defaulted)
      1. normal functions
      2. user-defined constructors
      3. user-defined operators
*/




/*------------------------------------------------------------------------------
                ============[ the noexcept operator ]============
------------------------------------------------------------------------------*/

// the noexcept operator can also be used inside functions.
// it takes an expression as an argument, and returns [true] or [false] if the
// compiler thinks it will throw an exception or not.
// the noexcept operator is checked statically at compile-time, and doesn't actually
// evaluate the input expression.

namespace noexcept_operator
{
    void foo() {throw -1;}
    void boo() {};
    void goo() noexcept {};
    struct S{};

    void main()
    {
        constexpr bool b1{ noexcept(5 + 3) }; // true; ints are non-throwing
        constexpr bool b2{ noexcept(foo()) }; // false; foo() throws an exception
        constexpr bool b3{ noexcept(boo()) }; // false; boo() is implicitly noexcept(false)
        constexpr bool b4{ noexcept(goo()) }; // true; goo() is explicitly noexcept(true)
        constexpr bool b5{ noexcept(S{}) };   // true; a struct's default constructor is noexcept by default
    }
}

// the noexcept operator can be used to conditionally execute code depending on
// whether it is potentially throwing or not.




/*------------------------------------------------------------------------------
           ============[ exception safety guarantees ]============
------------------------------------------------------------------------------*/

/*
  - a [excpetion safety guarantee] is a contractual guideline about how functions
    or classes will behave iin the event an exception occurs.

  - there are four levels of exception safety:
      1. no guarantee       -- class may be left in an unusable state
      2. basic guarantee    -- no memory leaked, the object is usable, program state modified
      3. strong guaranteee  -- no memory leaked, program state will not be changed
      4. no throw / no fail    [info below]

  - no-throw:
    > if a function fails, it won't throw an exception, instead, it will return error
      code or ignore the problem
    > codes that should be no-throw:
        1. destructors and memory deallocation/cleanup functions
        2. functions that higher-lvel no-throw functions need to call

  - no-fail:
    > a function will always succeed in what it tries to do
    > codes that should be no-fail:
        1. move constructors and move assignment (move semantics)
        2. swap functions
        3. clear/erase/reset functions on containers
        4. operations on std::unique_ptr
        5. functions that higher-lvel no-fail functions need to call
*/




/*------------------------------------------------------------------------------
               ============[ when to use noexcept ]============
------------------------------------------------------------------------------*/

/*
  - by default, most functions are potentially throwing, so if your function calls
    other functions, there is a good chance it calls a function that is potentially
    throwing, an thus is potentially throwing too.

  - there are few good reasons to mark functions as non-throwing:
    > non-throwing functions can be safely called from functions that are not
      exception-safe, such as destructors
    > functions that are noexcept can enable the compiler to perform some optimizations
      that would not otherwise be available.
    > there are significant cases where knowing a function is noexcept allows us
      to produce more efficient implementations in our own code.

  - the standard library's policy is to use [noexcept] only on functions that [must
    not] throw or fail.

  - for our code, there are two places that make sense to use [noexcept]:
    > on constructors and overloaded assignment operators that are no-throw
    > on functions for which you want to express a no-throw or no-fail guarantee
*/


// [ best practice ]
/*------------------------------------------------------------------------------
    make constructors and overloaded assignment [noexcept] when you can.
    use [noexcept] on other function to express a no-fail or no-throw guarantee.

    if you are uncertain whether a function should have a no-fail/no-throw
    guarantee, error on the side of caution and do not mark it with [noexcept].
    reversing a decision to use noexcept violates an interface commitment to the
    user about the behavior of the function, and may break existing code.
    making guarantees stronger by later adding noexcept to a function that was
    not originally noexcept is considered safe.
------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------------
    ============[ dynamic exception specifications (deprecated)]============
------------------------------------------------------------------------------*/

// before C++11 and until C++17, dynamic exception specifications were used in place
// of [noexcept]
// the [dynamic exception specifications] syntac uses the [throw] keyword to list
// which exception types a function might directly or indirectly throw.

// int doSomething1() throw();                          // does not throw exceptions
// int doSomething2() throw(std::out_of_range, int*);   // may either throw std::out_of_range or int*
// int doSomething3() throw(...);                       // may throw anything


//==============================================================================

int main()
{
    noexcept_operator::main();
    noexcept_specifier::main();
    return 0;
}
