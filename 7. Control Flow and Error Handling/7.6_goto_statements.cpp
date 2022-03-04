//============[  ]============

// the next kind of control flow statements is unconditional jump
// in C++ unconditional jumps are implemented via the goto statement and the spot to jump
// to is identified through use of a statement label

#include <iostream>
#include <cmath>        // for math functions

    int main_goto()
    {
        double x {};
        
    tryAgain:   // this is a statement label
        std::cout << "Enter a non-negative number: ";
        std::cin >> x;

        if (x < 0.0)
            goto tryAgain;  // this is a goto statement

        std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
        return 0;
    }



//============[ statement labels have function scope ]============

// function scope means the label is visible throughout the function even before the
// function even before its point of declaration.
// the goto statement and its correspoding statement label must appear in the same function

    void printCats(bool skip)
    {
        if (skip)
            goto end;     // jump forward; statement label end is visible here due to it having function scope

        std::cout << "cats";

    end:
        ;   // statement labels must be assosciated with a statement
    }

    int main_label_scope()
    {
        printCats(true);
        printCats(false);

        return 0;
    }

// you can't jump forward over the initialization of any variable that is still in scope
// at the location being jumped to

//#define ILLEGAL

#ifdef ILLEGAL
    int main_illegal_jump()
    {
        goto skip;      // error: this jump is illegal because
        int x { 5 };    // this initialized variable is still in scope at statement label 'skip'

    skip:
        x += 3;         // what would this even evaluate to if x wasn't initialized?

        return 0;
    }
#endif


/* best practice
    avoid goto statements (unless the alternatives are significantly worse for cede readability)
*/

//=======================================================================================

int main()
{
    main_goto();
    main_label_scope();

    return 0;
}