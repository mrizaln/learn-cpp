#include <iostream>

int add(int x, int y);      // the definition is in the add.cpp file

int main(){
    int x { 100 };
    int y { 20 };

    std::cout << add(x, y) << std::endl;
}

// to compile you need to include the add.cpp file at compile
// like this:
//      $ g++ -o out main.cpp add.cpp