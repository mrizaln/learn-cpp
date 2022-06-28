#include <iostream>


/*---------------------------------------------------------------------------------------
         ============[ constructors with overlapping functionality ]============
---------------------------------------------------------------------------------------*/

/*
  - when you instantiate a new object, the object's constructor is called implicitly.
  - it is not uncommon to have a class with multiple constructors that have overlapping
    functionality
*/




/*---------------------------------------------------------------------------------------
              ============[ the obvious solution doesn't work ]============
---------------------------------------------------------------------------------------*/

namespace obvious_solution
{
    class Foo
    {
    public:
        Foo()
        {
            // do to do A
        }

        Foo(int value)
        {
            Foo();      // use above constructor to do A (doesn't work)
            // code to do B
        }
    };
}

/*
  - however, if you try to have one constructor call another constructor in this way, it
    will compile and may be cause a warning, but it will not work as you expect.
  - what's happening is that Foo() instantiates a new Foo object, which is immediately
    discarded, because it's not stored in a variable.
*/




/*---------------------------------------------------------------------------------------
                   ============[ delegating constructors ]============
---------------------------------------------------------------------------------------*/

/*
  - constructors are allowd to call other constructros from the same class.
  - this process is called [delegating constructors] (or constructor chaining).

  - to have one constructor call another, simply call the constructor in the member initializer
    list.
  - this is one case where calling another constructor directly is acceptable.
*/

namespace delegating_constructor
{
    class Foo
    {
    private:

    public:
        Foo()
        {
            // code to do A
        }

        Foo(int value) : Foo{}      // use Foo() default constructor to do A
        {
            // code to do B
        }
    };

    class Employee
    {
    private:
        int m_id{};
        std::string m_name{};

    public:
        Employee(int id=0, std::string_view name="")
            : m_id{ id }
            , m_name{ name }
        {
            std::cout << "Employee " << m_name << " created.\n";
        }

        // use a delegating constructor to minimize redundant code
        Employee(std::string_view name) : Employee{ 0, name }
        { }
    };
}

/*
  - a few additional notws about delegating constructors:
     1. a constructor that delegates to another constructor is not allowed to do any member
        initialization itself.
     2. it's possible for one constructor to delegate to another constructor, which delegates
        back to the first constructor (this forms infinite loop).
*/


// [ best practice ]
/*---------------------------------------------------------------------------------------
    if you have multiple constructors that have the same functionality, use delegating
    constructors to avoid duplicate code.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
          ============[ using a normal member function for setup ]============
---------------------------------------------------------------------------------------*/

// because a constructor can only initialize or delegate, this leads to a challenge if our
// default constructor does some common initialization

// consider the following:

namespace using_a_normal_member_function_for_setup
{
    class Foo
    {
    private:
        const int m_value{ 0 };

    public:
        Foo()
        {
            // code to do some common setup tasks (e.g. open a file or database)
        }

        Foo(int value) : m_value{ value }   // we need initialize m_value since it's const
        {
            // how do we get to the common initialization code in Foo() ?
        }
    };
}

// constructors are allowed to call non-constructor member functions (and non-member functions),
// so the solution is to use a normlal member function to handle the common setup tasks.

namespace using_a_normal_member_function_for_setup
{
    class Bar
    {
    private:
        const int m_value{ 0 };

        void setup()
        {
            // code to do some common setup tasks (e.g. open a file or database)
            std::cout << "Setting this up...\n";
        }

    public:
        Bar()
        {
            setup();
        }

        Bar(int value) : m_value{ value }
        {
            setup();
        }
    };
}




/*---------------------------------------------------------------------------------------
                      ============[ resetting a class ]============
---------------------------------------------------------------------------------------*/

/*
  - you may find yourself in the situation where you want to write amember function (e.g.
    named reset()) to reset a class back to the default state.

  - because you probably already have a default constructor that initializes you members
    to the appropiate default values, you may be tempted to try to call the default constructor
    directly from reser().
  - however, trying to call a constructor directly will generally result in unexpected behavior
    as we have shown above, so that won't work.

  - however, if the class is assignable (meaning it has an accessible assinment operator),
    we can create a new class object, and then use assignment to overwrite the values in
    the object we want to reset.
*/

namespace resetting_a_class
{
    class Foo
    {
    private:
        int m_a{ 5 };
        int m_b{ 6 };

    public:
        Foo() = default;

        Foo(int a, int b)
            : m_a{ a }, m_b{ b }
        { }

        void print()
        {
            std::cout << m_a << ' ' << m_b << '\n';
        }

        void reset()
        {
            // consider this a bit of magic for now
            *this = Foo();  // create a new object, then use assignment to overwrite our
                            // implicit object
        }
    };

    void main()
    {
        Foo a{ 1, 2 };
        a.print();

        a.reset();
        a.print();
    }
}




//=======================================================================================

int main()
{
    resetting_a_class::main();

    return 0;
}