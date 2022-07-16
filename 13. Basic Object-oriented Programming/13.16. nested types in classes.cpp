#include <iostream>


/*---------------------------------------------------------------------------------------
                      ============[ nesting types ]============
---------------------------------------------------------------------------------------*/

// much like functions and data can be members of a class, in C++, types can also be defined
// (nested) inside of a class

namespace nesting_types
{
    class Fruit
    {
    public:
        enum FruitType
        {
            apple,
            banana,
            cheery
        };
    
    private:
        FruitType m_type{};
        int m_percentageEaten{ 0 };

    public:
        Fruit(FruitType type)
            : m_type{ type }
        {
        }

        FruitType getType() const { return m_type; }
        int getPercentageEaten() const { return m_percentageEaten; }
    };

    void main()
    {
        Fruit apple{ Fruit::apple };

        if (apple.getType() == Fruit::apple)
            std::cout << "I am an apple";
        else
            std::cout << "I an not an apple";
    }
}

/*
  - in the above, we nested an enum inside a class.
  - classes essentially act as a namespace for any nested types, much as enum classes do.

  - although enumerations are probably the most common type that is nested inside a class,
    C++ will let you define other types within a class, such as typedefs, type aliases, and
    even other classes.
*/