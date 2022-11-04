#include <iostream>
#include <string>

// #define USE_ORIGINAL_CONSTRUCTOR


/*---------------------------------------------------------------------------------------
                               ============[ ]============
---------------------------------------------------------------------------------------*/

/*
  - when instantiating a function template for a given type, the compiler stencils out a
    copy of the templated function and replaces the template type parameters with the
    actual types used in the variable declaration.
  - this means a particular function will have the same implementation details for each
    instantiated type.
  - occasionally there are cases where it is useful to implement a templated function
    slightly different for a specific data type.
  - [template specialization] is one way to accomplish this.
*/

namespace example
{
    template <typename T>
    class Storage
    {
    private:
        T m_value{};

    public:
        Storage(T value)
            : m_value{ value }
        {
        }

        ~Storage() = default;

        void print()
        {
            std::cout << m_value << '\n';
        }
    };

    // we want double type to print differently (using scientific notation)
    template <>     // tell the compiler that this is a template function
    void Storage<double>::print()
    {
        std::cout << std::scientific << m_value << '\n';
    }


    void main()
    {
        // Define some storage units
        Storage<int> nValue { 5 };
        Storage<double> dValue { 6.7 };

        // Print out some values
        nValue.print();
        dValue.print();
    }
}




/*---------------------------------------------------------------------------------------
                      ============[ another example ]============
---------------------------------------------------------------------------------------*/

// consider what happens if we tr to use our templated Storage class with datatype const
// char*, the constructor for Storage<char*> looks like this:

#ifdef USE_ORIGINAL_CONSTRUCTOR
namespace example
{
    template<>
    Storage<char*>::Storage(char* value)
        : m_value{ value }                  // this is just a shallow copy!
    {
    }
}
#endif

// the above code is just a shallow copy!
// fortunately we can fix this problem using template specialization

#ifndef USE_ORIGINAL_CONSTRUCTOR
namespace example
{
    // deep copy
    template <>
    Storage<char*>::Storage(char* value)
    {
        if (!value)
            return;

        // figure out how long the string in value is
        int length{ 0 };
        while (value[length] != '\0')
            ++length;
        ++length;           // +1 to account for null terminator

        // allocate memory to hold the value string
        m_value = new char[length];

        //copy the actual value string into the m_value memory
        for (int count{ 0 }; count < length; ++count)
            m_value[count] = value[count];
    }

    // we also need to explicitly define the destructor
    template <>
    Storage<char*>::~Storage()
    {
        delete[] m_value;
    }


    void main_char_ptr()
    {
        // Dynamically allocate a temporary string
        std::string s;

        // Ask user for their name
        std::cout << "Enter your name: ";
        std::cin >> s;

        // Store the name
        Storage<char*> storage(s.data());

        storage.print(); // Prints our name

        s.clear(); // clear the std::string

        storage.print(); // Prints our name
    }
}
#endif




//=======================================================================================

int main()
{
    example::main();
    example::main_char_ptr();

    return 0;
}