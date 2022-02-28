//===========[ static local variables ]============

// we know that local variables have  atuomatic duration by default which means they are
// created at the point of definition, and destroyed when the block is exited

// using the   static   keyword on a local variable changes its duration from automatic
// duration to static duration.
// this means the variable now created at the start of the program, and destroyed at the
// end of the program (just like a global variable).
// as a result, the static variable will retain its value even after it goes out of scope!

//---------[ automatic duration ]--------
#include <iostream>

void incrementAndPrint_automatic()
{
    int value { 1 };    // automatic duration by default
    ++value;
    std::cout << value << '\n';
} // value is destroyed here

int main_automatic()
{
    incrementAndPrint_automatic();
    incrementAndPrint_automatic();
    incrementAndPrint_automatic();

    return 0;
}


// --------[ static duration ]--------
void incrementAndPrint_static()
{
    static int s_value { 1 };     // this initializer is only executed once
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

int main_static()
{
    incrementAndPrint_static();
    incrementAndPrint_static();
    incrementAndPrint_static();

    return 0;
}

// just like we use "g_" to prefix global variables, it's common to use "s_to prefix static
// (static duration) local variables.

// one of the most common uses for static duration local variables is for unique ID generators.
int generateID()
{
    static int s_itemID { 0 };
    return s_itemID++;  // makes copy of s_itemID, increments the real s_itemID, then returns the value in th copy
}

// static variables offer some of the benefits of global variables (they don't get destroyed
// until the end of the program) while limiting their visibility to block scope.
// this makes them safer for use even if you change their value regularly.

/* best practive
    initialize your static local variables. static local variables are only initialized the
    first time the code is executed, not on subsequent calls
*/



//============[ static local cinstants ]============

// one good use for a const static local variable is when you have a function that eed to
// use a const value, but creating or initializing the object is expensive (e.g. you need
// to read the value from database).
// if you used a normal local variable, the variable would be created and initialized every
// time the function was executed.
// with a const static local variable, you can create and initialize the expensive object
// once, and then reuse it whenever the function is called




//---------[ don't use static local variables to alter flow ]--------

int getInteger()
{
    static bool s_isFirstCall { true };

    if (s_isFirstCall)
    {
        std::cout << "Enter an integer: ";
        s_isFirstCall = false;
    }
    else
    {
        std::cout << "Enter another integer: ";
    }

    int i{};
    std::cin >> i;
    return i;
}

int main_alter_flow()
{
    int a { getInteger() };
    int b { getInteger() };

    std::cout << a << " + " << b << " = " << (a + b) << '\n';

    return 0;
}

// static local variables should only be used if in your entire program and in the forseeable
// future of your program, the variable is unique and it wouldn't make sense to reset the
// variable

/* best practice
    avoid static local variables unless the variable never needs to be reset
*/


//=======================================================================================


int main()
{
    // main_automatic();
    // std::cout << '\n';
    // main_static();
    // std::cout << '\n';

    main_alter_flow();
}