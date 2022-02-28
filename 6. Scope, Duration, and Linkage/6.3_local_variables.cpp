//========[ local variables have block scope ]========
// they are in scope from their point of definition to the end of the block they are
// defined within

#include <iostream>

void scope()
{
    int i { 5 };        // i enters scope here
    double d { 4.0 };   // d enters scope here
} // i and d go out of scope here

int function_scope(int x, int y)   // x and y enter scope here
{
    // assign the greater of x or y to max
    int max { (x > y) ? x : y };    // max enters scope here

    return max;
} // x, y, and mac leave scope here



//========[ local variable have automatic storage duration ]========
// a variable's storage duration (usually just called duration) determines what rules
// govern when and how a variable will be created and destroyed.
// in most cases, a variable's storage duratoin directly determines its lifetime.

void duration()
{
    int i { 5 };        // i created and initialized here
    double d { 4.0 };   // d created and initialized here
} // i and d are destroyed here



//========[ local variables in nested blocks ]========

int variables_nested_blocks()
{ // outer block
    int x { 5 };        // x enters scope and is created here

    { // nested block
        int y { 7 };    // y enters scope and is creted here

        // x and y are both in scope here
        std::cout << x << " + " << y << " = " << x + y << '\n';
    } // y goes out of scope and is destroyed here

    // y can not be used here because it is out of scope in this block

    return 0;
} // x goes out of scope and is destroyed here



//========[ local variables have no linkage ]========
// local variables have no linkage, which means that each declaration refers to unique object

int linkage()
{
    int x { 2 };        // local variable, no linkage
    {
        int x { 3 };    // this identifier x refers to a different object that the previous x
    }
    return 0;
}



//========[ variables should be defined in the most limited scope ]========
// if a variable is only used within a nested block, it should be defined inside that nested block.
// by limitin the scope of a variable, you reduce the complexity of the program because the number
// of active variables is reduced.

int limited_scope()
{
    // do not define y here
    {
        // y is only used inside this block, so define it here
        int y { 5 };
        std::cout << y << '\n';
    }

    // otherwise y could still be used here, where it's not needed

    return 0;
}

// if a variable is needed in an outer block, it needs to be declared in the outer block
void variable_outer_block()
{
    int y { 5 };    // we're declarin y here because we need it in this outer block

    {
        int x{};
        std::cin >> x;

        // if we declared y here, immediately before its actual first use...
        if (x == 4)
            y = 4;
    } // ...it would be destroyed here

    std::cout << y; // and we need y to exist here
}




int main()
{
    scope();
    function_scope(1, 2);
    duration();
    variables_nested_blocks();
    linkage();
    limited_scope();
    variable_outer_block();

    return 0;
}
