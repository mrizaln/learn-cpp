//============[ code coverage ]============

// the term code coverage is used to describe how much of the source of a program is executed
// while testing.
// there are many different metrics used for code coverage.



//============[ statement coverage ]============

// the term statement coverage refers to the percentage of statements in your code that have
// been exercised by your testing routine.

    int foo(int x, int y)
    {
        int z{ y };
        if (x > y)
        {
            z = x;
        }
        return z;
    }

// calling this function as foo(1, 0) will give you complete statement coverage for this
// function, as every statement will execute

    bool isLowerVowel(char c)
    {
        switch (c) // statement 1
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true; // statement 2
        default:
            return false; // statement 3
        }
    }

// this function will require two calls to test all of the statements, as there is no way
// to reach statement 2 and 3 in the same function call



//============[ branch coverage ]============

// refers to the percentage of branches that have been executed, each possible branch counted
// separately.

// the previous call to foo(1, 0) gave us 100% statement coverage
// but if the call is foo(0, 1), it gave us 50% coverage

#include <iostream>

    void compare(int x, int y)
    {
        if (x > y)
            std::cout << x << " is greater than " << y << '\n';     // case 1
        else if (x < y)
            std::cout << x << " is less than " << y << '\n';        // case 2
        else
            std::cout << x << " is equal to " << y << '\n';         // case 3
    }

// 3 calls are needed to get 100% branch coverage here

/* best practice
    aim for 100% branch coverage of your code
*/



//============[ loop coverage ]===========

// loop caoverage (0, 1, 2 test) says that if you have a loop in your code, you should
// it works properly when it iterates 0 times, 1 time, and 2 times.
// if it works correctly for the 2-iteration case, it should work correctly for all iterations
// greater than 2.

    void spam(int timesToPrint)
    {
        for (int count { 0 }; count < timesToPrint; ++count)
            std::cout << "Spam!";
    }

// to test the loop within this function properly, you should call it three times: spam(0),
// spam(1), and spam(2).

/* best practice
    use the 0, 1, 2 test to ensure your loops work correctly with different number of iterations
*/



//============[ testing different categories of input ]============

// when writing functions that accept parameters, or when accepting user input, consider
// what happens with different categories of input.

// here are some besic guidelines for category testing:
    // for integers, make sure you've considered how your function handles negative values,
    // zero, and positive values. you should also check for overflow if that's relevant

    // for floating point numbers, make sure you've considered how your function handles
    // values that have precision issues.
    // good double type values to test with are 0.1 and -0.1 (to test numbers that are
    // slightly larger that expected) and 0.6 and -0.6 (to test numbers that are slightly
    // smaller than expected).

    // for string, make sure you've considered how your function handles an empty string
    // (just as null terminator), normal valid strings, strings that have whitespace, and
    // strings that are all whitespace.

    // if your function takes a pointer, don't forget to test nullptr as well.

/* best practice
    test different categories of input value to make sure your unit handles them properly
*/


//=======================================================================================
