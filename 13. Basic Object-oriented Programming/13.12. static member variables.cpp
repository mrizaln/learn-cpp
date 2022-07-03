#include <iostream>
#include <array>


/*---------------------------------------------------------------------------------------
                   ============[ static member variables ]============
---------------------------------------------------------------------------------------*/

// unlike normal member variables, static member variables are shared by all objects of the
// class.

namespace static_member_variables
{
    class Something
    {
    public:
        static int s_value;
    };

    int Something::s_value{ 1 };

    void main()
    {
        Something first;
        Something second;

        first.s_value = 2;

        std::cout << first.s_value << '\n';
        std::cout << second.s_value << '\n';
    }
}




/*---------------------------------------------------------------------------------------
     ============[ static members are not associated with class objects ]===========
---------------------------------------------------------------------------------------*/

/*
  - static members exist even if no objects of the class have been instantiated.
  - much like global variables, they are created when the program starts, and destroyed
    when the program ends.
  - it is better to think of static members as belonging to the class itself, not to the
    class.
  - it can be accessed directly using the class name and the scope resolution operator.
*/

namespace static_member_are_not_associated_with_class_objects
{
    class Something
    {
    public:
        static int s_value;
    };

    int Something::s_value{ 1 };    // defines the static member variable (explanation on the next section)

    void main()
    {
        Something::s_value = 2;
        std::cout << Something::s_value << '\n';
    }
}




/*---------------------------------------------------------------------------------------
      ============[ defining and initializing static member variables ]============
---------------------------------------------------------------------------------------*/

/*
  - when we declare a static member variable inside a class, we're telling the compiler about
    the existence of a static member variable, but not actually defining it.
  - because statis member variables are not part of the individual class objects, you must
    explicitly define the static member outside the class.

  - note that static member definition is not subject to access controls: you can define and
    initialize the variable even if it's declared as private (or protected) in the class.

  - if the class is defined in a .h file, the static member definition is usually placed in
    the associated code file for the class.
  - if the class is defined in a .cpp file, the static member definition is usually placed
    directly underneath the class.
  - do not put the static member definition in a header file: much like a global variable,
    if that header file gets included more than once, you'll end up with multiple definitions,
    which will cause a linker error.
*/




/*---------------------------------------------------------------------------------------
      ============[ inline initialization of static member variables ]============
---------------------------------------------------------------------------------------*/

namespace inline_initialization_of_static_member_variables
{
    class Whatever
    {
    public:
        // static const integral type or const enum can be initialized inline
        static const int s_value_int{ 4 };

        // static constexpr members can be initialized inside the class definition
        static constexpr double s_value_double{ 2.2 };
        static constexpr std::array<int, 3> s_array{ 1, 2, 3 };     // even works for classes that support constexpr initialization

        // as of C++17, we can also initialize non-const static members in the class definition
        // by declaring them inline
        static inline int s_value_inline{ 4 };
    };
}




/*---------------------------------------------------------------------------------------
            ============[ an exmple of static member variables ]============
---------------------------------------------------------------------------------------*/

// why use static variables inside classes?
// on useful example is to assigne a unique ID to every instance of the class.

namespace example_of_static_member_variables
{
    class Something
    {
    private:
        static inline int s_idGenerator{ 1 };   // C++17
        // static int s_idGenerator;            // C++14 or older
        int m_id{};

    public:
        Something()
            : m_id{ s_idGenerator++ }   // grab the next value from the id generator
        {}

        int getID() const { return m_id; }
    };

    // Something::s_idGenerator{ 1 };   // C++14 or older

    void main()
    {
        Something first{};
        Something second{};
        Something third{};

        std::cout << first.getID() << '\n';
        std::cout << second.getID() << '\n';
        std::cout << third.getID() << '\n';
    }
}



//=======================================================================================

int main()
{
    static_member_variables::main();
    static_member_are_not_associated_with_class_objects::main();
    example_of_static_member_variables::main();

    return 0;
}