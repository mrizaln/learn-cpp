#include <iostream>


/*
  - a [destructor] is another special kind of class member function that is executed when
    an object if that class is destroyed.
  - destructors are designed to help clean up.

  - when an object goes out of scope normally, or a dynamically allocated object is explicitly
    deleted using the delete keyword, the class destructor is automatically called to do any
    necessary clean up before the object is removed from memory.
*/




/*---------------------------------------------------------------------------------------
                    ============[ destructor naming ]============
---------------------------------------------------------------------------------------*/

/*
  - like constructors, destructors have specific naming rules:
    1.  the destructor must have the same name as the class, preceded by a tilde (~)
    2.  the destructor can not take arguments
    3.  the destructor has no return type.

  - a class can only have a single destructor.
*/




/*---------------------------------------------------------------------------------------
                    ============[ a destructor example ]============
---------------------------------------------------------------------------------------*/

#include <cassert>
#include <cstddef>

namespace example
{
    class IntArray
    {
    private:
        int* m_array{};
        int m_length{};

    public:
        IntArray(int length)    // constructor
        {
            assert (length > 0);

            m_array = new int[static_cast<std::size_t>(length)]{};
            m_length = length;
        }

        ~IntArray()     // destructor
        {
            delete[] m_array;
        }

        void setValue(int index, int value) { m_array[index] = value; }
        int getValue(int index) { return m_array[index]; }

        int getLength() { return m_length; }
    };

    void main()
    {
        IntArray ar(10);        // allocate 10 integers
        for (int count{ 0 }; count < ar.getLength(); ++count)
            ar.setValue(count, count+1);
        
        std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';
    } // ar is destroyed here
}




/*---------------------------------------------------------------------------------------
        ============[ RAII (resource acquisition is initialization) ]============
---------------------------------------------------------------------------------------*/

/*
  - RAII is a programming technique whereby resource use is tied to the lifetime of the
    objects with automatic duration (e.g. non-dynamically allocated objects).
  - in C++, RAII is implemented via classes with constructors and destructors.

  - a resource is typically acquired in the object's constructor.
  - that resource can then be used while the object is alive.
  - the resource is released in the destructor, when the object is destriyed.
  - the advantage of RAII is that it helps prevent resource leaks as all resource-holding
    objects are cleaned up automatically.
*/




/*---------------------------------------------------------------------------------------
              ============[ a warning about the exit() function ]============
---------------------------------------------------------------------------------------*/

/*
  - note that if you use exit() function, your program will terminate and no destructors
    will be called.
  - be wary if you're relying on your destructors to do necessary cleanup work.
*/


//=======================================================================================

int main()
{
    example::main();

    return 0;
}