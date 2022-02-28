// a compound statements (also called a block or block statement is a group of zero or more
// statements that is treated by the compiler as if it were a single statement

// blocks begin with a   {   , end with a   }   symbol
// blocks can be used anywhere single statement is allowd.
// no semicolon is needed at the end of a block

#include <iostream>

int add(int x, int y)
{   // start block
    return x + y;
}   // end block (no semicolon)

int nested()
{ // outer block
    // multiple statements
    int value {};

    {   // inner/nested block
        add(3,4);
    }   // end inner/nested block

    return 0;
} // end outer block


//========[ using block to execute multiple statements conditionally ]======
// by default   if statements   executes a single statement if the condition evaluates to
// true. however we can replace this single statement with a block statement

int conditional()
{
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;
    
    if (value >= 0)
    { // start of nested bloxk
        std::cout << value << " is a positive integer (or zero)\n"
                              "Double this numner is " << value *2 << '\n';
    } // end of nested block 
    else
    { // start of nested block
        std::cout << value << " is a negative integer (or zero)\n"
                              "The positive of this number is " << -value << '\n';
    } // end of nested block

    return 0;
}


//========[ block nesting levels ]========
// the C++ standard says that C++ compilers should support 256 levels of nesting
// however not all do

int nesting_level()
{ // block 1, nesting level 1
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;

    if (value > 0)
    { // block 2, nesting level 2
        if (value % 2)
        { // block 3, nesting level 3
            std::cout << value << " is a positive and even\n";
        }
        else
        { // block 4, nesting level 3
            std::cout << value << " is a positive and odd\n";
        }
    }

    return 0;
}

/* best practice
    keep the nesting level of your functions to 3 or less.
    if your function has a need for more nested levels, consider refactoring your function
    into sub-function
*/

int main()
{
    conditional();
}
