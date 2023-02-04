// to rethrow an exception, simply use the throw keyword from within the catch block
// (with no associated variable), like so

#include <iostream>

class Base
{
public:
    Base() { }
    virtual void print() { std::cout << "Base"; }
};

class Derived : public Base
{
public:
    Derived() { };
    void print() override { std::cout << "Derived"; }
};

int main()
{
    try {
        try {
            throw Derived{};
        } catch (Base& b) {
            std::cout << "Caught Base b, which is actually a ";
            b.print();
            std::cout << '\n';
            throw;    //  <---------------------------------------------- here
        }
    } catch (Base& b) {
        std::cout << "Caught Base b, which is actually a ";
        b.print();
        std::cout << '\n';
    }
    return 0;
}
