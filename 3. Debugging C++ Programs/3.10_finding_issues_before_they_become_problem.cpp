// Don't make errors
    // 1. follow best practces
    // 2. don't program when tired
    // 3. understand where the common potfalls are in a language
    // 4. keep your programs simple
    // 5. don't let your funtions get too long
    // 6. prefer using the standard library to writing your own code, when possible
    // 7. comment your code liberally

// Refactoring functions
    // when making changes to your code, make behavioral changes OR structural changes
    // an then retest for correctness

// An introduction to defensive programming
    // errors can be not only of your own making, but also occur when your users use the
    // appication in a way that you did not anticipate

    // defensive programming is a practice whereby the programmer tries to anticipate all
    // of the ways the software could be misused using the code

// Finding errors fast
    // the best way to do this is to program a little bit a time
    // and then test your code and make sure it works

// An introduction to testing function
    #include <iostream>

    int add(int x, int y)
    {
        return x + y;
    }

    void testadd()
    {
        std::cout << "This function should print: 2 0 0 -2\n";
        std::cout << add(1, 1) << ' ';
        std::cout << add(-1, 1) << ' ';
        std::cout << add(1, -1) << ' ';
        std::cout << add(-1, -1) << ' ';
    }

    int the_main()
    {
        testadd();
        return 0;
    }

    // this is a primitive form of unit testing, which is a software testing method by which
    // small units of source code are tested to determine whether they are correct

// An introduction to constraints
    // constraints-based techniques involve the addition of some etra code to check that some
    // set of assumptions or expectations are not violated

// Shotgunning for general issues
    // programmers tend to make certain kinds of common mistakes, and some of those mistakes
    // can be discovered by programs trained to look for them.
    // these programs, generally known as   static analysis tools   (informal: linters) are
    // programs that analyze your code to identify specific semantic issues