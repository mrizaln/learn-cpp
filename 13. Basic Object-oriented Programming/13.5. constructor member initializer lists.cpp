#include <iostream>
#include <string_view>

/*---------------------------------------------------------------------------------------
                 ============[ member initializer lists ]============
---------------------------------------------------------------------------------------*/

/*
  - C++ provides a method for initializing class member variables (rather that assigning
    values to them after they are created) via a [member initializer list] ("member initialization
    list").
  - do not confuse these with the similarly named initializer list that we can use to assign
    values to arrays.
*/

namespace member_initializer_lists
{
    class Something
    {
    private:
        int m_value1{};
        double m_value2{};
        char m_value3{};
        const std::string m_const_string{};

    public:
        Something() : m_value1{ 1 }, m_value2{ 2.2 }, m_value3{ 'c' }, m_const_string{ "haha" }    // initialize our member variable
        {
            // no need for assignment here
        }

        Something(int value1, double value2, char value3, std::string_view str)
            : m_value1{ value1 }, m_value2{ value2 }, m_value3{ value3 }, m_const_string{ str }
        {
            // no need for assignment here
        }

        void print()
        {
            std::cout << "Something(" << m_value1 << ", " << m_value2 << ", " << m_value3 << ", " << ")\n";
        }
    };

    void main()
    {
        Something something{ 12, 23.3, 'v', "ndsafkj" };
        something.print();
    }
}

/*
  - the member initializer list is inserted after the constructor parameters.
  - it begins with a colon (:), and then lists each variable to initialize along with the
    value for that variable separated by a comma.
*/

// [ rule ]
/*---------------------------------------------------------------------------------------
    use member initializer lists to initialize your class member variables instead of
    assignment.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                  ============[ initializing array members ]============
---------------------------------------------------------------------------------------*/

namespace initializing_array_members
{
    class Something
    {
    private:
        const int m_array[5];

    public:
        // prior to C++11, you can only zero initialize an array member via a member initialization
        // list. however, since C++11, we can fully initialize a member array using uniform
        // initialization.
        Something(): m_array{ 1, 2, 3, 4, 5 }
        {
        }
    };
}




/*---------------------------------------------------------------------------------------
        ============[ initializing member variables that are classes ]============
---------------------------------------------------------------------------------------*/

// a member initialization list can also be used to initialize members that are classes.

namespace initializing_member_variables_that_are_classes
{
    class A
    {
    public:
        A(int x = 0) { std::cout << "A = " << x << '\n'; }
    };

    class B
    {
    private:
        A m_a{};

    public:
        B(int y)
            : m_a{ y - 1 }
        {
            std::cout << "B = " << y << '\n';
        }
    };

    void main()
    {
        B b{ 5 };
    }
}




/*---------------------------------------------------------------------------------------
            ============[ formatting your initializer lists ]============
---------------------------------------------------------------------------------------*/

namespace formatting_your_initializer_list
{
    class Something
    {
    private:
        int m_value1{};
        double m_value2{};
        char m_value3{};
        float m_value4{};

    public:
        // if the initializer list fits on the same line as the function name, then it is
        // fine to put everything on one line.
        Something() : m_value1{ 1 }, m_value2{ 2.2 }, m_value3{ 'c' }
        {
        }

        // if the initializer list doesn't fit on the same line as the function name, then
        // it should go indented on the next line.
        Something(int value1, double value2, char value3='c')
            : m_value1{ value1 }, m_value2{ value2 }, m_value3{ value3 }
        {
        }

        // if all of the initializers list don't fit on a single line, then you can space
        // them out, one per line.
        Something(int value1, double value2, char value3='c', float value4=3.14f)
            : m_value1{ value1 }
            , m_value2{ value2 }
            , m_value3{ value3 }
            , m_value4{ value4 }
        {
        }
    };
}




/*---------------------------------------------------------------------------------------
                  ============[ initializer list order ]============
---------------------------------------------------------------------------------------*/

/*
  - variables in the initializer list are not initialized in the order that they are specified
    in the initializer list.
  - instead, they are initialized in the order in which they are declared in the class.
*/




//=======================================================================================

#include <cstdint>      // for uint8_t

namespace quiz
{
    /*
      - write a class named RGBA that contains 4 member variables of type std::uint8_t named
        m_red, m_green, m_blue, and m_alpha.
      - assign default values of 0 to m_red, m_green, and m_blue, and 255 to m_alpha.
      - create a constructor that uses a member initializer list that allows the user to
        initialize values for m_red, m_green, m_blue, and m_alpha.
      - include a print() function that outputs the value of the member variables.
    */

    class RGBA
    {
    public:
        // update: use uint_fast8_t or uint_least8_t
        using color_type = uint8_t;

    private:
        color_type m_red{};
        color_type m_green{};
        color_type m_blue{};
        color_type m_alpha{};

    public:
        RGBA(color_type red=0, color_type green=0, color_type blue=0, color_type alpha=255)
            : m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha }
        {
        }

        void print()
        {
            std::cout << "r=" << static_cast<int>(m_red)   << ' '
                      << "g=" << static_cast<int>(m_green) << ' '
                      << "b=" << static_cast<int>(m_blue)  << ' '
                      << "a=" << static_cast<int>(m_alpha) << '\n';
        }
    };

    void main()
    {
        RGBA teal{ 0, 127, 127 };
	    teal.print();
    }
}


//=======================================================================================

int main()
{
    member_initializer_lists::main();
    initializing_member_variables_that_are_classes::main();

    quiz::main();

    return 0;
}