#include <iostream>


/*---------------------------------------------------------------------------------------
                    ============[ container class ]============
---------------------------------------------------------------------------------------*/

/*
  - a [container class] is a class designed to hold and orgineze multiple instances of another
    type.
  
  - container classes typically implement a fairly standardized minimal set of functionality.
  - most well-defined containers will include functions that:
    1. create an empty container (via a constructor)
    2. insert a new object into the container
    3. remove an object from the container
    4. report the number of objects currently in the container
    5. empty the container of all objects
    6. provide access to the stored objects
    7. sort the elements (optional)

  - container classes implement a member-of relationship.
*/




/*---------------------------------------------------------------------------------------
                    ============[ types of containers ]============
---------------------------------------------------------------------------------------*/

/*
  - container classes generally come in two different varietes:
    1. [value containers] are compositions that store copies of the objects that they are
       holding.
    2. [reference containers] are aggregations that store pointers or references to other
       objects.
*/




/*---------------------------------------------------------------------------------------
                  ============[ an array container class ]===========
---------------------------------------------------------------------------------------*/

/*
  - in this example, we are going to write an integer array class from scratch that implements
    most of the common functionality that containers should have.
  - this array class is going to be a value container.
  - this container will be similar to std::vector<int>
*/

#include <cassert>

class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length)
        : m_length{ length }
    {
        assert(length >= 0);

        if (length) m_data = new int[length]{};
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        assert(index >=0 && index < m_length);
        return m_data[index];
    }

    void reallocate(int newLength)
    {
        erase();    // first, delete any existing elements

        if (newLength <= 0) return;

        // allocate
        m_data = new int[newLength];
        m_length = newLength;
    }

    void resize(int newLength)
    {
        if (newLength == m_length) return;
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // new array
        int* newData{ new int[newLength] };

        // copy
        if (m_length > 0)
        {
            int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

            // copy elements one by one
            for (int index{ 0 }; index < elementsToCopy; ++index)
                newData[index] = m_data[index];
        }

        // delete old array
        delete[] m_data;

        // points to new array
        m_data = newData;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);

        // new array with length+1
        int* data{ new int[m_length+1] };

        // copy all of the elements up to index
        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];
        
        // insert our new data
        data[index] = value;

        // copy all of the values after the inserted element
        for (int after{ index }; after < m_length; ++after)
            data[after+1] = m_data[after];

        // delete old array and reassign to new array
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        assert(index >= 0 && index < m_length);
        
        if (m_length == 1)
        {
            erase();
            return;
        }

        // new array
        int* data{ new int[m_length-1] };

        // copy all of the elements up to index
        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        // copy all of the elements after the removed element
        for (int after{ index }; after < m_length; ++after)
            data[after-1] = m_data[after];

        // delete old array and reassign to new array
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void insertAtBeginning(int value) { insertBefore(value, 0); }
    void insertAtEnd(int value) { insertBefore(value, m_length); }

    int getLength() const { return m_length; }
};



int main()
{
    IntArray array(10);

    for (int i{ 0 }; i < 10; ++i)
        array[i] = i+1;

    array.resize(8);
    array.insertBefore(20, 5);
    array.remove(3);
    array.insertAtEnd(30);
    array.insertAtBeginning(40);

    for (int i{ 0 }; i < array.getLength(); ++i)
        std::cout << array[i] << ' ';
    std::cout << '\n';

    return 0;

}