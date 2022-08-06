#include <iostream>
#include <cassert>


// [ description ]
/*---------------------------------------------------------------------------------------
    write your own integer array class named IntArray from scratch. user should pass in
    the size of the array when it is created, and the array should be dynamically
    allocated. use assert statements to guard against bad data.
---------------------------------------------------------------------------------------*/

class IntArray
{
private:
    int m_size{};
    int* m_array{ nullptr };

    void swap(IntArray& x, IntArray& y)
    {
        using std::swap;
        swap(x.m_array, y.m_array);
        swap(x.m_size, y.m_size);
    }

public:
    IntArray(const int size=0)
        : m_size{ size }
    {
        assert(size > 0);
        m_array = new int[m_size]{};
    }

    IntArray(const IntArray& array)
        : IntArray{ array.m_size }
    {
        for (int i{ 0 }; i < m_size; ++i)
            m_array[i] = array.m_array[i];
    }

    ~IntArray()
    {
        delete[] m_array;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_size);
        return m_array[index];
    }

    IntArray& operator=(IntArray array)   // copy first
    {
        if (this == &array)     // self-assignment guard
            return *this;

        swap(*this, array);     // swap resources
        return *this;
    } // array destroyed here

    friend std::ostream& operator<<(std::ostream& out, const IntArray& array);
};

std::ostream& operator<<(std::ostream& out, const IntArray& array)
{
    for (int i{ 0 }; i < array.m_size; ++i)
        out << array.m_array[i] << ' ';
    return out;
}


IntArray fillArray()
{
    IntArray a(5);

    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;

    return a;
}


int main()
{
    IntArray a{ fillArray() };
    std::cout << a << '\n';

    auto& ref{ a };     // we're using this reference to avoid compiler self-assignment errors
    a = ref;

    IntArray b(1);
    b = a;

    std::cout << b << '\n';

    return 0;
}