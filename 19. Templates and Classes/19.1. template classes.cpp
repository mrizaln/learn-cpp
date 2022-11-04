#include <iostream>
#include <cassert>


/*---------------------------------------------------------------------------------------
              ============[ templates and container classes ]============
---------------------------------------------------------------------------------------*/

// creating template classes works pretty much identically to creating template functions

namespace template_and_container_class
{
    template <typename T>
    class Array
    {
    private:
        int m_length{};
        T* m_data{}; // changed type to T

    public:
        Array(int length)
        {
            assert(length > 0);
            m_data = new T[length]{}; // allocated an array of objects of type T
            m_length = length;
        }

        Array(const Array&) = delete;
        Array& operator=(const Array&) = delete;

        ~Array()
        {
            delete[] m_data;
        }

        void erase()
        {
            delete[] m_data;
            // We need to make sure we set m_data to 0 here, otherwise it will
            // be left pointing at deallocated memory!
            m_data = nullptr;
            m_length = 0;
        }

        T& operator[](int index) // now returns a T&
        {
            assert(index >= 0 && index < m_length);
            return m_data[index];
        }

        // templated getLength() function defined below
        int getLength() const;
    };

    // member functions defined outside the class need their own template declaration
    template <typename T>
    int Array<T>::getLength() const // note class name is Array<T>, not Array
    {
    return m_length;
    }

    void main()
    {
        Array<int> intArray{ 12 };
        Array<double> doubleArray{ 12 };

        for (int count{ 0 }; count < intArray.getLength(); ++count)
        {
            intArray[count] = count;
            doubleArray[count] = count + 0.5;
        }

        for (int count{ intArray.getLength() - 1 }; count >= 0; --count)
            std::cout << intArray[count] << '\t' << doubleArray[count] << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                ============[ splitting up template classes ]============
---------------------------------------------------------------------------------------*/

/*
  - a template is not a class or a function -- it is a stencil used to create classes or
    functions.
  - as such, it does not work in quite the same way as normal function or classes.
  - in most cases, this isn't much of a issue.
  - however, ther is one area that commonly causes problems for developers.

  - with non-template classes, the common procedure is to put the class definition in a
    header file, and the member function definitions in a similarly named code file.
  - in this way, the source for the class is compiled as a separate project file.
  - however, with templates, this does not work.

    detail: [https://www.learncpp.com/cpp-tutorial/template-classes/]
*/



//=======================================================================================

int main()
{
    template_and_container_class::main();

    return 0;
}