#include <iostream>
#include <string>
#include <string_view>
#include <array>


/*---------------------------------------------------------------------------------------
          ============[ pointers, references, and derived classes ]============
---------------------------------------------------------------------------------------*/

// C++ let us set a Base pointer or reference to a Derived object.

namespace pointer_reference_to_base_class
{
    class Animal
    {
    protected:
        std::string m_name{};

        // protected because we don't want people to create Animal objects directly
        Animal(std::string_view name)
            : m_name{ name }
        {
        }

        // to prevent slicing (covered later)
        Animal(const Animal&) = default;
        Animal& operator=(const Animal&) = default;

    public:
        const auto& getName() const { return m_name; }
        const auto& speak() const { return "???"; }
    };

    class Cat: public Animal
    {
    public:
        Cat(std::string_view name)
            : Animal{ name }
        {
        }
    };

    class Dog: public Animal
    {
    public:
        Dog(std::string_view name)
            : Animal{ name }
        {
        }
    };

    void main()
    {
        const Cat cat{ "Fred" };
        std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';

        const Dog dog{ "Garbo" };
        std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';

        const Animal* pAnimal{ &cat };
        std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

        const Animal& rAnimal{ dog };
        std::cout << "rAnimal is named " << rAnimal.getName() << ", and it says " << rAnimal.speak() << '\n';

        /* [ outputs: ]
            cat is named Fred, and it says Meow
            dog is named Garbo, and it says Woof
            pAnimal is named Fred, and it says ???
            pAnimal is named Garbo, and it says ???
        */
    }
}

/*
  - because rAnimal and pAnimal are a Animal reference and pointer, they can only see members
    of Animal.
  - so even though Cat::speak() or Dog::speak() shadows Animal::speak() for derived objects,
    the base pointer/reference can not see Cat::speak() or Dog::speak().
*/




/*---------------------------------------------------------------------------------------
      ============[ use for pointers and references to base classes ]============
---------------------------------------------------------------------------------------*/

// we would be able to pass derived objects using base class pointer or reference
// the problem is of course, the function can't call derived version of speak()

namespace pass_derived_objects
{
    using pointer_reference_to_base_class::Animal;
    using pointer_reference_to_base_class::Cat;
    using pointer_reference_to_base_class::Dog;

    void report(const Animal& rAnimal)
    {
        std::cout << rAnimal.getName() << " says " << rAnimal.speak() << '\n';
    }

    void main()
    {
        report(Cat{ "fred" });      // prints: fred says ???
    }
}


// we can also able to make an array of derived objects in a single array
// the aforementioned problem still persists though

namespace multiple_derived_objects_array
{
    using pointer_reference_to_base_class::Animal;
    using pointer_reference_to_base_class::Cat;
    using pointer_reference_to_base_class::Dog;

    void main()
    {
        const Cat fred{ "Fred" };
        const Cat misty{ "Misty" };
        const Cat zeke{ "Zeke" };

        const Dog garbo{ "Garbo" };
        const Dog pooky{ "Pooky" };
        const Dog truffle{ "Truffle" };

        // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
        // Note: to_array requires C++20 support (and at the time of writing, Visual Studio 2022 still doesn't support it correctly)
        const auto animals{ std::to_array<const Animal*>({&fred, &garbo, &misty, &pooky, &truffle, &zeke }) };

        // Before C++20, with the array size being explicitly specified
        // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };

        for (const auto animal : animals)
        {
            std::cout << animal->getName() << " says " << animal->speak() << '\n';
        }
    }
}

// p.s. the virtual function will come to rescue.




//=======================================================================================

int main()
{
    pointer_reference_to_base_class::main();
    pass_derived_objects::main();
    multiple_derived_objects_array::main();

    return 0;
}