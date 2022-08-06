#include <iostream>
#include <cassert>


/*---------------------------------------------------------------------------------------
            ============[ assignment vs copy constructor ]============
---------------------------------------------------------------------------------------*/

/*
  - the purpose of the copy constructor and the assignment operator are almost equivalent:
    both copy one object to another.
  - however, the copy constructor initializes new objects, whereas the assignment operator
    replaces the contents of existing objects.
*/




/*---------------------------------------------------------------------------------------
            ============[ overloading the assignment operator ]============
---------------------------------------------------------------------------------------*/

// the assignment operator must be overloaded as a member function

namespace overloading_assignment_operator
{
    class Fraction
    {
    private:
        int m_numerator{ 0 };
        int m_denominator{ 1 };

    public:
        Fraction(int numerator=0, int denominator=1)
            : m_numerator{ numerator }
            , m_denominator{ denominator }
        {
            assert(denominator != 0);
        }

        Fraction(const Fraction& fraction)
            : m_numerator{ fraction.m_numerator }
            , m_denominator{ fraction.m_denominator }
        {
        }

        Fraction& operator=(const Fraction& fraction);
        friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
    };

    std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
    {
        out << fraction.m_numerator << '/' << fraction.m_denominator;
        return out;
    }

    Fraction& Fraction::operator=(const Fraction& fraction)
    {
        m_numerator = fraction.m_numerator;
        m_denominator = fraction.m_denominator;

        // return the existing object so we can chain this operator
        return *this;
    }


    void main()
    {
        Fraction fiveThirds{ 5, 3 };
        Fraction f;
        f = fiveThirds;
        Fraction f1;
        Fraction f2;
        f2 = f1 = f;                // we can chain the assignment
        std::cout << f << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                ============[ issues due to self-assignment ]===========
---------------------------------------------------------------------------------------*/

/*
  - C++ allows self-assignment, like x = x
  - under the simplistic implementation above, all of the members will be assigned to themselves,
    which has no overall impact.
  - however, in cases where an assignment operator need to dynamically assign memory, self-
    assignment can actually be dangerous.
*/

namespace self_assignment_issues
{
    class MyString
    {
    private:
        char* m_data {};
        int m_length {};

    public:
        MyString(const char* data = nullptr, int length = 0 )
            : m_length { length }
        {
            if (length)
            {
                m_data = new char[length];

                for (int i { 0 }; i < length; ++i)
                    m_data[i] = data[i];
            }
        }
        ~MyString()
        {
            delete[] m_data;
        }

        // Overloaded assignment
        MyString& operator= (const MyString& str);

        friend std::ostream& operator<<(std::ostream& out, const MyString& s);
    };

    std::ostream& operator<<(std::ostream& out, const MyString& s)
    {
        out << s.m_data;
        return out;
    }

    // A simplistic implementation of operator= (do not use)
    MyString& MyString::operator= (const MyString& str)
    {
        // if data exists in the current string, delete it
        if (m_data) delete[] m_data;

        m_length = str.m_length;

        // copy the data from str to the implicit object
        m_data = new char[str.m_length];

        for (int i { 0 }; i < str.m_length; ++i)
            m_data[i] = str.m_data[i];

        // return the existing object so we can chain this operator
        return *this;
    }

    void main()
    {
        MyString alex("Alex", 5);       // Meet Alex
        MyString employee;
        employee = alex;                // Alex is our newest employee
        std::cout << employee << '\n';  // Say your name, employee

        alex = alex;
        std::cout << alex;      // we'll probably got garbage output
    }
}

// in the above, we delete the object that we want to assign (because they are the same)




/*---------------------------------------------------------------------------------------
           ============[ detecting and handling self-assignment ]============
---------------------------------------------------------------------------------------*/

namespace handling_self_assignment
{
    class MyString
    {
    private:
        char* m_data {};
        int m_length {};

    public:
        MyString(const char* data = nullptr, int length = 0 )
            : m_length { length }
        {
            if (length)
            {
                m_data = new char[length];

                for (int i { 0 }; i < length; ++i)
                    m_data[i] = data[i];
            }
        }
        ~MyString()
        {
            delete[] m_data;
        }

        // Overloaded assignment
        MyString& operator= (const MyString& str);

        friend std::ostream& operator<<(std::ostream& out, const MyString& s);
    };

    std::ostream& operator<<(std::ostream& out, const MyString& s)
    {
        out << s.m_data;
        return out;
    }

    MyString& MyString::operator= (const MyString& str)
    {
        // self-assignment check
        if (this == &str)
            return *this;

        // if data exists in the current string, delete it
        if (m_data) delete[] m_data;

        m_length = str.m_length;

        // copy the data from str to the implicit object
        m_data = new char[str.m_length];

        for (int i { 0 }; i < str.m_length; ++i)
            m_data[i] = str.m_data[i];

        // return the existing object so we can chain this operator
        return *this;
    }
}

/*
  - by checking if the address of our implicit object is the same as the address of the object
    being passed in as a parameter, we have our assignment operator just return immediately
    without doing any other work.
*/




/*---------------------------------------------------------------------------------------
             ============[ when not to handle self-assignment ]============
---------------------------------------------------------------------------------------*/

/*
  - typicallly, self-assignment check is skipped for copy constructor, because the object
    being copy constructed is newly created.
  - the self-assignment check also may be omitted in a classes that can naturally handle
    self-assignment;
*/




/*---------------------------------------------------------------------------------------
                  ============[ the copy and swap idiom ]============
---------------------------------------------------------------------------------------*/

// a better way to handle self-assignment issues is via what's called the copy and swap idiom:
// [https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom]




/*---------------------------------------------------------------------------------------
                  ============[ default assignment operator ]===========
---------------------------------------------------------------------------------------*/

/*
  - unlike other opearators, the compiler will provide a default public assignment operator
    for you class if you do not provide one.
  - this assignment operator does memberwise assignment.

  - just like other constructors and operators, you can prevent assignments from being made
    by making your assignment operator private or using the delete keyword.
*/



//=======================================================================================

int main()
{
    overloading_assignment_operator::main();
    self_assignment_issues::main();

    return 0;
}