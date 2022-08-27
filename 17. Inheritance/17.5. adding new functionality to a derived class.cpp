#include <iostream>


class Base
{
protected:
    int m_value{};

public:
    Base(int value)
        : m_value{ value }
    {
    }

    void identify() const { std::cout << "I am a Base\n"; }
};

class Derived: public Base
{
public:
    Derived(int value)
        : Base{ value }
    {
    }

    int getValue() const { return m_value; }
};

int main()
{
    Derived derived{ 5 };
    std::cout << derived.getValue() << '\n';

    Base base{ 4 };
    // std::cout << base.getValue() << '\n';        // can't (getValue() is member of Derived)
}