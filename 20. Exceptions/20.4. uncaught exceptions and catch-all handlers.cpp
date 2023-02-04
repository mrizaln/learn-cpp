/*------------------------------------------------------------------------------
               ============[ uncaught exceptions ]============
------------------------------------------------------------------------------*/

/*
  - when a function throws an exception that it does not handle itself, it is making
    the assumption that a function up the call stack will handle the exception.
  - when no exception handler can be found, [std::terminate()] is called, and the
    application is terminated.
  - in such case, the call stack may or may not be unwound.
*/





/*------------------------------------------------------------------------------
               ============[ catch-all handlers ]============
------------------------------------------------------------------------------*/

// a catch-all handler works just like a normal catch block, except that instead
// of using a specific type to catch it uses the ellipses operator (...) as the
// type to catch

void catch_all()
{
    try {
        // piece of code that may throw exception
    } catch (...) {
        std::cerr << "Abnormal termination\n";
    }
}
