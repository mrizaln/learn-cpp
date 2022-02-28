//========[ why (non-const) global variables are evil ]========
// by far the biggest reason non-const gloval variables are dangerous is because their
// values can be changed by any function that is called, and there is no easy way for the
// programmer to know that this will happem

#include <iostream>

int g_mode;     // decalre global variable (will be zero-initialized by default)

void doSomething()
{
    g_mode = 2;     // set the global g_mode variable to 2
}

int evil_globals()
{
    g_mode = 1;     // note: this sets the global g_mode variable to 1. it does not declare a local g_mode variable

    doSomething();

    // programmer still expects g_mode to be 1
    // but doSomething() changed it to 2!

    if (g_mode == 1)
        std::cout << "No threat detected.'\n";
    else
        std::cout << "Launching nuclear missiles...\n";

    return 0;
}

// global variables can be accessed anywhere, you might have to look through the entire
// program to understand their usage.
// global varibles also make your program less modular and less flexible.
// in particular, avoid using global variables for important "decision-point" variables.

/* best practice
    use local variable instead of global variables whenever possible
*/



//========[ the initialization order problem of global variables ]========
// initialialization of static variables happens in two phase:
    // 1. static initialization:    global variables with constexpr initializer are initilaized to those values, and zero-initialized (without initializer)
    // 2. dynamic initilization:    this pahes is more complex and nuanced, but the gist of it is that global variables with non-constexpr initializers are initialized

// within a single file, global variables are generally initialized in order of definition
// (there are a few exceptions).
// given this, you need to be careful not to have variables dependent on the initialization
// value of other variables that won't be initialized until later.

// For example:
int initx();    // forward declaration
int inity();    // forward declaration

int g_x { initx() };    // g_x is initialized first
int g_y { inity() };

int initx()
{
    return g_y;     // g_y isn't initialized when this is called
}

int inity()
{
    return 5;
}

int initialization_problem()
{
    std::cout << g_x << ' ' << g_y << '\n';
    return 0;
}

/* warning
    dynamic initialization of global variables causes a lot of problems in C++.
    avoid dynamic initialization wheneve possible.
*/


//========[ so what are very good reason to use non-const global variavles? ]========
// as a rule of thumb, any use of a global variable should meet at least the following two criteria:
    // 1. there should only ever be one of the thing the variable represents in your program
    // 2. its use should be ubiquitous throughout your program


//========[ protecting yourself from global destruction ]========
// if you do find a good use for a non-const global variable, a few useful bits of advice
// will minimize the amount of trouble you can get into

    // 1. prefix all non-namespaced global variables with "g" or "g_", or better yet
    //    put then in a namespace to reduce the chance of naming collisions

        namespace constants
        {
            constexpr double gravity { 9.8 };
        }

    // 2. instead of allowing direct acess to the global variable, it's a berrte practive
    //    to "encapsulate" the variable. make sure the variable can only be accessed from
    //    within the file it's declared in.

        //-----[ insted of ]------
        namespace constants_1
        {
            extern const double gravity { 9.8 };    // has external linkage, is directly accessible by other files
        }

        //------[ do this ]------
        namespace constants_2
        {
            constexpr double gravity { 9.8 };   // has internal linkage, is accessible only by this file
        }

        double getGravity()     // this funcion can be exported to other files to access the global outside of this file
        {
            // we could add logic here if needed later
            // or change the implementation transparently to the callers
            return constants_2::gravity;
        }

    // 3. when writing an otherwise standalone funtion that uses the global variable, don't
    //    use the variable directly in your function body. pass it as an argument instead.

        namespace constants_3
        {
            constexpr double gravity { 9.8 };
        }

        // this function can calculate the instant velocity for any gravity value
        double instantVelocity(int time, double gravity)
        {
            return gravity * time;
        }

        void print_instant_velocity()
        {
            std::cout << instantVelocity(5, constants_3::gravity);
        }


//=======================================================================================

int main()
{
    evil_globals();
    initialization_problem();
    print_instant_velocity();
}