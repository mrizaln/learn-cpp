#include <iostream>
#include <cassert>  // for assert()


/*
  - all of the overloaded operators you have seen so far let you define the type of the operator's
    parameters, but not the number of parameters.
  - the paranthesis operator (operator()) is a particularly interesting operator in that it
    allows you to vary both the type and number of parameters it takes.

  - there are two things to keep in mind:
      > first, the paranthesis operator must be implementedas a member function.
      > second, in non-object-oriented C++, the () operator is used to call functions.
        in the case of classes, operator() is just a normal operator that calls a function
        (named operator()) like any other overloaded operator.
*/



/*---------------------------------------------------------------------------------------
                        ============[ an example ]============
---------------------------------------------------------------------------------------*/

/*
  - matrices are a key component of linear algebra, and are often used to do geometric
    modeling and 3d computer graphics work.
  - in the previous lesson of overloading operator[], we learned that we could overload
    operator[] to provide access to private one-dimenisional arra.
  - however, a matrix is a two-dimensional array.
  - because operator[] is limited to a single parameter, it is not sufficient to let us
    index a two-dimensional array.

  - however, because the operator() can take as many parameters as we want it to have, we
    can define a version of operator() that takes two integer index parameters, and use it
    to access our two-dimensional array.
*/

namespace an_example
{
    class Matrix
    {
    private:
        // 4x4 matrix
        double m_data[4][4]{};

    public:
        double& operator()(int row, int col);
        double operator()(int row, int colr) const;
        void operator()();
    };

    double& Matrix::operator()(int row, int col)
    {
        assert(col >= 0 && col < 4 && "col is out of range");
        assert(row >= 0 && row < 4 && "row is out of range");

        return m_data[row][col];
    }

    double Matrix::operator()(int row, int col) const
    {
        assert(col >= 0 && col <4 && "col is out of range");
        assert(row >= 0 && row <4 && "row is out of range");

        return m_data[row][col];    
    }

    void Matrix::operator()()
    {
        // reset all elements of the matrix to 0.0
        for (int row{ 0 }; row < 4; ++row)
        {
            for (int col{ 0 }; col < 4; ++col)
            {
                m_data[row][col] = 0.0;
            }
        }
    }


    void main()
    {
        Matrix matrix{};
        matrix(1, 2) = 4.5;
        std::cout << matrix(1, 2) << '\n';
        matrix();   // erase matrix
        std::cout << matrix(1, 2) << '\n';
    }
}

/*
  - because the operator() is so flexible, it can be tempting to use it for many different
    purposes.
  - however, this is stringly discouraged, since the () symbol does not really give any
    indication of what the operator is doing.
  - in our example above it would be better to have written the erase functionality as a
    function called clear() or erase(), as matrix.erase() is easier to understand than
    matrix() (which could do anything!).
*/




/*---------------------------------------------------------------------------------------
                  ============[ having fun with functors ]============
---------------------------------------------------------------------------------------*/

/*
  - operator() is also commonly overloaded to implement [functors] (or [function object]),
    which are classes that operate like functions.
  - the advantage of functor over normal function is that functors can store data in member
    variables.
*/

namespace functor
{
    class Accumulator
    {
    private:
        int m_counter{ 0 };

    public:
        int operator()(int i){ return (m_counter += i); }
    };


    void main()
    {
        Accumulator acc{};
        std::cout << acc(10) << '\n';       // prints 10
        std::cout << acc(20) << '\n';       // prints 30
    }
}

/*
  - why use functor if you can do the same with a function and a static variable?
  - well, we could, but because normal functions only have one global instance, we'd be limited
    to using it for one thing at a timr.
  - with functors, we can instantiate as many separate functor objects as we need and use
    them all simultaneously.
*/




//=======================================================================================

namespace quiz
{
    class MyString
    {
    private:
        std::string string{};

    public:
        MyString(std::string str) : string{ str } { }

        std::string operator()(int start, int length);
        std::string operator()(int start, int length) const;
    };

    std::string MyString::operator()(int start, int length)
    {
        return string.substr(start, length);
    }

    std::string MyString::operator()(int start, int length) const
    {
        return string.substr(start, length);
    }

    
    void main()
    {
        MyString string{ "Hello, world!" };
        std::cout << string(7, 5) << '\n';      // start at index 7 and return 5 characters
    }
}



//=======================================================================================

int main()
{
    an_example::main();
    functor::main();

    quiz::main();

    return 0;
}