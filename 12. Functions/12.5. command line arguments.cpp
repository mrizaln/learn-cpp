#include <iostream>

/*
  - command line argments are optional string arguments that are passed by the operating
    system to the program when it is launched.

  - much like function parameters provide a way for a function to provide inputs to another
    function, command line arguments provide a way for people or programs to provide inputs
    to a program.
*/


/*---------------------------------------------------------------------------------------
               ============[ passing command line arguments ]============
---------------------------------------------------------------------------------------*/

/*
  - to pass an arguemt to a program, first you need to open command line (or shell).
    then type the program executable on the command line.
  - following that, type the arguments after the program executable separated by space.
  -  a program may receive more than one arguments separated by spaces.
*/

// an example, using convert program (from imagemagick package) to convert png to jpg
/*------------------------------------
    $ convert input.png output.jpg
------------------------------------*/




/*---------------------------------------------------------------------------------------
                ============[ using command line arguments ]============
---------------------------------------------------------------------------------------*/

// to receive command line arguments in the program, we need to change the form of main().
// this new form of main takes two arguments (named argc and argv by convention).

/*--------------------------------------
    int main(int argc, char* argv[])
----------------[ or ]------------------
    int main(int argc, char** argv)
--------------------------------------*/

/*
  - [argc] is an integer parameter containing a count of the number of arguments passed
    to the program (argc = argument count).
  - argc will always be at leas 1, because the first argument is always the name of the
    program itself.
  - each command line argument the user provides will cause argc to increase by 1.

  - [argv] is where the actual argument values are stored (argv = argument values).
  - although the declaration of argv looks intimidating, argv is really just an array of
    C-style strings.
  - the length of this array is argc.
*/

namespace example
{
    int main(int argc, char* argv[])
    {
        std::cout << "There are " << argc << " arguments:\n";

        for (int count{ 0 }; count < argc; ++count)
            std::cout << count << ' ' << argv[count] << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
    ============[ dealing with numeric arguments ]============
---------------------------------------------------------------------------------------*/

// command line arguments are always passed as strings, even if the value provided is numeric
// in nature.
// to use a command line argument as a number, you must convert it from a string to a number
// unfortunately, C++ makes this a little more difficult than it should be.

#include <sstream>  // for std::stringstream
#include <string>
namespace dealing_with_numeric_arguments
{
    int main(int argc, char* argv[])
    {
        if (argc <= 1)
        {
            // on some operating systems, argv[0] can end up as an empty string instead of
            // the program's name.
            if (argv[0])
                std::cout << "Usage: " << argv[0] << " <number> " << '\n';
            else
                std::cout << "Usage: <program name> <number> " << '\n';
            
            return 1;
        }

        // set up a string stream variable named convert, initialized with the input from argv[1]
        std::stringstream convert{ argv[1] };

        int myInt{};
        if (!(convert >> myInt))    // do the conversion
            myInt = 0;              // if conversion fails, set myInt to a default value

        std::cout << "Got integer: " << myInt << '\n';

        return 0;
    }

}




//=======================================================================================

int main(int argc, char* argv[])
{
    // example::main(argc, argv);
    dealing_with_numeric_arguments::main(argc, argv);
}