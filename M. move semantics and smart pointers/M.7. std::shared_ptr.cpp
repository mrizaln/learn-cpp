/*------------------------------------------------------------------------------
                  ============[ std::shared_ptr ]============
------------------------------------------------------------------------------*/

/*
  - unlike std::unique_ptr, which is designed to singly own and manage a resource,
    std::shared_ptr is meant to solve the case where you need multiple smart pointers
    co-owning a resouce.
  - this means that it is fine to have multiple std::shared_ptr pointing to the
    same resource.

  - internally, std::shared_ptr keeps track of how many std::shared_ptr are sharing
    the resource.
  - as long as the least one std::shared_ptr is pointing to the resource, the resouce
    will not be deallocated, even if individual std::shared_ptr are destroyed.
  - as soon as the las std::shared_ptr managing the resource goes out of scope, (or
    reassigned), the resource will be deallocated.
*/

#include <iostream>
#include <memory>    // for std::shared_ptr

namespace shared_ptr
{
    class Resource
    {
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
    };

    void main()
    {
        // allocate a Resource object and have it owned by std::shared_ptr
        Resource* res{ new Resource };
        std::shared_ptr<Resource> ptr1{ res };
        {
            std::shared_ptr<Resource> ptr2{ ptr1 };    // make another std::shared_ptr pointing to the same thing

            std::cout << "Killing one shared pointer\n";
        }    // ptr2 goes out of scope here, but nothing happens

        std::cout << "Killing another shared pointer\n";
    }    // ptr1 goes out of scope here, and the allocated Resource is destroyed
}

// [ best practice ]
/*------------------------------------------------------------------------------
    always make a copy of an existing std::shared_ptr if you need more than one
    std::shared_ptr pointing to the same resource.
------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------------
                ============[ std::make_shared ]============
------------------------------------------------------------------------------*/

// much like std::make_unique() can be used to create a std::unique_ptr in C++14,
// std::make_shared() can (and should) be used to make a std::shared_ptr (since C++11)




/*------------------------------------------------------------------------------
============[ shared pointers can be created from unique pointers ]============
------------------------------------------------------------------------------*/

/*
  - a std::unique_ptr can be converted into a std::shared_ptr via a special std::shared_ptr
    constructor that accepts a std::unique_ptr r-value.
  - the contents of the std::unique_ptr will be moved to the std::shared_ptr.

  - however, std::shared_ptr can not be safely converted to a std::unique_ptr.
  - this means that if you're creating a function that is going to return a smart
    pointer, you're better off returning a std::unique_ptr and assigning it to a
    std::shared_ptr if and when that's appropriate.
*/




//==============================================================================

int main()
{
    shared_ptr::main();

    return 0;
}
