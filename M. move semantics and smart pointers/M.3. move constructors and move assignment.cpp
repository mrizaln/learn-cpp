/*------------------------------------------------------------------------------
       ============[ move constructors and move assignemnt ]============
------------------------------------------------------------------------------*/

/*
  - C++11 defines two new functions in service of move semantics: a move constructor,
    and a move assignment operator.
  - the goal of the move constructor and move assignment is to move ownership of
    the resources from one object to another.

  - defining move constructor and move assignment work analogously to their copy
    counterparts.
  - however, the move constructor and move assignment use non-const r-value reference
    parameters.
*/

#include <iostream>
#include <utility>

namespace example
{
    template <typename T>
    class Auto_ptr
    {
    private:
        T* m_ptr{};

    public:
        Auto_ptr(T* ptr = nullptr)
            : m_ptr{ ptr }
        {
            std::cout << "default ctor called\n";
        }

        ~Auto_ptr()
        {
            delete m_ptr;

            std::cout << "dtor called, it contains  : " << (m_ptr ? (void*)m_ptr : (void*)0) << '\n';
        }

        // copy constructor
        Auto_ptr(const Auto_ptr& other) noexcept
            : m_ptr{ new T }
        {
            *m_ptr = *other.m_ptr;
            std::cout << "copy ctor called\n";
        }

        // move constructor
        Auto_ptr(Auto_ptr&& other) noexcept
            : Auto_ptr{}        // initialize via default constructor (C++11 only)
        {
            swap(*this, other);
            std::cout << "move ctor called\n";
        }

        // copy assignment & move assignment (?)
        Auto_ptr& operator=(Auto_ptr other) noexcept    // shallow copy
        {
            swap(*this, other);                         // then swap
            return *this;

            std::cout << "assignment called\n";
        }

        // move assignment
        // Auto_ptr& operator=(Auto_ptr&& other)
        // {
        //     if (&other == this)
        //         return *this;

        //     delete m_ptr;

        //     m_ptr = other.m_ptr;
        //     other.m_ptr = nullptr;

        //     return *this;
        // }

        // see: https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
        //      https://stackoverflow.com/questions/37915088/a-better-way-to-implement-copy-and-swap-idiom-in-c11
        friend void swap(Auto_ptr& left, Auto_ptr& right)
        {
            // enable ADL
            using std::swap;

            swap(left.m_ptr, right.m_ptr);
        }

        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }
        bool isNull() const { return m_ptr == nullptr; }
    };

    class Resource
    {
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
    };

    Auto_ptr<Resource> generateResource()
    {
        Auto_ptr<Resource> res{new Resource};
        return res;         // this return value will invoke the move constructor
    }

    void main()
    {
        Auto_ptr<Resource> mainres{ generateResource() };
        std::cout << ">> mainres (valid)        : " << &*mainres<< '\n';

        std::cout << "\n> performing copy\n";
        Auto_ptr<Resource> copyres;
        std::cout << ">> copyres (uninitialized): " << &*copyres << '\n';

        copyres = mainres;
        std::cout << ">> mainres (still valid)  : " << &*mainres << '\n';
        std::cout << ">> copyres (valid)        : " << &*copyres << '\n';

        std::cout << "\n> performing move\n";
        auto moveres = std::move(copyres);

        std::cout << ">> copyres (invalidated)  : " << &*copyres << '\n';
        std::cout << ">> moveres (valid)        : " << &*moveres << '\n';

        std::cout << "\n> performing move\n";
        moveres = std::move(mainres);
        std::cout << ">> mainres (invalidated)  : " << &*mainres << '\n';
        std::cout << ">> moveres (valid)        : " << &*moveres << '\n';

        std::cout << "\n> string: \n";
        Auto_ptr<std::string> str{ new std::string("Hello") };
        auto strr = std::move(str);

        std::cout << '\n';
    }
}




/*------------------------------------------------------------------------------
    ============[ implicit move constructor and move assignment ]============
------------------------------------------------------------------------------*/

/*
  - the compiler will create an implicit move constructor and move assignment operator
    if all of the following are true:
      > there are no user-declared copy constructors or copy assignment operators.
      > there are no user-declared move constructors or move assignment operators.
      > there is no user-declared destructor.
*/




/*------------------------------------------------------------------------------
                 ============[ another example ]============
------------------------------------------------------------------------------*/

#include <chrono> // for std::chrono functions
#include <iostream>

namespace another_example
{
    template <typename T>
    class DynamicArray
    {
    private:
        T* m_array;
        int m_length;

    public:
        DynamicArray(int length)
            : m_array(new T[length]), m_length(length)
        {
        }

        ~DynamicArray()
        {
            delete[] m_array;
        }

        // Copy constructor
        DynamicArray(const DynamicArray &arr)
            : m_length(arr.m_length)
        {
            m_array = new T[m_length];
            for (int i = 0; i < m_length; ++i)
                m_array[i] = arr.m_array[i];
        }

        // Copy assignment
        DynamicArray& operator=(const DynamicArray &arr)
        {
            if (&arr == this)
                return *this;

            delete[] m_array;

            m_length = arr.m_length;
            m_array = new T[m_length];

            for (int i = 0; i < m_length; ++i)
                m_array[i] = arr.m_array[i];

            return *this;
        }

        // Move constructor
        DynamicArray(DynamicArray &&arr) noexcept
            :  m_array(arr.m_array), m_length(arr.m_length)
        {
            arr.m_length = 0;
            arr.m_array = nullptr;
        }

        // Move assignment
        DynamicArray& operator=(DynamicArray &&arr) noexcept
        {
            if (&arr == this)
                return *this;

            delete[] m_array;

            m_length = arr.m_length;
            m_array = arr.m_array;
            arr.m_length = 0;
            arr.m_array = nullptr;

            return *this;
        }

        int getLength() const { return m_length; }
        T& operator[](int index) { return m_array[index]; }
        const T& operator[](int index) const { return m_array[index]; }

    };

    class Timer
    {
    private:
        // Type aliases to make accessing nested type easier
        using Clock = std::chrono::high_resolution_clock;
        using Second = std::chrono::duration<double, std::ratio<1> >;

        std::chrono::time_point<Clock> m_beg { Clock::now() };

    public:
        void reset()
        {
            m_beg = Clock::now();
        }

        double elapsed() const
        {
            return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
        }
    };

    // Return a copy of arr with all of the values doubled
    DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr)
    {
        DynamicArray<int> dbl(arr.getLength());
        for (int i = 0; i < arr.getLength(); ++i)
            dbl[i] = arr[i] * 2;

        return dbl;
    }

    void main()
    {
        Timer t;

        DynamicArray<int> arr(1000000);

        for (int i = 0; i < arr.getLength(); i++)
            arr[i] = i;

        arr = cloneArrayAndDouble(arr);
        std::cout << "copy: " << t.elapsed() << " s\n";

        t.reset();
        arr = std::move(cloneArrayAndDouble(arr));
        std::cout << "move: " << t.elapsed() << " s\n";

    }
}



//==============================================================================

int main()
{
    example::main();
    // another_example::main();

    return 0;
}
