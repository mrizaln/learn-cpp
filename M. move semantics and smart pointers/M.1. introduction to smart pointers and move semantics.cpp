/*------------------------------------------------------------------------------
              ============[ smart pointer ]============
------------------------------------------------------------------------------*/

// sometimes we forgot to deallocate a dynamically allocated memory.
// smart pointer can help

// a [smart pointer] is a composition class that is designed to manage dynamically
// allocated memory and ensure that memory gets deleted when the smart pointer object
// goes out of scope.

// more on this at later chapter




/*------------------------------------------------------------------------------
                  ============[ move semantics ]============
------------------------------------------------------------------------------*/

// [move semantics] means the class will transfer ownership of the object rather
// than making a copy.

#include <iostream>

namespace using_move_semantics
{
    template <typename T>
    class Auto_ptr
    {
    private:
        T* m_ptr{};

    public:
        Auto_ptr(T* ptr = nullptr)
            :m_ptr{ ptr }
        {
        }

        ~Auto_ptr()
        {
            delete m_ptr;
        }

        // a copy constructor that implements move semantics
        Auto_ptr(Auto_ptr& a)
        {
            m_ptr = a.m_ptr;        // transfer our pointer
            a.m_ptr = nullptr;      // make sure the source no longer owns the pointer
        }

        // an assignment operator that implements move semantics
        Auto_ptr& operator=(Auto_ptr& a)
        {
            if (&a == this)
                return *this;

            delete m_ptr;
            m_ptr = a.m_ptr;
            a.m_ptr = nullptr;
            return *this;
        }

        T& operator*() const { return *m_ptr; };
        T* operator->() const { return m_ptr; };
        bool isNull() const { return m_ptr == nullptr; };
    };


    class Resource
    {
        public:
            Resource() { std::cout << "Resource acquired\n"; }
            ~Resource() { std::cout << "Resource destroyed\n"; }
    };

    void main()
    {
        Auto_ptr<Resource> res1{ new Resource() };
        Auto_ptr<Resource> res2;                    // start as nullptr

        std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
        std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

        res2 = res1;

        std::cout << "Ownership transferred\n";

        std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
        std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");
    }
}




//==============================================================================

int main()
{
    using_move_semantics::main();

    return 0;
}
