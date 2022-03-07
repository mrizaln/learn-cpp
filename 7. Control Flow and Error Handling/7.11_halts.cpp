//============[  ]============

// a halt is a flow control statement that terminates the program.
// in C++, halts are implemented as functions (rather thatn keywords).



//============[ the std::exit() functions ]============

// std::exit() is a function that causees the program to terminate normally.
// normal terminataion means the program has exited in an expected way.

// std::exit() performs a number of cleanup function.
// first, object with static storage duration are destroyed.
// then some other miscellaneous file cleanup is done if any files were used.
// finally, control is returned back to the OS, with the argument passed to std::exit()
// used as the status code.



//==========[ calling std::exit() explicitly ]============

// although std::exit() is called implicitly when function main() ends, std::exit() can
// also be called explicitly to halt the program before it would normally terminate.
// when std::exit() is called this way, you will need to include the cstdlib header

#include <cstdlib>
#include <iostream>

    void cleanup()
    {
        // code here to do any kind of cleanup required
        std::cout << "cleanup!\n";
    }

    int main_std_exit()
    {
        std::cout << 1 << '\n';
        cleanup();

        std::exit(0);       // terminate and return status code 0 to operating system

        // the following statements nevet execute
        std::cout << 2 << '\n';

        return 0;
    }

// one important note about calling std::exit() explicitly: std::exit() does not clean up
// any local variables (either in the current function, or in functions up the call stack).
// because of this, it's generally better to avoid calling std::exit().

/* warning
    the std::exit() function does not clean up local variables in the current function or
    up the call stack.
*/



//===========[ std::atexit() ]============

// because std::exit() terminates the program immediately, you may want to manyally do some
// cleanup (in the above example, we manually calle function cleanup()) before terminating.
// remember to manyally call a cleanup function before calling every call to exit() adds
// burden to the programmer

// to assist with this, C++ offers the std::atexit() function, which allows you to specify
// a function that will automatically be called on program terminattion via std::exit().

    // the cleanup function has been defined above

    int main_std_atexit()
    {
        // register cleanup() to be called automatically when std::exit() is called
        std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

        std::cout << 1 << '\n';

        std::exit(0); // terminate and return status code 0 to operating system

        // The following statements never execute
        std::cout << 2 << '\n';

        return 0;
    }

// a few notes about st::atexit() and the cleanup function:
    // - because std::exit() is called implicitly when main() terminates, this will invoke
    //   any functions registered by std::atexit() if the program exit that way.
    
    // - the function being registered must take no parameters and have no return value.

    // - you can register multiple cleanup functions using std::atexit() if you want, and
    //   they will be called in reverse order of registration.



//============[ std::abort() and std::terminate() ]============

// the std::abort function causes your program to terminate abnormally.
// abnormal termination means the program had some kind of unusual tuntime error and the
// program couldn't continue to run.
// for example trying to divide by 0 will result in an abnormal termination.

// std::abort() does not do any cleanup

    int main_abort()
    {
        std::cout << 1 << '\n';
        std::abort();

        // the following statements never executes
        std::cout << 2 << '\n';

        return 0;
    }

// the std::terminate() function is typically used in conjunction with exceptions.
// although std::terminate can be called explicitly, it is more often called implicitly when
// an exception isn't handled.
// by default, std::terminate() calls std::abort();



//============[ when should you use a halt? ]============

// the short answer is "almost never".
// destroying local objects is an important part of C++, and none of the above-mentioned
// functions clean up local variables.
// exeptions are a better and safer mechanism for handling error cases.


/* best practice
    only use a halt if there is no safe way to return normally from the main function.
    if you haven't disabled exceptions, prefer using exceptions for handling error safely.
*/


//=======================================================================================

int main()
{
    // main_std_exit();
    main_std_atexit();

    return 0;
}