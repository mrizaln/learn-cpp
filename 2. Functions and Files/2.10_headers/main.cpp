#include <iostream>
#include "add.h"

// angled brackets vs double quotes
    // angled brackets: header file we didn't write ourselves. the compiler will search for
    //                  the header only in the directories specified by the include
    //                  directories
    // double quotes: header written by ourselves. first search in the current directory, then
    //                in the include directories

// #include order
    // to maximize that missing includes will be flagged by compiler, order your #include
    // as follows
        // 1. the paired header file
        // 2. other headers from your project
        // 3. 3rd party library headers
        // 4. standard library headers
    // the headers grouping for each group should be sorted alphabetically

int add(int x, int y);      // the definition is in the add.cpp file

int main(){
    int x { 100 };
    int y { 20 };

    std::cout << add(x, y) << std::endl;
}

// to compile you need to include the add.cpp file at compile
// like this:
//      $ g++ -o out main.cpp add.cpp