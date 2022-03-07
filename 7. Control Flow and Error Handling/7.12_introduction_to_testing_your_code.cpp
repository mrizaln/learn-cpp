//============[ test your program in small pieces ]============

// you're much better off writing small functions (or classes), and then compiling and testing
// them immediately.
// that way, if you make a mistake, you'll know it has to be in the small amount of code
// that you changed since the last time you compiled/tested.

// testing a small part of your code in isolation to ensure that "unit" of code is correct
// is called  unit testing  .
// each unit test is designed to ensure that a particular behaviour of the unit is correct

/* best practice
    write your program in small, well defined unites (functions or classes), compile often
    and test your code as you go.
*/



//============[ informal testing ]============

// one way you can test code is to do informal testing as you write the program.
// after writing a unit of code, you can write some code to test the unit that was just added,
// and theh erase the test once the test passes.

#include <iostream>

    // we want to test the following function
    bool isLowerVowel(char c)
    {
        switch (c)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
        }
    }

    int main_informal()
    {
        // so here's our temporary tests to validate it works
        std::cout << isLowerVowel('a'); // temporary test code, should produce 1
        std::cout << isLowerVowel('q'); // temporary test code, should produce 0

        return 0;
    }



//============[ preserving your test ]============

// what if you want to test your code again but your previous test code is already deleted?
// make a function to do that.
// if you modify or add new capabilities on your code but don't want to break anything that
// was already working, you can add new test case on your code

    // we want to test the isLowerVowel() function (above)

    void testVowel()
    {
        // you can retest using this
        // or add new test cases also
        std::cout << isLowerVowel('a'); // temporary test code, should produce 1
        std::cout << isLowerVowel('q'); // temporary test code, should produce 0
    }



//============[ automatic your test functions ]============

// one probel with the above test functions is tahta it relies on you to manually verify
// the result when you run it.
// this requires you to remember what the expected answer was at worst, and manually compare
// the actual results to the expected results

// we can do better by writing a test function that contains both the tests AND the expected
// answers and compares them, so we don't have to.

    int testVowel_with_expected()
    {
        if (isLowerVowel('a') != true) return 1;
        if (isLowerVowel('q') != false) return 2;

        return 0;
    }

// now you can call the test function anytime, and the test routine will return an "all good"
// signal (return 0), or the test number that didn't pass.



//============[ unit testing frameworks ]============

// because writing functions to execise other functions is so common and useful, there are
// an entire framework that are designed to help simplify this,



//============[ integration testing ]============

// once each of your units has been tested in isolation, they can be integrated into your
// program and retested to make sure they were integrated properly.
// this is called an integration test



//=======================================================================================
