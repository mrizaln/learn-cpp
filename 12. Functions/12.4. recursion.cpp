#include <iostream>
#include <vector>

// a recursive function in C++ is a function that calls itself.

/*---------------------------------------------------------------------------------------
              ============[ recursive termination conditions ]============
---------------------------------------------------------------------------------------*/

// a recursive termination is a condition that, when met, will cause the recursive function
// to stop calling itself.

namespace recursive_function_with_termination_condition
{
    void countDown(int count)
    {
        std::cout << "push " << count << '\n';
        
        if (count > 1)  // termination condition
            countDown(count-1);
        
        std::cout <<"pop " << count << '\n';
    }

    int sumTo(int sumto)
    {
        if (sumto <= 0)      return 0;
        else if (sumto == 1) return 1;
        else                 return sumTo(sumto-1) + sumto;
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ recursive algorithm ]============
---------------------------------------------------------------------------------------*/

/*
  - recursive functions typically solve a problem by first finding the solution to a subset
    of the problem (recursively), and then modifying that sub-solution to get a solution.

  - in many recursive alogithms, some inputs produce trivial outputs (for example, sumTo(1)
    has the trivial output 1, no recursion required).
  - inputs for which an algorithm trivially produces an output is called a [base case].
  - base cases act as termination condition for the algorithm.
*/




/*---------------------------------------------------------------------------------------
                    ============[ fibonacci numbers ]============
---------------------------------------------------------------------------------------*/

// fibonacci numbers are defined mathematically as:
/*----------------------------------------
    F(n) = 0              ;  if n == 0
           1              ;  if n == 1
           F(n-1) + F(n-2);  if n  > 1
----------------------------------------*/

namespace fibonacci
{
    int fibonacci_simple(int count)
    {
        // termination condition
        if (count == 0) return 0;
        if (count == 1) return 1;

        return fibonacci_simple(count-1) + fibonacci_simple(count-2);
    }
}




/*---------------------------------------------------------------------------------------
                   =============[ memoization algorithms ]============
---------------------------------------------------------------------------------------*/

// the above recursive Fibonacci algorithm isn't very efficient, in part because each call
// to a Fibonacci non-base case results in two more Fibonacci calls.
// this produces an exponential number of function calls.

// there are technique that can be used to reduce the number of calls necessary.
// one technique, called [memoization], caches the result of expensive function calls so
// the result can be returned when the same input occurs again.

namespace fibonacci
{
    int fibonacci_memoized(int count)
    {
        // cache
        static std::vector<int> results{ 0, 1 };

        if (count < std::ssize(results))
            return results[count];
        else
        {
            results.push_back(fibonacci_memoized(count-1) + fibonacci_memoized(count-2));
            return results[count];
        }
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ recursive vs iterative ]============
---------------------------------------------------------------------------------------*/

/*
  - recursive problem can always be solved iteratively, but for non-trivial problems, the
    recursive version is often much simpler to write (and read)

  - iterative functions are almost always more efficient than their recursive counterparts.
  - this is because every time you call a function there is some amount of overhead that
    takes place in pushing and popping stack frames.
  - iterative functions avoid this overhead.

  - sometimes the recursive implementation of a functions is so much cleaner and easier to
    follow that incurring a little extra overhead is more than worth it for the benefir in
    maintainability.

  - in general, recursion is a good choice when most of the following are true:
      > the recursive code is much simpler to implement.
      > the recursion depth can be limited.
      > the iterative version of the algorithm requires managing a stack of data.
      > this isn't a performance-critical section of code.

  - however, if the recursive algorithm is simpler to implement, it may make sense to start
    recursively and then optimize to an iterative algorithm later.
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    generally favor iteration over recursion, except when recursion really makes sense.
---------------------------------------------------------------------------------------*/




//=======================================================================================

#include <cassert>

namespace quiz_1
{
    /*
        write a factorial function using recursion
    */

    int factorial(int num)
    {
        // termination condition
        if (num == 0 || num == 1) return 1;
        else if (num < 0) assert(false && "cannot be negative!");   // no negative num
        
        return (num * factorial(num-1));
    }

    void main()
    {
        // test
        std::cout << "\nrecursive factorial:\n";
        std::cout << "0! = " << factorial(0) << " == 1\n";
        std::cout << "1! = " << factorial(1) << " == 1\n";
        std::cout << "2! = " << factorial(2) << " == 2\n";
        std::cout << "3! = " << factorial(3) << " == 6\n";
        std::cout << "5! = " << factorial(5) << " == 120\n";
        std::cout << "8! = " << factorial(8) << " == 40320\n";
    }
}


namespace quiz_2
{
    /*
        write a recursive function that takes an integer as input an returns the sum of
        each individual digit in the integer. assume the input values are positive.
    */

    auto sumDigit(auto num)
    {
        // termination condition (base case)
        if (num / 10 == 0) return num;

        return (num % 10 + sumDigit(num / 10));
    }

    void main()
    {
        // test
        std::cout << "\nsum digit:\n";
        std::cout << "1 = "            << sumDigit(1)            << " == " << 1  << '\n';
        std::cout << "67 = "           << sumDigit(67)           << " == " << 13 << '\n';
        std::cout << "124 = "          << sumDigit(124)          << " == " << 7  << '\n';
        std::cout << "234986 = "       << sumDigit(234986)       << " == " << 32 << '\n';
        std::cout << "234986547936 = " << sumDigit(234986547936) << " == " << 66 << '\n';
    }
}


namespace quiz_3
{
    /*
        write a program that asks the user to enter a positive integer, and then uses a
        recursive function to print out the binary representation for that number.
    */

    void printBinaryFromInt(unsigned int num)
    {
        // convert negative number (signed int) to positive (unsigned int)
        // the bit representation is the same

        // base case
        if (num == 0) return;

        printBinaryFromInt(num/2);
        std::cout << (num % 2);
    }

    int getInt()
    {
        int input{};

        while (true)
        {
            std::cout << "Please enter an integer: ";
            std::cin >> input;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Not an integer.\n";
            }
            else 
                return input;
        }
    }

    void main()
    {
        int integer{ getInt() };
        printBinaryFromInt(integer);   
        std::cout << '\n';
    }
}



//=======================================================================================

int main()
{
    recursive_function_with_termination_condition::countDown(5);
    std::cout << recursive_function_with_termination_condition::sumTo(5) << '\n';

    // first 13 fibonacci numbers
    for (int count{ 0 }; count < 13; ++count)
        std::cout << fibonacci::fibonacci_simple(count) << ' ';
    std::cout << '\n';

    // first 13 fibonacci numbers (using memoized version)
    for (int count{ 0 }; count < 13; ++count)
        std::cout << fibonacci::fibonacci_memoized(count) << ' ';
    std::cout << '\n';

    quiz_1::main();
    quiz_2::main();
    quiz_3::main();

    return 0;
}