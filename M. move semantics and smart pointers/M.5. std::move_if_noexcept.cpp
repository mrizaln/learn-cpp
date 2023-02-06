/*------------------------------------------------------------------------------
            ============[ the move constructor problem ]============
------------------------------------------------------------------------------*/

/*
  - consider the case where we are copying some object, and the copy fails for some
    reason.
  - in such a case, the object being copied is not harmed in any way, because the
    source doesn't need to be modified to create a copy.
  - [strong exception guarantee] is upheld.

  - now consider the case where we are instead moving an object.
  - if the move operation is interrupted by an exception after the transfer of ownership
    occurs, then our source object will be left in a modified state.
  - [strong exception guarantee] is not upheld.
*/




/*------------------------------------------------------------------------------
        ============[ std::move_if_noexcept to the rescue ]============
------------------------------------------------------------------------------*/

/*
  - std::move_if_noexcept can be used to determine whether a move should be performed,
    otherwise copy is performed.

  - if the compiler can tell that an object passed as an argument to std::move_if_noexcept
    won't throw an exception when it is move constructed, then std::move_if_noexcept
    will perform identically to std::move and.
  - otherwise, std::move_if_noexcept will return a normal l-value reference to the
    object.
*/

#include <iostream>
#include <utility>      // For std::pair, std::make_pair, std::move, std::move_if_noexcept
#include <stdexcept>    // std::runtime_error

namespace example
{
    class MoveClass
    {
    private:
        int* m_resource{};

    public:
        MoveClass() = default;

        MoveClass(int resource)
            : m_resource{ new int{ resource } }
        {
        }

        // Copy constructor
        MoveClass(const MoveClass& that)
        {
            // deep copy
            if (that.m_resource != nullptr) {
                m_resource = new int{ *that.m_resource };
            }
        }

        // Move constructor
        MoveClass(MoveClass&& that) noexcept
            : m_resource{ that.m_resource }
        {
            that.m_resource = nullptr;
        }

        ~MoveClass()
        {
            std::cout << "destroying " << *this << '\n';

            delete m_resource;
        }

        friend std::ostream& operator<<(std::ostream& out, const MoveClass& moveClass)
        {
            out << "MoveClass(";

            if (moveClass.m_resource == nullptr) {
                out << "empty";
            } else {
                out << *moveClass.m_resource;
            }

            out << ')';

            return out;
        }
    };

    class CopyClass
    {
    public:
        bool m_throw{};

        CopyClass() = default;

        // Copy constructor throws an exception when copying from a CopyClass object where its m_throw is 'true'
        CopyClass(const CopyClass& that)
            : m_throw{ that.m_throw }
        {
            if (m_throw) {
                throw std::runtime_error{ "abort!" };
            }
        }
    };

    void use_move()
    {
        // We can make a std::pair without any problems:
        std::pair my_pair{ MoveClass{ 13 }, CopyClass{} };

        std::cout << "my_pair.first: " << my_pair.first << '\n';

        // But the problem arises when we try to move that pair into another pair.
        try {
            my_pair.second.m_throw = true;    // To trigger copy constructor exception

            // The following line will throw an exception
            std::pair moved_pair{ std::move(my_pair) };    // <-- use of std::move

            std::cout << "moved pair exists\n";    // Never prints
        } catch (const std::exception& ex) {
            std::cerr << "Error found: " << ex.what() << '\n';
        }

        std::cout << "my_pair.first: " << my_pair.first << '\n';    // <-- source modified
    }

    void use_copy()
    {
        // We can make a std::pair without any problems:
        std::pair my_pair{ MoveClass{ 13 }, CopyClass{} };

        std::cout << "my_pair.first: " << my_pair.first << '\n';

        // But the problem arises when we try to move that pair into another pair.
        try {
            my_pair.second.m_throw = true;    // To trigger copy constructor exception

            // The following line will throw an exception
            std::pair moved_pair{ std::move_if_noexcept(my_pair) };    // <-- use of std::move_if_noexcept

            std::cout << "moved pair exists\n";    // Never prints
        } catch (const std::exception& ex) {
            std::cerr << "Error found: " << ex.what() << '\n';
        }

        std::cout << "my_pair.first: " << my_pair.first << '\n';    // <-- source intact
    }
}




// [ warning ]
/*------------------------------------------------------------------------------
    if a type has both potentially throwing move semantics and deleted copy
    semantics, then std::move_if_noexcept will waive the strong guarantee and
    invoke move semantics. this conditional waiving of the strong guarantee is
    ubiquitous in the standard library container classes, since they use
    std::move_if_noexcept often.
------------------------------------------------------------------------------*/


//==============================================================================

int main()
{
    example::use_move();
    std::cout << '\n';
    example::use_copy();

    return 0;
}
