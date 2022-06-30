#include <iostream>


/*---------------------------------------------------------------------------------------
    ============[ defining member functions outside the class definition ]============
---------------------------------------------------------------------------------------*/

/*
  - C++ provides a way to separate the "declaration" portion of the class from the "implementation"
    portion.
  - this is done by defining the class member functions outside of the class definition.
  - to do so, simply define the member functions of the class as if they were normal functions,
    but prefix the class name to the function using the scope resolution operator.
*/

namespace defining_member_functions_outside_the_class_definitions
{
    class Date
    {
    private:
        int m_year{};
        int m_month{};
        int m_day{};

    public:
        Date(int year, int month, int day);

        void setDate(int year, int month, int day);

        int getYear() { return m_year; }
        int getMonth() { return m_month; }
        int getDay() { return m_day; }
    };

    // date constructor
    Date::Date(int year, int month, int day)
    {
        setDate(year, month, day);
    }

    // date member function
    void Date::setDate(int year, int month, int day)
    {
        m_year = year;
        m_month = month;
        m_day = day;
    }

    // other example with member initializer list
    class Calc
    {
    private:
        int m_value{ 0 };

    public:
        Calc(int value=0);

        auto& add(int value);
        auto& sub(int value);
        auto& mul(int value);
        int getValue() { return m_value; }
    };

    Calc::Calc(int value) : m_value{ value } {}

    auto& Calc::add(int value) { m_value += value; return *this; }
    auto& Calc::sub(int value) { m_value -= value; return *this; }
    auto& Calc::mul(int value) { m_value *= value; return *this; }
}




/*---------------------------------------------------------------------------------------
          ============[ putting class definitions in a header file ]============
---------------------------------------------------------------------------------------*/

/*
  - class definitions can be put in header files in order to facilitate reuse in multiple
    files or multiple projects.
  - traditionally, the class definition is put in a header file of the same name as the class,
    and the member functions defined outside of the class are put in a .cpp file of the same
    name as the class.
*/




/*---------------------------------------------------------------------------------------
     ============[ what should i define in the header file vs cpp file, ]============
     ============[   and what inside the class definition vs outside    ]============
---------------------------------------------------------------------------------------*/

/*
  - the writer recommend the following:
    1. for classes used in only one file that aren't generally reusable, define them directly
       in the single .cpp file they're used in.
    2. for classes used in multiple files, or intended for general reuse, define them in a
       .h file that has the same name as the class.
    3. trivial member functions (trivial ctor or dtor, access functions, etc.) can be defined
       inside the class.
    4. non-trivial member functions should be defined in a .cpp file that has the same name
       as the class.
*/

// default parameter for member functions should be declared in the class definition (in
// the header file), where they can be seen by whomever #includes the header.