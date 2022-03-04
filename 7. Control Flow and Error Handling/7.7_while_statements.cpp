//============[ loops ]============

// loops are control flow construct that allow a piece of code to execute repeatedly until
// some condition is met.



//============[ while statement ]============

// the while statement is the simplest of the three loop types that C++ provides, and it
// has a definition similar to that of an if statement

#include <iostream>

    int main_while_example()
    {
        int count { 1 };
        while (count <= 10)
        {
            std::cout << count << ' ';
            ++count;
        }
        std::cout << "done!" << '\n';

        return 0;
    }



//============[ intentional inifinite loops ]===========

    int main_infinite_loop()
    {
        while (true)
        {
            std::cout << "loop again (y/n)? ";
            char c {};
            std::cin >> c;

            if (c == 'n')
                return 0;
        }

        return 0;
    }



//============[ loop variables should be signed ]============

// loop variables is an integer that is used o count how many times a loop has executed
// loop variables should almost always be signed, as unsigned integers can lead to unexpected
// issues.

// #define INFINITE
#ifdef INFINITE

    int main_infinityyyy()
    {
        unsigned int count { 10 };

        // count from 10 down to 0
        while (count >= 0) 
        {
            if (count == 0)
            {
                std::cout << "blastoff!";
            }
            else
            {
                std::cout << count << ' ';
            }
            --count;
        }  

        return 0;
    }

#endif

// above loop will be infinite, because when count reach zero then decremented, it will
// wrap around to int_size^2 - 1

/* best practice
    loop variables should be of type (signed) int
*/



//============[ doing something every N iteration ]============

// we can use modulus operator (%) to do that!

    int main_do_something_every_n()
    {
        int count { 1 };
        while (count <= 50)
        {
            // pad the number under 10 with a leading 0 for formatting purposes
            if (count < 10)
            {
                std::cout << '0';
            }

            std::cout << count << ' ';

            // if the loop variable is divisible by 10, print a newline
            if (count % 10 == 0)
            {
                std::cout << '\n';
            }

            // increment the loop counter
            ++count;
        }

        return 0;
    }



//============[ nested loops ]============

    int main_nested()
    {
        int outer { 1 };
        while (outer <= 5)
        {
            int inner { 1 };
            while (inner <= outer)
            {
                std::cout << inner << ' ';
                ++inner;
            }

            std::cout << '\n';
            ++outer;
        }

        return 0;
    }



//=======================================================================================

int main()
{
    main_while_example();
    main_infinite_loop();
#ifdef INFINITE
    main_infinityyyy();
#endif
    main_do_something_every_n();
    main_nested();

    return 0;
}