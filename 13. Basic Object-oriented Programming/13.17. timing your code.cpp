#include <iostream>
#include <chrono>       // for std::choro functions



/*
  - when writing your code, simetimes you'll run accross caes where you're not sure whether
    one method or another will be more performant.
  - so how do you tell?

  - one easy way is to time your code to see how long it takes to run.
  - C++11 comes with some functionality in the chrono library to do just that.
  - however, using the chrono library is a bit arcane.
  - the good news is that we can easily encapsulate all the timing functionality we need
    into a class that we can then use in our own programs.
*/

class Timer
{
private:
    // type aliases
    using clock_type = std::chrono::steady_clock;
    using second_type = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_type> m_beg{ clock_type::now() };

public:
    void reset()
    {
        m_beg = clock_type::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
    }
};

/*
  - to use it, we instantiate a Timer object at the top of our main function (or wherever
    we want to start timing), and then call the elapsed() member function whenever we want
    to know how long the program took to run to that point.
*/




/*---------------------------------------------------------------------------------------
                        ============[ an example ]============
---------------------------------------------------------------------------------------*/

// now, for example, we try to time where we sort an array of 10000 elements.

#include <array>
#include <numeric>      // std::iota
#include <algorithm>
#include <cstddef>      // std::size_t


namespace an_example
{
    const int g_arrayElements{ 10000 };

    // selection sort
    template <std::size_t arr_n>
    void selectionSort(std::array<int, arr_n>& array)
    {
        for (std::size_t startIndex{ 0 }; startIndex < (g_arrayElements-1); ++startIndex)
        {
            std::size_t smallestIndex{ startIndex };        // the index of smallest element we've encountered so far

            for (std::size_t currentIndex{ startIndex+1 }; currentIndex < g_arrayElements; ++currentIndex)
            {
                if (array[currentIndex] < array[smallestIndex])
                    smallestIndex = currentIndex;

                std::swap(array[startIndex], array[smallestIndex]);
            }
        }
    }

    // bubble sort
    template <std::size_t arr_n>
    void bubbleSort(std::array<int, arr_n>& array)
    {
        std::size_t size{ array.size() };
        for (std::size_t iteration { 0 }; iteration < size-1; ++iteration)
        {
            for (std::size_t index { 0 }; index < size-1; ++index)
            {
                if (array[index] > array[index+1])
                    std::swap(array[index], array[index+1]);
            }
        }
    }

    // insertion sort
    template <std::size_t arr_n>
    void insertionSort(std::array<int, arr_n>& array)
    {
        for (std::size_t startIndex{ 0 }; startIndex < array.size(); ++startIndex)
        {
            int* numPtr{ &array[startIndex] };
            
            // extract
            int num{ *numPtr };

            for (int sortedIndex{ (int)(startIndex-1) }; sortedIndex >= 0; --sortedIndex)
            {
                int* current{ &array[sortedIndex] };

                if (*current < num)
                    break;

                *(current + 1) = *current;
                numPtr = current;
            }

            *numPtr = num;
        }
    }

    void main()
    {
        std::array<int, g_arrayElements> array;
        std::iota(array.rbegin(), array.rend(), 1);     // fill the array with values 10000 to 1

        // std::array<int, g_arrayElements> array_copy;
        // std::copy(array.begin(), array.end(), array_copy.begin());
        
        
        // selection sort
        auto array_copy{ array };
        Timer t;
        selectionSort(array_copy);
        std::cout << "selection sort : " << t.elapsed() << " seconds\n";

        // bubble sort
        array_copy = array;
        t.reset();
        bubbleSort(array_copy);
        std::cout << "bubble sort    : " << t.elapsed() << " seconds\n";

        // insertion sort
        array_copy = array;
        t.reset();
        insertionSort(array_copy);
        std::cout << "insertion sort : " << t.elapsed() << " seconds\n";

        // std::sort
        array_copy = array;
        t.reset();
        std::ranges::sort(array_copy);
        std::cout << "std::sort      : " << t.elapsed() << " seconds\n";
    }
}




//=======================================================================================

int main()
{
    an_example::main();

    return 0;
}