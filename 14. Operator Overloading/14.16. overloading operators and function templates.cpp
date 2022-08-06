#include <iostream>



/*
  - in lesson 8.14, we duscussed how the compiler will use function templates to instantiate
    functions, which are then compiled.
  - we also noted that these functions may not compile, if the code in the function template
    tries to perform some operation that the actual type doesn't support.

  - in this lesson we'll take a look at a few examples where our instantiated functions won't
    compile because our actual class types don't support those operators, and show how we
    can define those operators so that the instantiated functions will compile.
*/


/*---------------------------------------------------------------------------------------
      ============[ operators, function calls, and function templates ]============
---------------------------------------------------------------------------------------*/

namespace example
{
    // here we have a function template
    template <typename T>
    T average(const T* myArray, int numValues)
    {
        T sum{ 0 };
        for (int count{ 0 }; count < numValues; ++count)
            sum += myArray[count];      // a)

        sum /= numValues;               // b)
        return sum;
    }

    // here we have a class
    class Cents
    {
    private:
        int m_cents{};
    
    public:
        Cents(int cents)
            : m_cents{ cents }
        {
        }

        friend bool operator<(const Cents& c1, const Cents& c2);
        friend std::ostream& operator<<(std::ostream& out, const Cents& cents);

        // to make our class compile when using average function template above, we need
        // to provide definition for operator used in a) and b) above

        // a)
        Cents& operator+=(const Cents& cents)
        {
            m_cents += cents.m_cents;
            return *this;
        }

        // b)
        Cents& operator/=(int x)
        {
            m_cents /= x;
            return *this;
        }
    };

    bool operator<(const Cents& c1, const Cents& c2)
    {
        return c1.m_cents < c2.m_cents;
    }

    std::ostream& operator<<(std::ostream& out, const Cents& cents)
    {
        out << cents.m_cents << " cents";
        return out;
    }


    // our code will be able to compile
    void main()
    {
        Cents centsArray[] { Cents { 5 }, Cents { 10 }, Cents { 15 }, Cents { 14 } };
        std::cout << average(centsArray, 4) << '\n';
    }
}



int main()
{
    example::main();

    return 0;
}