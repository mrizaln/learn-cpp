// A general approach to debugging
    // 1. find the root couse of the problem (usually th line of code that's not working)
    // 2. ensure you understand why the issue is occuring
    // 3. determine how you'll fix the problem
    // 4. repair the issue causing the problem
    // 5. retest to ensure the problem has been fixed and no new problems have emerged

// A strategy for debugging
    // 1. finding problems via code inspection
        // look the code, but if the code is complex it's not easy to inspect the code directly
    // 2. finding problems by running the program
        // a. figure out how to reproduce the problem
        // b. run the program and gather information to narrow down where the problem is
        // c. repeat the prior step until you find the problem

// Basic debugging tactics
    // tactic #1: commenting out your code

    // tactic #2: validating your code flow
        // it is common in more complex programs that the program is calling a function too many
        // or too few times (including not at all)
        // in such cases, it can be helpful to place statements at the top of your funtions to
        // print the function's name

        /* Tip
            when printing information for debugging puposes, use   std::cerr   instead of   std::cout   
            reason:   std::cout   may be buffered
                      std::cerr   not buffered     --->  outputs immediately
        */

    // tactic #3: printing values
        // the program may be calculating or passing the wrong value

        // why using printing statements to debug isn't great
            // 1. debug statements clutter your code
            // 2. debug statements cullter the output of your program
            // 3. debug statements must be removed after you're down with them, which makes them non-reusable
            // 4. debug statements require modification of your code to both add and to remove, which can introduce new bugs

// More debugging tactics
    // 1. conditionalizing your debugging code
        // using the preprocessor directives

        #include <iostream>
        #define ENABLE_DEBUG        // comment to disable debugging

        int getUserInput_0()
        {
        #ifdef ENABLE_DEBUG
        std::cerr << "getUserInput() called\n";
        #endif
            std::cout << "Enter a number: ";
            int x{};
            std::cin >> x;
            return x;
        }

        int main_0()
        {
        #ifdef ENABLE_DEBUG
        std::cerr << "main() called\n";
        #endif
            int x{ getUserInput_0() };
            std::cout << "You entered: " << x;

            return 0;
        }

    // 2. using a logger
        // for example, we're using   plog   logger

        #include <iostream>
        #include <plog/Log.h>   // include the log headers
        #include <plog/Initializers/RollingFileInitializer.h>

        int getUserInput_1()
        {
            PLOGD << "getUserInput() called";
        
            std::cout << "Enter a number: ";
            int x{};
            std::cin >> x;
            return x;
        }

        int main_1()
        {
            plog::init(plog::debug, "logfile.txt");
            // plog::init(plog::none, "logfile.txt");      // essentially turn off the logger

            PLOGD << "main() called";

            int x{ getUserInput_1() };
            std::cout << "You entered: " << x;

            return 0;
        }

        int main()
        {
            main_1();
        }