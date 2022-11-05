#include <iostream>


/*---------------------------------------------------------------------------------------
                            ============[ ]============
---------------------------------------------------------------------------------------*/

namespace example
{
    template <typename T>
    class Storage
    {
    private:
        T m_value;
    
    public:
        Storage(T value)
            : m_value{ value }
        {
        }

        ~Storage() = default;

        void print() const
        {
            std::cout << m_value << '\n';
        }
    };
}

// above will have problems when parameter T was of type char* because of the shallow copy
// that takes place in the constructor.

namespace example
{
    // the fix is to use partial template specialization
    template <typename T>
    class Storage<T*>
    {
    private:
        T* m_value;

    public:
        Storage(T* value)       // for pointer type T
            : m_value{ new T{ *value }}     // this copies a single value, not an array
        {
        }

        ~Storage()
        {
            delete m_value;     // scalar delete
        }

        void print() const
        {
            std::cout << *m_value << '\n';
        }
    };

    
    void main()
    {
        // Declare a non-pointer Storage to show it works
        Storage<int> myint { 5 };
        myint.print();

        // Declare a pointer Storage to show it works
        int x { 7 };
        Storage<int*> myintptr { &x };

        // Let's show that myintptr is separate from x.
        // If we change x, myintptr should not change
        x = 9;
        myintptr.print();
    }
}




//=======================================================================================

int main()
{
    example::main();

    return 0;
}