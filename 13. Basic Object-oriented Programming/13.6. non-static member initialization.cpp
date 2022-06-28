#include <iostream>
#include <string>
#include <string_view>


/*
  - when writing a class that has multiple constructors (whih is most of them), haing to
    specify default values for all members in each constructor results in redundant code.
  - if you update the default value for a member, you need to touch each constructor.

  - it's possible to gibe normal class member variables (those that don't use static keyword)
    a default initialization value directly.
*/

namespace non_static_member_initialization
{
    class Rectangle
    {
    private:
        double m_length{ 1.0 };
        double m_width{ 1.0 };

    public:
        void print()
        {
            std::cout << "length: " << m_length << ", width: " << m_width << '\n';
        }
    };

    void main()
    {
        Rectangle x{};      // x.m_length = 1.0, x.m_width = 1.0
        x.print();
    }
}

/*
  - non-static member initialization (in-class member initializers) provides default values
    for your member variables that your constructor will use if the constructors do not provide
    initialization values for the members themselves.

  - if a default initialization value is provided and the constructor initializes the member
    via the member initializer list, the member initializer list will take precedence.
*/

namespace member_initializer_list_vs_non_static_member_initialization
{
    class Rectangle
    {
    private:
        double m_length{ 1.0 };
        double m_width{ 1.0 };

    public:
        Rectangle(double length, double width)
            : m_length{ length }
            , m_width{ width }
        {
            // m_lenght and m_width are initialied by the constructor (the default values
            // aren't used).
        }

        Rectangle(double length)
            : m_length{ length }
        {
            // m_length is initialized by the constructor
            // m_width's default valu (1.0) is used.
        }

        void print()
        {
            std::cout << "length: " << m_length << ", width: " << m_width << '\n';
        }
    };

    void main()
    {
        Rectangle x{ 2.0, 3.0 };
        x.print();

        Rectangle y{ 4.0 };
        y.print();
    }
}

// note that initializing members using non-static member initialization requires using either
// an equal sign, or a brace (uniform) initializer -- the paranthesis initialization from
// doesn't work here.


// [ rule ]
/*---------------------------------------------------------------------------------------
    favor use of non-static member initialization to give default values for your member
    variables.
---------------------------------------------------------------------------------------*/




//=======================================================================================

namespace quiz
{
    class Ball
    {
    private:
        std::string m_color{ "black" };
        double m_radius{ 10.0 };

    public:
        Ball() = default;

        Ball(std::string_view color)
            : m_color{ color }
        {
        }

        Ball(double radius)
            : m_radius{ radius }
        {
        }

        Ball(std::string_view color, double radius)
            : m_color{ color }
            , m_radius{ radius }
        {
        }

        void print()
        {
            std::cout << "color: " << m_color << ", radius: " << m_radius << '\n';
        }
    };

    void main()
    {
        Ball def;
        def.print();

        Ball blue{ "blue" };
        blue.print();

        Ball twenty{ 20.0 };
        twenty.print();

        Ball blueTwenty{ "blue", 20.0 };
        blueTwenty.print();
    }
}




//=======================================================================================

int main()
{
    non_static_member_initialization::main();
    member_initializer_list_vs_non_static_member_initialization::main();

    quiz::main();

    return 0;
}