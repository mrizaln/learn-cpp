#include <iostream>
#include <cassert>


/*---------------------------------------------------------------------------------------
                      ============[ shallow copying ]============
---------------------------------------------------------------------------------------*/

/*
  - the default copy constructor and default assignment operators C++ provides use a copying
    method called memberwise copy (also known as [shallow copy]).
  - this means that C++ copies each member of the class individually.
  - when classes are simple (e.g. do not contain any dynamically allocated memory), this
    works very well.

  - however, when designing classes that handle dynamically allocated memory, memberwise
    (shallow) copying can get us in a lot of trouble.
  - this is because shallow copies of a pointer just copy the address of the pointer -- it
    does not allocate any memory or copy the contents being pointed to.
*/




/*---------------------------------------------------------------------------------------
                      ============[ deep copying ]============
---------------------------------------------------------------------------------------*/

/*
  - on answer to this problem is to do a deep copy on any non-null pointers being copied.
  - a [deep copy] allocates memory for the copy and then copies the actual value, so that
    the copy lives in distinc memory from the source.
  - this way, the copy and source are distinct and will not affect each other in any way.
  - doing deep copies requires that we write our own copy constructor and overloaded assignment
    operators.
*/

#include <cstring>      // for std::strlen()

namespace deep_copy
{
    class MyString
    {
    private:
        char* m_data{};
        int m_length{};

    public:
        // default constructor
        MyString(const char* source = "")
        {
            assert(source);     // make sure source isn't a null string

            // find the lenght of the string (+1 character for a terminator)
            m_length = std::strlen(source) + 1;

            // allocate a buffer equal to this length
            m_data = new char[m_length];

            // copy the parameter string into our internal buffer
            for (int i{ 0 }; i < m_length; ++i)
                m_data[i] = source[i];
        }

        void deepCopy(const MyString& source)
        {
            // first we need to deallocate any value that this string is holding
            delete[] m_data;

            m_length = source.m_length;

            // m_data is a pointer, so we need to deep copy it if it is non-null
            if (source.m_data)
            {
                // aloocate memory for our copy
                m_data = new char[m_length];

                // do the copy
                for (int i{ 0 }; i < m_length; ++i)
                    m_data[i] = source.m_data[i];
            }
            else
                m_data = nullptr;
        }

        // copy constructor
        MyString(const MyString& source)
        {
            deepCopy(source);
        }

        // destructor
        ~MyString()
        {
            delete[] m_data;
        }

        char* getString() { return m_data; }
        int getLength() { return m_length; }

        // assignment operator
        MyString& operator=(const MyString& source)
        {
            // check for self-assignment
            if (this != &source)
                deepCopy(source);       // do the deep copy
            return *this;
        }
    };
}

// a better solution is probably using copy-and-swap idiom