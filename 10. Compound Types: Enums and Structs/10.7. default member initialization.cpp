#include <iostream>

/*---------------------------------------------------------------------------------------
                            ============[  ]============
---------------------------------------------------------------------------------------*/

/* 
  - when we define a struct (or class) type, we can provide a default initialization value
    for each member as part of the type definition.
  - this process is called [non-static member initialization], and the initialization value
    is called a [default member initializer]
*/

namespace default_member_initialization
{
    struct Something
    {
        int x;              // no initialization value (bad)
        int y {};           // value-initialized by default
        int z { 2 };        // explicit default value
    };

    int main()
    {
        Something s1;
        std::cout << s1.x << ' ' << s1.y << ' ' << s1.z << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
==========[ explicit initialization values take precedence over default values ]=========
---------------------------------------------------------------------------------------*/

namespace explicit_precede_default
{
    using default_member_initialization::Something;

    int main()
    {
        Something s2 { 5, 6, 7};        // no default values are used
        std::cout << s2.x << ' ' << s2.y << ' ' << s2.z << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
        ============[ always provide default values for your members ]============
---------------------------------------------------------------------------------------*/

// to avoid the possibility of uninitialized members, ensure each member has default value

namespace always_provide_default_values
{
    struct Fraction
    {
        int numerator {};           // ok
        int denominator { 1 };      // ok
    };

    int main()
    {
        Fraction f1;
        Fraction f2 {};
        Fraction f3 { 6 };
        Fraction f4 { 5, 8 };

        std::cout << f1.numerator << '/' << f1.denominator << '\n';
        std::cout << f2.numerator << '/' << f2.denominator << '\n';
        std::cout << f3.numerator << '/' << f3.denominator << '\n';
        std::cout << f4.numerator << '/' << f4.denominator << '\n';

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    provide a default value for all members. this ensure that your members will be
    initialized even if the variable definition doesn't include an initialized list.

    if no explicit initializer values will be provided for an aggregate, prefer value
    initialization (with an empty braces initializer) to default initialization.
---------------------------------------------------------------------------------------*/



//=======================================================================================

int main()
{
    default_member_initialization::main();
    explicit_precede_default::main();
    always_provide_default_values::main();

    return 0;
}