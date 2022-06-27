#include <iostream>

/*---------------------------------------------------------------------------------------
                ============[ public and private members ]============
---------------------------------------------------------------------------------------*/

namespace public_and_private
{
    struct DateStruct
    {
        int year{};
        int month{};
        int day{};
    };

    class DateClass
    {
        int year{};
        int month{};
        int day{};
    };

    void main()
    {
        DateStruct date_s;

        // we can access the member of date_s directly
        date_s.year = 2022;
        date_s.month = 6;
        date_s.day = 25;

        DateClass date_c;

        // we can't access the member of date_c directly
        // date_c.year = 2022;     // error
        // date_c.month = 6;       // error
        // date_c.day = 25;        // error
    }
}

/*
  - all members of a struct are public by default.
  - [public members] are members of a struct or class that can be accessed directly by
    anyone, including from code that exists outside the struct or class.

  - by default, all members of a class are private.
  - [private members] are members of a class that can only be accessed by other members of
    the class.
*/




/*---------------------------------------------------------------------------------------
                      ============[ access specifiers ]============
---------------------------------------------------------------------------------------*/

// although class members are private by default, we can make them public by using the
// public keyword.

namespace access_specifiers
{
    class DateClass
    {
    public:
        int m_year{};
        int m_month{};
        int m_day{};
    };

    void main()
    {
        DateClass date;
        date.m_year = 2022;
        date.m_month = 6;
        date.m_day = 26;
    }
}

// because DateClass's members are now public, they can be accessed directly by main().

/*
  - the [public] keyword, along with the following colo, is called an access specifier.
  - [access specifiers] determine who has access to the members that follow the specifier.

  - C++ provides 3 different access specifier keywords:
    1. public
    2. private
    3. protected (works much like private does)
*/




/*---------------------------------------------------------------------------------------
                  ============[ mixing access specifiers ]============
---------------------------------------------------------------------------------------*/

// a class can use multiple access specifiers to set the access levels of each of its members.

namespace mixing_type_specifiers
{
    class DateClass
    {
        int m_year{};       // private by default, can only be accessed by other members
        int m_month{};      // ^^^
        int m_day{};        // ^^^
    
    public:
        void setDate(int year, int month, int day)      // public, can be access by anyone 
        {
            m_year = year;
            m_month = month;
            m_day = day;
        }

        void print()    // public, can be accessed by anyone
        {
            std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
        }
    };

    void main()
    {
        DateClass date;
        date.setDate(2022, 6, 26);
        date.print();
    }
}

// the group of public members of a class are often referred to as a [public interface].




/*---------------------------------------------------------------------------------------
          ============[ access controls work on a per-class basis ]=============
---------------------------------------------------------------------------------------*/

// consider this following program

namespace access_controls_work_on_a_per_class_basis
{
    class DateClass
    {
        int m_year{};
        int m_month{};
        int m_day{};

    public:
        void setDate(int year, int month, int day)
        {
            m_year = year;
            m_month = month;
            m_day = day;
        }

        void print()
        {
            std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
        }

        // note the addition of this function
        void copyFrom(const DateClass& d)
        {
            // note that we can access the private member of d directly
            m_year = d.m_year;
            m_month = d.m_month;
            m_day = d.m_day;
        }
    };

    void main()
    {
        DateClass date;
        date.setDate(2022, 6, 26);
        date.print();

        DateClass copy{};
        copy.copyFrom(date);
        copy.print();
    }
}

/*
  - one nuance of C++ that is often missed or misunderstood is that access control works
    on a per-class basis, not a per-object basis.
  - this means that when a function has access to the private members of a class, it can
    access the private members of any object of that class type that it can see.
*/




/*---------------------------------------------------------------------------------------
                ============[ structs vs classes revisited ]============
---------------------------------------------------------------------------------------*/

/*
  - the actual differences between a class and a struct in C++ is that a class defaults
    its members to private while a struct defaults its members to public.
*/




//=======================================================================================

namespace quiz_1
{
    class point3d
    {
        int m_x;
        int m_y;
        int m_z;

    public:
        void setValues(int x, int y, int z)
        {
            m_x = x;
            m_y = y;
            m_z = z;
        }

        void print()
        {
            std::cout << '<' << m_x << ", " << m_y << ", " << m_z << ">\n";
        }

        void copyFrom(const point3d& p)
        {
            m_x = p.m_x;
            m_y = p.m_y;
            m_z = p.m_z;
        }

        bool isEqual(const point3d& p)
        {
            return m_x == p.m_x && m_y == p.m_y && m_z == p.m_z;
        }
    };

    void main()
    {
        point3d point1{};
        point1.setValues(4, 12, 5);
        point1.print();

        point3d point2{};
        point2.copyFrom(point1);

        point3d point3{};
        point3.setValues(12, 1, 2);

        std::cout << std::boolalpha;
        std::cout << "point1 and point2 is equal: " << point1.isEqual(point2) << '\n';      // true
        std::cout << "point2 and point3 is equal: " << point2.isEqual(point3) << '\n';      // false
        std::cout << "point3 and point1 is equal: " << point3.isEqual(point1) << '\n';      // false
    }
}




// #include <vector>
#include <cassert>

namespace quiz_2
{
    /*     write a class that implements a simple stack     */

    class Stack
    {
        int m_array[10]{};        // can only hold 10 items
        int m_size{ 0 };

    public:
        void reset()
        {
            for (int& n: m_array)
            {
                n = 0;
            }
        }

        bool push(int n)
        {
            // the stack is full
            if (m_size >= 10)
                return false;

            m_array[m_size] = n;
            ++m_size;

            return true;
        }

        int pop()
        {
            // stack is empty
            assert(m_size && "can't pop an empty stack");

            --m_size; 
            return m_array[m_size];
        }

        void print()
        {
            std::cout << "( ";

            for (int i{ 0 }; i < m_size; ++i)
                std::cout << m_array[i] << ' ';

            std::cout << ")\n";
        }
    };

    void main()
    {
        Stack stack;
        stack.reset();

        stack.print();

        stack.push(5);
        stack.push(3);
        stack.push(8);
        stack.print();

        stack.pop();
        stack.print();

        stack.pop();
        stack.pop();

        stack.print();
    }
}


//=======================================================================================

int main()
{
    // mixing_type_specifiers::main();
    // access_controls_work_on_a_per_class_basis::main();

    // quiz_1::main();
    quiz_2::main();

    return 0;
}