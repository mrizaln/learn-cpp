/*------------------------------------------------------------------------------
               ============[ cleaning up resources ]============
------------------------------------------------------------------------------*/

// one of the biggest problems that new programmers run into when using exceptions
// is the issue of cleaning up resources when an exception occurs

// one way to solve this is to use a local variable that knows how to cleanup
// itself when it goes out of scope (smart pointer)




/*------------------------------------------------------------------------------
            =============[ exceptions and destructors ]============
------------------------------------------------------------------------------*/

// unlike in constructors, exceptions should never be thrown in destructors
// the best course of action is just write a message to a log file instead


// [ rule ]
/*------------------------------------------------------------------------------
    destructors should not thrown exceptions
------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------------
               ============[ performance concerns ]============
------------------------------------------------------------------------------*/

// exceptions do come with a small performance price to pay
// the main performance penalty happens when an exception is thrown




/*------------------------------------------------------------------------------
          ============[ so when should i use exceptions? ]============
------------------------------------------------------------------------------*/

/*
  - exception handling is best used when all of the following are true:
    1. the error being handled is likely to occur only infrequently
    2. the error is serious and execution could not continue otherwise
    3. the error cannot be handled at the place where it occurs
    4. there isn't a good alternative way to return an error code back to the caller
*/
