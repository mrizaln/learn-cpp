#include <iostream>


/*
  - in certain cases, we need a variable only temporarily.

  - an [anonymous object] is essentially a value that has no name.
  - because they have no name, there's no way to refer to them beyond the point where they
    are created.
*/

namespace anonymous_objects
{
    int add(int x, int y)
    {
        return x + y;       // anonymous object
    }

    void printValue(int value)
    {
        std::cout << value;
    }

    void main()
    {
        int x{ 5 };             // not using anonymous object
        int y{ 6 };             // ^^
        int z{ add(x, y) };     // ^^
        printValue(z);

        printValue(add(5, 6));      // using anonymous object
    }
}


/*---------------------------------------------------------------------------------------
                   ============[ anonymous class objects ]============
---------------------------------------------------------------------------------------*/

// it is possible to construct anonymous objects of our own class types

namespace anonymous_class_objects
{
    class Cents
    {
    private:
        int m_cents{};

    public:
        Cents(int cents)
            : m_cents{ cents }
        {
        }

        int getCents() const { return m_cents; }
    };

    Cents add(const Cents& c1, const Cents& c2)
    {
        // list initialization looks at the return type of the function and creates the correct object accordingly
        return { c1.getCents() + c2.getCents() };
    }

    void main()
    {
        // print anonymous Cents value
        std::cout << "I have "
                  << add(Cents{ 6 }, Cents{ 8 }).getCents()
                  << " cents.\n";
    }
}




//=======================================================================================

int main()
{
    anonymous_objects::main();
    anonymous_class_objects::main();
}