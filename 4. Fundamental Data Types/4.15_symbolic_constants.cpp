// before we have talked about literal constants
// now we will talk about symbolic constants

//========[ const variables ]========
// to make a variable constant, simply put the const keyword before or after the variable type
void example()
{
    const double gravity{ 9.8 };    // preferred
    int const sidesInSquare{ 4 };   // okay, but not preferred
}

// const variables must be initialized
// note that const variables can be initialized from other variables
#include <iostream>
void initialized()
{
    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    const int userAge{ age };
}

// compile-time constant vs runtime constant
void comparison()
{
    int num{};
    std::cin >> num;
    const int constantNum{ num };   // runtime constant
    const int otherConstantNum{ 100 }; // compile-time constant
}

//========[ constexpr ]========
// constexpr ensures that a constant must be compile-time constant
void compile_time_constant()
{
    constexpr double gravity{ 9.8 };    // ok
    constexpr int sum{ 4 + 5 };         // ok, can be resolved at compile-time

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    // constexpr int myAge{ age };         // compile error, age is runtime constant
}

int main()
{
    compile_time_constant();
}