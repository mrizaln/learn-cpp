#include <iostream>
#include <algorithm>

// we know that a pointer is a variable that holds the address of another variable.
// function pointers are similar, except that instead of pointing to variables, they point
// to functions.



/*---------------------------------------------------------------------------------------
                    ============[ pointers to functions ]============
---------------------------------------------------------------------------------------*/

// the syntax for creating a non-const function pointer is one of the ugliest things you
// will ever see in C++:

/*----------------------
    int (*fcnPtr)();
----------------------*/

// in the above, fcnPtr is a pointer to a function that has no parameters and returns an
// integer.
// fcnPtr can point to any function that matches this type.

// to make a const functoin pointer:

/*----------------------------
    int (*const fcnPtr)();
----------------------------*/




/*---------------------------------------------------------------------------------------
         ============[ assigning a function to a function pointer ]============
---------------------------------------------------------------------------------------*/

namespace assign_function_to_pointer
{
    int foo()
    {
        return 5;
    }

    int goo()
    {
        return 6;
    }

    void main()
    {
        int (*fcnPtr)(){ &foo };        // fcnPtr points to function foo
        fcnPtr = &goo;                  // fcnPtr points to goo
    }
}

// unlike fundamenta types, C++ will implicitly convert a function into a function pointer
// if needed.
// however, it will not implicitly convert function pointers to void pointers (and vice-versa).

// function pointer can also be initialized ot assigned the value nullptr

namespace assign_function_to_pointer
{
    int (*fcnPtr)(){ nullptr };
}




/*---------------------------------------------------------------------------------------
         ============[ calling a function using a function pointer ]============
---------------------------------------------------------------------------------------*/

// there are two wway to call a function using function pointer:

namespace calling_function_using_function_pointer
{
    int foo(int x)
    {
        return x;
    }

    // first method: explicit dereference
    void first_method()
    {
        int (*fcnPtr)(int){ &foo };
        (*fcnPtr)(5);                   // explicit dereference
    }

    // second method: implicit dereferene
    void second_method()
    {
        int (*fcnPtr)(int){ &foo };
        fcnPtr(5);                      // implicit dereference
    }
}

// note: default parameters won't work for functions called through function pointers.
// because default parameters are resolved on compile-time, whereas function pointers are
// resolved at run-time.




/*---------------------------------------------------------------------------------------
      ============[ passing functions as arguments to other functions ]============
---------------------------------------------------------------------------------------*/

// functions used as arguments to another function are sometimes called [callback functions].

namespace passing_function
{
    // Note our user-defined comparison is the third parameter
    void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
    {
        for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
        {
            // bestIndex is the index of the smallest/largest element we've encountered so far.
            int bestIndex{ startIndex };

            for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
            {
                // If the current element is smaller/larger than our previously found smallest
                if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
                {
                    bestIndex = currentIndex;
                }
            }

            // Swap our start element with our smallest/largest element
            std::swap(array[startIndex], array[bestIndex]);
        }
    }

    bool ascending(int x, int y)
    {
        return x > y;
    }

    bool descending(int x, int y)
    {
        return x < y;
    }

    bool evensFirst(int x, int y)
    {
        // if x even and y odd, x goes first (no swap)
        if ((x % 2 == 0) && !(y % 2 == 0))
            return false;
        
        // if x odd and y even, y goes first (swap)
        if (!(x % 2 == 0) && (y % 2 == 0))
            return true;

        // ascending order
        return ascending(x, y);
    }

    void main()
    {
        int array[]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };

        // std::ranges::sort(array, evensFirst);
        selectionSort(array, std::ssize(array), evensFirst);

        for (int i : array)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                ============[ providing default functions ]============
---------------------------------------------------------------------------------------*/

// the same as to give default argument to a variable of a function parameter

/*
    void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);
*/




/*---------------------------------------------------------------------------------------
    ============[ making function pointers prettier with type aliases ]============
---------------------------------------------------------------------------------------*/

// the title is self-explanatory

using ValidateFunction = bool(*)(int, int);

// this defines a type alias caleed ValidateFunction that is a pointer to a function that
// takes to ints and retuns a bool

void a_function__(int x, int y, bool (*fcnPtr)(int, int)) {};      // ugly
void a_function_0(int x, int y, ValidateFunction pfcn) {};         // clean




/*---------------------------------------------------------------------------------------
                    ============[ using std::function ]============
---------------------------------------------------------------------------------------*/

// an alternative method of defining and storing function pointers is to use std::function,
// which is part of the standard library <function> header.

// to define a function pointer using this method, declare a std::function object like so

#include <functional>

namespace using_std_function
{
    void doSomething(int x, int y, std::function<bool(int, int)> fcn)
    {
        // do something
    }
}




/*---------------------------------------------------------------------------------------
            ============[ type inference for function pointers ]============
---------------------------------------------------------------------------------------*/

// much like the auto keyword can be used to infer the type of normal variables, the auto
// keyword can also infer the type of a function pointer.

namespace type_inference_function_pointer
{
    int foo(int x)
    {
        return x;
    }

    void main()
    {
        auto fcnPtr{ &foo };
        std::cout << fcnPtr(5) << '\n';
    }
}




//=======================================================================================

namespace quiz
{
    // calculator

    template <typename T>
    T getInput(std::string message)
    {
        T input {};
        std::cout << message;
        std::cin >> input;
        return input;
    }

    int add(int x, int y)      { return x + y; }
    int subtract(int x, int y) { return x - y; }
    int multiply(int x, int y) { return x * y; }
    int division(int x, int y) { return x / y; }

    using ArithmeticFunction = int (*)(int, int);

    ArithmeticFunction getArithmeticFunction(char op)
    {
        switch (op)
        {
            case '+': return add;
            case '-': return subtract;
            case '*': return multiply;
            case '/': return division;
            default:  return nullptr;
        }
    }

    void main()
    {
        int  num1{ getInput<int> ("Please input an integer         (1/2): ") };
        char op  { getInput<char>("Select an operation      (+, -, *, /): ") };
        int  num2{ getInput<int> ("Please input an integer         (2/2): ") };

        auto operate{ getArithmeticFunction(op) };
        if (operate)
            std::cout << num1 << ' ' << op << ' ' << num2 << " = " << operate(num1, num2) << '\n';
    }
}




//=======================================================================================

int main()
{
    passing_function::main();
    type_inference_function_pointer::main();

    quiz::main();

    return 0;
}