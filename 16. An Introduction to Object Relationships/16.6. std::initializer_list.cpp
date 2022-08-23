/*---------------------------------------------------------------------------------------
      ============[ class initialization using std::initializer_list ]===========
---------------------------------------------------------------------------------------*/

/*
  - if we create a constructor that takes an std::initializer_list parameter, we can create
    objects using the initializer list as an input.
  - std::initializer_list lievers in the <initializer_list> header.

  - you have to thell std::initializer_list what type of data the list holds using angled
    brackets.
  - std::initializer_list has a (misnamed) size() function which returns the number of elements
    in the list.
*/

#include <iostream>
#include <cassert>
#include <initializer_list>


class IntArray
{
private:
	int m_length {};
	int* m_data {};

    void swap(IntArray& x, IntArray& y)
    {
        using std::swap;
        swap(x.m_length, y.m_length);
        swap(x.m_data, y.m_data);
    }

public:
	IntArray() = default;

	IntArray(int length)
		: m_length{ length }
		, m_data{ new int[length]{} }
	{

	}

	IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
		: IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
	{
		// Now initialize our array from the list
		int count{ 0 };
		for (auto element : list)
		{
			m_data[count] = element;
			++count;
		}
	}

	~IntArray()
	{
		delete[] m_data;
		// we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
	}

	IntArray(const IntArray&) = delete; // to avoid shallow copies
	IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies

    IntArray& operator=(std::initializer_list<int> list)
    {
        int length{ static_cast<int>(list.size()) };

        // if different size, reallocate
        if (length != m_length)
        {
            delete[] m_data;
            m_length = length;
            m_data = new int[length]{};
        }

        int count{ 0 };
        for (auto element : list)
            m_data[count++] = element;

        return *this;        
    }

	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	int getLength() const { return m_length; }
};




/*---------------------------------------------------------------------------------------
        ============[ class assginment using std::initializer_list ]============
---------------------------------------------------------------------------------------*/

/*
  - you can also use std::initializer_list to assign new values to a class by overloading
    the assignment operator to take a std::initializer_list parameter.
  - this works analogously to the above.

  - note that if you implement a constructor that takes a std::initializer_list, you should
    ensure you do at least one of the following:
    1. provide an overloaded list assignment operator
    2. provide a proper deep-copying copy assignment operator
*/




//=======================================================================================


int main()
{
	IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';
    std::cout << '\n';

    array = { 1, 3, 5, 7, 9, 11 };
    for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';
    std::cout << '\n';

	return 0;
}