#include <iostream>
#include <cassert>



// when all members of a class (or struct) are [public], we can use [aggregate initialization]
// to initialize the class (or struct) using list-initialization.

namespace aggregate_initialization
{
    class Foo
    {
    public:
        int m_x{};
        int m_y{};
    };

    void main()
    {
        Foo foo{ 6, 7 };        // list-initialization
    }
}

// however as soon as we make any member variables private, we're no longer able to initialize
// classes in this way.

// then how do we initialize a class with private member variables?
// the answer is though constructors



/*---------------------------------------------------------------------------------------
                       ============[ constructors ]============
---------------------------------------------------------------------------------------*/

/*
  - a [constructor] is a spcial kind of class member function that is automatically called
    when an object of that class is created.
  - constructors are typically used to initialize member variables of the class to appropiate
    user-provided values, or to do any setup steps necessary for the class to be used.

  - after a constructor executes, the object should be in a well-defined, usable state.

  - constructors have specific rules for how they must be named:
      1. constructors must have the same name as the class.
      2. constructors have no return type.
*/




/*---------------------------------------------------------------------------------------
       ============[ default constructors and default initialization ]============
---------------------------------------------------------------------------------------*/

// a constructor that takes no parameters is called a [default constructor].
// it is called if no user-provided initialization values are provided.

namespace constructor
{
    class Fraction
    {
        int m_numerator{};
        int m_denomerator{};

    public:
        // default constructor
        Fraction()
        {
            m_numerator = 0;
            m_denomerator = 1;
        }

        Fraction(int, int);     // ignore this for now (for parameterized constructor)

        // setter

        int getNumerator() { return m_numerator; }
        int getDenomerator() { return m_denomerator; }
        double getValue() { return static_cast<double>(m_numerator)/m_denomerator; }
    };

    void main_use_default()
    {
        Fraction frac{};
        std::cout << frac.getNumerator() << '/' << frac.getDenomerator() << '\n';   // prints 0/1
    }
}

// when the Fraction frac{} executes, the default constructor gets called.
// although technically incorrect, this is often called [default initialization].




/*---------------------------------------------------------------------------------------
                    ============[ value-initialization ]============
---------------------------------------------------------------------------------------*/

/*
  - in the above program, we initialized our class object using value-initialization
    ---------------------------------------------------
        Fraction frac{};    // value-initialization
    ---------------------------------------------------

  - we can also initialize our class objects using default-initialization
    -----------------------------------------------------
        Fraction frac;      // default-initialization
    -----------------------------------------------------

  - for the most part, default and list-initialization of a class object result in the same
    outcome: the default constructor is called.
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    favor value-initialization over default-initializatoin for class objects.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
==========[ direct- and list-initialization using constructors with parameters ]=========
---------------------------------------------------------------------------------------*/

// constructors can also be declared with parameters

namespace constructor
{
    // see the rest of the definition above

    // constructor with two parameters, one parameter having a default value
    Fraction::Fraction(int numerator, int denominator=1)
    {
        assert(denominator != 0 && "denominator can't be 0 !");
        m_numerator = numerator;
        m_denomerator = denominator;
    }

    void main_use_parameterized()
    {
        // call
        Fraction fiveThirds{ 5, 3 };        // list initialization,        calls Fraction(int, int)
        std::cout << fiveThirds.getValue() << '\n';

        Fraction threeQuarters(3, 4);       // direct initialization, also calls Fraction(int, int)
        std::cout << threeQuarters.getValue() << '\n';
    }
}

/*
  - prefer list initialization over direct initialization.

  - we'll discover reasons to use direct initialization when calling constructors later in
    the tutorials.
  - there is another special constructor that might make brace initialization do something
    different, int that case we have to use direct initialization.
*/


// [ best practice ]
/*---------------------------------------------------------------------------------------
    favor brace initialization to initialize class objects
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
        ============[ copy initialization using equals with classes ]============
---------------------------------------------------------------------------------------*/

/*
  - much like with fundamental variables, it's also possible to initialize classes using
    copy initialization.
  - however, this way of initialization may be less efficient.
  - more in future chapter.
*/

void copy_initialization()
{
    using constructor::Fraction;

    // copy-initialization
    Fraction six = Fraction{ 6 };       // calls Fraction(int, int)
}




/*---------------------------------------------------------------------------------------
         ============[ an implicitly generated default constructor ]============
---------------------------------------------------------------------------------------*/

/*
  - if your class has no constructors, C++ will automatically generate a public default constructor
    for you.
  - this is sometimes called an [implicit constructor].
*/

namespace implicit_constructor
{
    class Date
    {
    private:
        int m_year{ 1900 };
        int m_month{ 1 };
        int m_day{ 1 };

        // no user provided constructors, the compiler generates a default constructor
    };

    void main()
    {
        Date date{};
    }
}

/*
  - the Date class has no constructors, therefore, the compiler will generate a default
    constructor that allows us to create a Date object without arguments.

  - there is another way: you can use the default keyword to tell the compiler to create
    a default constructor for us anyway.
*/

namespace implicit_constructor
{
    class Datee
    {
    private:
        int m_year{ 1900 };
        int m_month{ 1 };
        int m_day{ 1 };

        Datee() = default;

        Datee(int year, int month, int day)
        {
            m_year = year;
            m_month = month;
            m_day = day;
        }
    };
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    if you have constructors in your [class] and need a default constructor that does
    nothing, use [= default].
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
               ============[ classes containing class members ]============
---------------------------------------------------------------------------------------*/

/*
  - a [class] may contain other class objects as member variables.
  - by default, when the outer class is constructed, the member variables will have their
    default constructors called.
  - this happens before the body of the constructor executes.
*/

namespace class_contain_class
{
    class A
    {
    public:
        A() { std::cout << "A\n"; }
    };

    class B
    {
    private:
        A m_a{};
    
    public:
        B() { std::cout << "B\n"; }
    };

    void main()
    {
        B b;    // calls A() then B()
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ constructor notes ]============
---------------------------------------------------------------------------------------*/

/*
  - many new programmers are confused about whether constructors create the objects or not.
  - they do not.
  - the compiler sets up the memory allocation for the object prior to the constructor call.
*/




//=======================================================================================

#include <string>
#include <string_view>

namespace quiz
{
    /*
      - write a class named [Ball].
      - ball should have two private member variables with default value: m_color ("black")
        and m_radius (10.0).
      - [Ball] should provide constructors to set only m_color, set only m_radius, set both
        or set neither value.
      - also write a function to print out the color and raius of the ball.
    */

    class Ball
    {
    private:
        std::string m_color{ "black" };
        float m_radius{ 10.0 };

    public:
        Ball(std::string_view color = "black", float radius = 10.0f)
        {
            m_color = color;
            m_radius = radius;
        }

        Ball(float radius)
        {
            m_radius = radius;
        }

        void print()
        {
            std::cout << "color: " << m_color << ", radius: " << m_radius << '\n';
        }
    };

    void main()
    {
        Ball def{};
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
    constructor::main_use_default();
    constructor::main_use_parameterized();

    class_contain_class::main();

    quiz::main();

    return 0;
}