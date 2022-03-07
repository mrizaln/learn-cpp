//============[ break ]============

// the break statement causes a while loop, do-while loop, for loop, or switch statement
// to end, with execution continuing with the next statement after the loop or switch being
// broken out of



//============[ breaking a loop ]============

// break statement can be used to end the loop early.
// execution continues with the next statement after the end of the loop.

// break is also a common way to get out of an intentional infinite loop.

#include <iostream>

    int main_breaking_infinite_loop()
    {
        while (true)
        {
            std::cout << "Enter 0 to exit or any other integer to continue: ";
            int num {};
            std::cin >> num;

            if (num == 0)
                break;
        }

        std::cout << "We're out!\n";

        return 0;
    }



//============[ break vs return ]============

// a break statement terminates the switch or loops, and execution continues at the first
// statement beyond the switch or loop.

// a return statement terminates the entire function that the loop is within, and execution
// continues at point where the function was called.

    int breakOrReturn()
    {
        while (true)
        {
            std::cout << "Enter 'b' to break or 'r' to return: ";
            char ch;
            std::cin >> ch;

            if (ch == 'b')
                break;       // execution will continue at the first statement beyond the loop
            if (ch == 'r')
                return 1;    // return will cause the function to immediately return to the caller
        }

        // breaking the loop causes the execution to resume here
        std::cout << "We broke out of the loop\n";

        return 0;
    }

    int main_breakOrReturn()
    {
        int returnValue { breakOrReturn() };
        std::cout << "Function breakOrReturn returned " << returnValue << '\n';

        return 0;
    }



//==========[ continue ]==========

// the continue statement provie a convenient way to end the current iteration of a loop
// without terminating the entire loop.

    int main_continue_a_loop()
    {
        for (int count{ 0 }; count < 10; ++count)
        {
            // if the number is dvisible by 4, skip this iteration
            if ((count % 4) == 0)
                continue;

            //if the number is not divisible by 5, keep going
            std::cout << count << '\n';

            // the continue statement jumps to here
        }

        return 0;
    }

// be careful when using a continue statement with while or do-while loops.
// if use of a continue statement causes some lines that change the value of variables are
// skipped, then the loop can be infinite

// #define INFINITEE
#ifdef INFINITEE

    int main_while_continue_infinite()
    {
        int count { 0 };
        while (count < 10)
        {
            if (count == 5)
                continue;       // jump to end of loop body
            
            std::cout << count << '\n';
            ++count;    // this statement is never executed after count reaches 5
            
            // the continue statement jumps to here
        }

        return 0;
    }

#endif



//============[ the dbate over use of break and continue ]=============

// many textbooks caution readers not to use break and continue in loops, both because it
// causes the executeon flow to jump around and because it can make the flow of logic harder
// to follow.

// however, used judiciously, break and continue can help make loops more readable by keeping
// the number of nested blocks down and reducing the need for complicated looping logic.

    int main_without_break()
    {
        int count{ 0 }; // count how many times the loop iterates
        bool keepLooping { true }; // controls whether the loop ends or not
        while (keepLooping)
        {
            std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
            char ch{};
            std::cin >> ch;

            if (ch == 'e')
                keepLooping = false;
            else
            {
                ++count;
                std::cout << "We've iterated " << count << " times\n";
            }
        }

        return 0;
    }

// above can be easier to understand using break:

    int main_judicious_use_break()
    {
        int count{ 0 }; // count how many times the loop iterates
        while (true) // loop until user terminates
        {
            std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
            char ch{};
            std::cin >> ch;

            if (ch == 'e')
                break;

            ++count;
            std::cout << "We've iterated " << count << " times\n";
        }

        return 0;
    }

/* best practice
    use break and continue when they simplify your loop logic
*/


//=======================================================================================

int main()
{
    main_breaking_infinite_loop();
    main_breakOrReturn();
    main_continue_a_loop();
#ifdef INFINITEE
    main_while_continue_infinite();
#endif
    main_judicious_use_break();

    return 0;
}