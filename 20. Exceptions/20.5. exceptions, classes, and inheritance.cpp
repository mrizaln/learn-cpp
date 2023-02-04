/*------------------------------------------------------------------------------
               ============[ when constructors fail ]============
------------------------------------------------------------------------------*/

/*
  - if a constructors must fail for some reason, simply throw an exception to indicate
    the object failed to create.
  - in such a case, the object's contruction is aborted, and all class members are
    destructed as per usual.

  - however, the class desctructor is never called.
  - because the desctructor never executes you can't rely on said desctructor to
    clean up any resources that have already been allocated.

  - taking advantage of the fact that class members are destructed even if the
    constructor fails, if you do the resource allocations inside the members of
    the class, then those members can clean up after themselves when they are
    destructed.

        [for example, using std::unique_ptr instead of raw pointer as member]
*/




/*------------------------------------------------------------------------------
                  ============[ exception classes ]============
------------------------------------------------------------------------------*/

// an exception class is just a normal class that is designed specifically to be
// thrown as an exception.




/*------------------------------------------------------------------------------
             ============[ exceptions and inheritance ]============
------------------------------------------------------------------------------*/

// since it's possible to throw classes as exceptions, and classes can be derived
// from other classes, we need to consider what happend when we use inherited classes
// as exceptions.




/*------------------------------------------------------------------------------
                 ============[ std::exception ]============
------------------------------------------------------------------------------*/

/*
  - std::exception (defined in <exception> header) is a small interface class designed
    to serve as a base class to any exception thrown by the C++ standard library.
  - it has a virtual member function called [what()] that returns descriptive text
    of what happens (in C-style string).
  - as of C++20, there are 28 different exception classes that can be thrown that
    derived from std::exception class.

    [https://en.cppreference.com/w/cpp/error/exception]

  - you can derive your own classes from std::exception and override the virtual
    what() function.
  - std::runtime_error is a populatr choice to be derived on; it has string handling
    capabilities.
*/
