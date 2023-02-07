/*------------------------------------------------------------------------------
                ============[ circular references ]============
------------------------------------------------------------------------------*/

// is a series of references where each object references the next, and the last
// object reference back to the first causing a referential loop

#include <iostream>
#include <memory>    // for std::shared_ptr
#include <string>

namespace circular_reference
{
    class Person
    {
        std::string             m_name;
        std::shared_ptr<Person> m_partner;    // initially created empty

    public:
        Person(const std::string& name)
            : m_name(name)
        {
            std::cout << m_name << " created\n";
        }
        ~Person()
        {
            std::cout << m_name << " destroyed\n";
        }

        friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
        {
            if (!p1 || !p2) {
                return false;
            }

            p1->m_partner = p2;
            p2->m_partner = p1;

            std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

            return true;
        }
    };

    void main()
    {
        auto lucy{ std::make_shared<Person>("Lucy") };      // create a Person named "Lucy"
        auto ricky{ std::make_shared<Person>("Ricky") };    // create a Person named "Ricky"

        partnerUp(lucy, ricky);    // Make "Lucy" point to "Ricky" and vice-versa
    }    // neither lucy nor ricky will be deallocated
}




/*------------------------------------------------------------------------------
            ============[ so what is std::weak_ptr for? ]============
------------------------------------------------------------------------------*/

/*
  - std::weak_ptr was designed to solve the "cyclical ownership" problem described
    above.
  - a std::weak_ptr is an observer -- it can observe and access the same object
    as std::shared_ptr (or other std::weak_ptr) but it is not considered an owner.
*/

namespace circular_reference_solved
{
    class Person
    {
        std::string m_name;
        std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

    public:

        Person(const std::string &name): m_name(name)
        {
            std::cout << m_name << " created\n";
        }
        ~Person()
        {
            std::cout << m_name << " destroyed\n";
        }

        friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
        {
            if (!p1 || !p2)
                return false;

            p1->m_partner = p2;
            p2->m_partner = p1;

            std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

            return true;
        }
    };

    void main()
    {
        auto lucy { std::make_shared<Person>("Lucy") };
        auto ricky { std::make_shared<Person>("Ricky") };

        partnerUp(lucy, ricky);
    }
}




/*------------------------------------------------------------------------------
                ============[ using std::weak_ptr ]============
------------------------------------------------------------------------------*/

/*
  - one downside of std::weak_ptr is that std::weak_ptr are not directly usable
    (they have no operator->).
  - to use a std::weak_ptr, you must first convert it into a std::shared_ptr.
  - to convert std::weak_ptr into a std::shared_ptr, you can use the lock() member
    function.
*/

namespace circular_reference_solved_again
{
    class Person
    {
        std::string m_name;
        std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

    public:

        Person(const std::string &name) : m_name(name)
        {
            std::cout << m_name << " created\n";
        }
        ~Person()
        {
            std::cout << m_name << " destroyed\n";
        }

        friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
        {
            if (!p1 || !p2)
                return false;

            p1->m_partner = p2;
            p2->m_partner = p1;

            std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

            return true;
        }

        const std::shared_ptr<Person> getPartner() const { return m_partner.lock(); } // use lock() to convert weak_ptr to shared_ptr
        const std::string& getName() const { return m_name; }
    };

    void main()
    {
        auto lucy { std::make_shared<Person>("Lucy") };
        auto ricky { std::make_shared<Person>("Ricky") };

        partnerUp(lucy, ricky);

        auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
        std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';
    }
}




/*------------------------------------------------------------------------------
     ============[ avoid dangling pointers with std::weak_ptr ]============
------------------------------------------------------------------------------*/

// the easiest way to test whether a std::weak_ptr is valid is to use the expired()
// member function, which returns true if the std::weak_ptr is pointing to an invalid
// object, and false otherwise.

namespace avoid_dangling_pointer
{
    class Resource
    {
    public:
        Resource() { std::cerr << "Resource acquired\n"; }
        ~Resource() { std::cerr << "Resource destroyed\n"; }
    };

    // Returns a std::weak_ptr to an invalid object
    std::weak_ptr<Resource> getWeakPtr()
    {
        auto ptr{ std::make_shared<Resource>() };
        return std::weak_ptr{ ptr };
    } // ptr goes out of scope, Resource destroyed

    // Returns a dumb pointer to an invalid object
    Resource* getDumbPtr()
    {
        auto ptr{ std::make_unique<Resource>() };
        return ptr.get();
    } // ptr goes out of scope, Resource destroyed

    int main()
    {
        auto dumb{ getDumbPtr() };
        std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

        auto weak{ getWeakPtr() };
        std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

        return 0;
    }
}


//==============================================================================

int main()
{
    circular_reference::main();
    std::cout << '\n';
    circular_reference_solved::main();
    std::cout << '\n';
    circular_reference_solved_again::main();
    std::cout << '\n';
    avoid_dangling_pointer::main();

    return 0;
}
