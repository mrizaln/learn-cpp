//========[ defining your own namespace ]========
// namespace identifiers are typically non-capitalized

#include <iostream>

namespace foo   // define a namespace named foo
{
    // this doSomething() belongs to namespace foo
    int doSomething(int x, int y)
    {
        return x + y;
    }
}

namespace goo
{
    // this doSomething() belongs to namespace goo
    int doSomething(int x, int y)
    {
        return x - y;
    }
}


//========[ accessing a namespace with the scope resolution operator (::)]========

void access()
{
    std::cout << foo::doSomething(4, 3) << '\n';
    std::cout << goo::doSomething(4, 3) << '\n';
}


// =======[ identifier resolution from within a namespace ]========

void print()    // this print() lives in the global namespace
{
    std::cout << " there\n";
}

namespace hoo
{
    void print()    // this print() lives in the hoo namespace
    {
        std::cout << "Hello";
    }

    void printHelloThere()
    {
        print();    // calls print() in hoo namespace
        ::print();  // calls print() in global namespace
    }
}


//========[ multiple namespace blocks are allowed ]========
// it is legal to declare namespace block in multiple locations (either accross multiole files, 
// or multiple places within the same file)
// all declarations within the namespace are considered part of the namespace

namespace basicMath
{
    constexpr double pi {3.14};
}

namespace basicMath
{
    // the constant e is also part of namespace basicMath
    constexpr double e { 2.7 };
}


//========[ nested namespaces ]========
// namespaces can be nested inside other namespaces, for example

namespace hoo::joo  // koo is a namespace inside the joo namespace (C++17 style)
{
    int add(int x, int y)
    {
        return x + y;
    }
}

void nested_namespace()
{
    std::cout << hoo::joo::add(7, 2) << '\n';
}


//========[ namespace aliases ]========
// shorten a long suquence of namespaces into something shorter

namespace hoo::joo
{
    int mul(int x, int y)
    {
        return x * y;
    }
}

void namespace_alias()
{
    namespace active = hoo::joo;            // active now refers to hoo::koo
    std::cout << active::mul(3, 2) << '\n'; // this is really hoo::joo::add()
}


//========[ when you should use namespaces ]========
// in applications, namespaces can be used to separate application-specific code from code
// that might be reusable later (e.g. math functions)


//=======================================================================================

int main()
{
    access();
    hoo::printHelloThere();
    std::cout << basicMath::pi << '\n';
    std::cout << basicMath::e << '\n';
    nested_namespace();
    namespace_alias();

    return 0;
}
