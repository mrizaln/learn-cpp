#include <iostream>

/*---------------------------------------------------------------------------------------
                    ============[ default argument ]============
---------------------------------------------------------------------------------------*/

// a default argument is a default value provided for a function parameter

namespace default_argument
{
    void print(int x, int y=10)     // 10 is the default argument
    {
        std::cout << "x: " << x << '\n';
        std::cout << "y: " << y << '\n';
    }

    int main()
    {
        print(1, 2);
        print(3);

        return 0;
    }
}

// default arguments are an excellendt option when a function needs a value that has a reasonable
// default value, but for which you want to let the caller override if they wish.




/*---------------------------------------------------------------------------------------
                ============[ multiple default arguments ]============
---------------------------------------------------------------------------------------*/

namespace multiple_default_argument
{
    void print(int x=10, int y=20, int z=30)
    {
        std::cout << "Values: " << x << ' ' <<  y << ' ' << z << '\n';
    }

    int main()
    {
        print(1, 2, 3);
        print(1, 2);
        print(1);
        print();

        return 0;
    }
}

// C++ (as of C++20) does not support a function call syntax such as print(,,3) as a way to
// provide an explicit value [z] while using the default arguments for [x] and [y].
// this has two major consequences:
    // 1. default arguments can only be supplied for the rightmost parameters.
    // 2. if more than one default argument exists, the leftmost default argument should be
    //    the one most likely to be explicitly set by the user.




/*---------------------------------------------------------------------------------------
          ============[ default arguments can not be redeclared ]============
---------------------------------------------------------------------------------------*/

// for a function with a forward declaration and a function definition, the default argument
// can be declared in either the forward declaration or the function definition, but not both

namespace default_argument_cannot_redeclared
{
    void print(int x, int y=4);     // forward declaration

    void print(int x, int y)
    {
        std::cout << "x: " << x <<'\n';
        std::cout << "y: " << y <<'\n';
    }

    int main()
    {
        print(1);

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    if the function has a forward declaration (especially one in a header file), put the
    default arguments there. otherwise put the default argument in the function definition
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
          ============[ default arguments and function overloading ]============
---------------------------------------------------------------------------------------*/

// functions with default arguemts may be overloaded

namespace default_arguments_function_overloading
{
    void print(std::string string)
    {
        std::cout << string << '\n';
    }

    void print(char ch='c')
    {
        std::cout << "here's a char: " << ch << '\n';
    }

    int main()
    {
        print("Hello world!");      // resolves to print(std::string)
        print('a');                 // resolves to print(char)
        print();                    // resolves to print(char)

        return 0;
    }
}




//=======================================================================================

int main()
{
    default_argument::main();
    multiple_default_argument::main();
    default_argument_cannot_redeclared::main();
    default_arguments_function_overloading::main();

    return 0;
}