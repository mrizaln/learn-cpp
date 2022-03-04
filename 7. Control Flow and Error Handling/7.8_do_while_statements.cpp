//============[  ]============

// what if we want to ask user to make a selection and if the user chooses an invalid
// selection, we ask them again.
// since a while loop evalueates the condition up front, it's an awkward choice.
// we could solve the issue like this:

#include <iostream>

    int main_ask_while()
    {
        // selection must be declared outside while loop so we can use it later

        int selection { 0 };
        while (selection != 1 && selection != 2 && selection != 3 && selection != 4)
        {
            std::cout << "Please make a selection: \n";
            std::cout << "1) Addition\n";
            std::cout << "2) Subtraction\n";
            std::cout << "3) Multiplication\n";
            std::cout << "4) Division\n";
            std::cin >> selection;
        }

        // do something with selection here
        // such as a switch statement

        std::cout << "You selected option #" << selection << '\n';

        return 0;
    }

// this only works because our initial value of 0 for selection isn't in the set of valid
// values (1, 2, 3, 4).
// what if 0 was avalid choice? we'd have to pick a different initializer



//============[ do while statements ]============

// to help solve problems like the above, C++ offers the do-while statement.
// a do while statement is a looping construct that works just like a while loop, except
// the statement always execute at least once.
// after the statement has been excuted, the do-while loop checks the condition.

    int main_do_something_while_ask()
    {
        int selection {};

        do
        {
            std::cout << "Please make a selection\n";
            std::cout << "1) Addition\n";
            std::cout << "2) Subtraction\n";
            std::cout << "3) Multiplication\n";
            std::cout << "4) Division\n";
            std::cin >> selection;
        }
        while (selection != 1 && selection != 2 && selection != 3 && selection != 4);

        // do something with the selction here
        // such as switch statement

        std::cout << "You selected option #" << selection << '\n';

        return 0;
    }

// one thing worth noting is that the selection variable must be declared outside the do block.
// otherwise, it will be destroyed when the do block terminates which happens before the
// conditional is evaluated.


/* best practice
    favor while loops over do-while when given an equal choice
*/


//=======================================================================================

int main()
{
    main_ask_while();
    main_do_something_while_ask();

    return 0;
}