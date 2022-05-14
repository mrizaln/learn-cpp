#include <iostream>

/*---------------------------------------------------------------------------------------
    ============[ member selection fot structs and references to structs ]============
---------------------------------------------------------------------------------------*/

// we already know that you can use member selection operator (.) to select a member from
// a struct object

// we can do the same to struct reference




/*---------------------------------------------------------------------------------------
          ============[ member selection for pointers to structs ]============
---------------------------------------------------------------------------------------*/

// we can't use the member selection operator directly

// either we dereference the pointer first then apply the member selection operator, or use
// a [member selection from pointer operator (->)] (arrow operator)

namespace member_selection_for_pointers_to_structs
{
    struct Employee
    {
        int id {};
        int age {};
        double wage {};
    };

    int main()
    {
        Employee joe { 1, 34, 65000.0 };

        ++joe.age;
        joe.wage = 68000.0;

        Employee* ptr { &joe };
        std::cout << (*ptr).id << '\n';         // dereference then use member selection
        std::cout << ptr->id << '\n';           // use arrow operator (better)

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
         ============[ mixing pointers and non-pointers to members ]============
---------------------------------------------------------------------------------------*/

// the member selection operator is alwaus applied to the currently selected variable.

namespace mixing_pointer_and_non_pointer
{
    struct Paw
    {
        int claws {};
    };

    struct Animal
    {
        std::string name {};
        Paw paw {};
    };

    int main()
    {
        Animal puma { "Puma", { 5 } };
        Animal* ptr { &puma };

        std::cout << ptr->paw.claws << '\n';

        return 0;
    }
}




//=======================================================================================

int main()
{
    member_selection_for_pointers_to_structs::main();
    mixing_pointer_and_non_pointer::main();

    return 0;
}