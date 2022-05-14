#include <iostream>

/*---------------------------------------------------------------------------------------
        ============[ data members are not initialized by default ]============
---------------------------------------------------------------------------------------*/

namespace struct_data_members_not_initialized
{
    struct Employee
    {
        int id;         // no initializer here
        int age;
        double wage;
    };

    int main()
    {
        Employee joe;                       // no initializer either
        std::cout << joe.id << '\n';        // undefined behavior

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
            ============[ aggregate initialization of a struct ]============
---------------------------------------------------------------------------------------*/

/*
  - an [aggregate data type] is any type that can contain multiple data members
  - some type of aggegates allow members to have different types (e.g. structs), while others
    require that all members must be of a single type (e.g. arrays).
*/

// aggregate use a form of initialization called [aggregate initialization], which allows
// us to directly initialize the members of aggregates.

// to do this, we provide an [initializer list] as an initializer, which is just a list of
// comma-separated values.

namespace aggregate_initialization
{
    using struct_data_members_not_initialized::Employee;

    int main()
    {
        Employee frank = { 1, 32, 60000.0 };    // copy-list initialization
        Employee robert ( 3, 45, 62500.0 );     // direct initialization        (C++20)
        Employee joe { 2, 28, 45000.0 };        // list initialization          [preferred]

        return 0;
    }
}

// each of these initialization forms does a [memberwise initialization], which means each
// member in the struct is initialized in the order of declaration.




/*---------------------------------------------------------------------------------------
        ============[ missing initializers in an initializer list ]============
---------------------------------------------------------------------------------------*/

// if an aggregate is initialized but the number of initialization values is fewer than the
// number of members, then all remaining members will be value-initialized.

namespace struct_missing_initializers
{
    using struct_data_members_not_initialized::Employee;

    int main()
    {
        Employee joe { 2, 28 };     // joe.wage will be value-initialized to 0.0
        Employee john {};           // value-initialize all member to 0.0

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                        ============[ const structs ]============
---------------------------------------------------------------------------------------*/

// variables of a struct type can be a const, they must be initialized.

namespace const_structs
{
    struct Rectangle
    {
        double length {};
        double width {};
    };

    int main()
    {
        const Rectangle unit { 1.0, 1.0 };
        const Rectangle zero {};                // value-initialize all member.

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
               ============[ designated initializers (C++20) ]============
---------------------------------------------------------------------------------------*/

// [designated initializers] allow you to explicitly define which initialization values map
// to which members.

// the members must be initialized in the same order in which they are declared in the struct,
// otherwise an error will result.

namespace designated_initializers
{
    struct Foo
    {
        int a {};
        int b {};
        int c {};
    };

    int main()
    {
        Foo f1 { .a{1}, .b{2}, .c{3} };     // ok
        // Foo f2 { .c{3}, .b{3} };            // not ok;

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    when adding a new member to an aggregate, it's safest to add it to the bottom of the
    definition list oso the initializers for other members don't shift.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
            ============[ assignment with an initializer list ]============
---------------------------------------------------------------------------------------*/

// you can also assign values to structs using an initializer list (which does memberwise
// assignment).

namespace struct_assignment_initializer_list
{
    using struct_data_members_not_initialized::Employee;

    int main()
    {
        Employee joe { 1, 32, 60000.0 };
        joe = { joe.id, 33, 66000.0 };

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
       ============[ assignment with designated initializers (C++20) ]============
---------------------------------------------------------------------------------------*/

// designated initializer can also be used in a list assignment.

namespace struct_assignment_designated_initizalizers
{
    using struct_data_members_not_initialized::Employee;

    int main()
    {
        Employee joe { 1, 32, 60000.0 };
        joe = { .id = joe.id, .age = 33, .wage = 66000.0};
    }
}



//=======================================================================================

int main()
{
    struct_data_members_not_initialized::main();

    return 0;
}