#include <iostream>
#include <vector>

/*---------------------------------------------------------------------------------------
                      ============[ length vs capacity ]============
---------------------------------------------------------------------------------------*/

// consider this:
int* array{ new int[10]{ 1, 2, 3, 4, 5 } };     // 5 elements initialized, 5 more is not

/*
  - what if we want to iterate over the elelements we've initialized, reserving the unused
    ones for future expansion?
  - in that case, we need to separately track how many elements were "used" from how many
    elements were allocated.

  - unlike built-in array and std::array, which only remembers its length, std::vector contains
    two separate attributes: length and capacity.
  - in the context of a std::vector [length] is how many elements are being used in the
    array, whereas [capacity] is how many elements were allcated in memory.
*/




/*---------------------------------------------------------------------------------------
                  ============[ more length vs. capacity ]============
---------------------------------------------------------------------------------------*/

// why differentiate between langth and capacity?
// std::vector will reallocate its memory if needed, but it would prefer not to, because
// resizing an array is computationally expensive.

namespace length_vs_capacity
{
    void main()
    {
        std::vector<int> array{};
        array = { 0, 1, 2, 3, 4, };     // array length = 5         capacity: 5
        std::cout << "Length: " << array.size() << " Capacity: " << array.capacity() << '\n';

        array = { 5, 6, 7};             // array length is now 3    capacity: 5
        std::cout << "Length: " << array.size() << " Capacity: " << array.capacity() << '\n';
    }
}




/*---------------------------------------------------------------------------------------
  ============[ array subscripts and at() are based on length not capacity ]============
---------------------------------------------------------------------------------------*/

// the title is self-expalanatory.




/*---------------------------------------------------------------------------------------
              ============[ stack behavior with std::vector ]============
---------------------------------------------------------------------------------------*/

/*
  - if the subscript operator and at() function are based on the array length, and the capaity
    is always at least as large as the array length, why bother about capacity?

  - although std::vector can be used as a dynamic array, it can also be used as a stack.
  - to do this, we can use 3 functions that match our key stack operations:
      > push_back() pushes an element on the stack.
      > back()      returns the value of the top element on the stack.
      > pop_back()  pops an element off the stack.
*/

namespace using_std_vector_as_stack
{
    template <typename T>
    void printStack(const std::vector<T>& stack)
    {
        std::cout << "(cap: " << stack.capacity()
                  << " len: " << stack.size() << ")\t";
        for (T element: stack)
            std::cout << element << ' ';
        std::cout << '\n';
    }

    void main()
    {
        std::vector<int> stack{};

        // because resizing the vector is expensive, we can tell the vector to allocate a
        // certain amount of capacity up front using the reserve() function:
        stack.reserve(5);   // set the capacity to 5

        printStack(stack);

        stack.push_back(5);
        printStack(stack);

        stack.push_back(3);
        printStack(stack);

        stack.push_back(2);
        printStack(stack);

        std::cout << "top: " << stack.back() << '\n';

        stack.pop_back();
        printStack(stack);

        stack.pop_back();
        printStack(stack);

        stack.pop_back();
        printStack(stack);
    }
}




/*---------------------------------------------------------------------------------------
            ============[ vectors may allocate extra capacity ]============
---------------------------------------------------------------------------------------*/

/*
  - when a vector is resized, the vector may allocate more capacity than is needed.
  - this is done to provide some "breathing room" for additional elements, to minimize the
    number of resize operations needed.
  - if, when, and how much additional capacity is allocated is left up to the compiler
    implementer.
*/




//=======================================================================================

int main()
{
    // length_vs_capacity::main();
    using_std_vector_as_stack::main();

    return 0;
}