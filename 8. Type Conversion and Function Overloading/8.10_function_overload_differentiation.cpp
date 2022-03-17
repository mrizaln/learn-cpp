//============[ how overloaded functions are differentiated ]============

/*---------------------------------------------------------------------------------------
function property    | used for overloading  |     notes
-----------------------------------------------------------------------------------------
number of parameters        yes             
type of parameters          yes                 excludes typedefs, type aliases, and const qualifier on value parameters. includes ellipses.
return type                 no
---------------------------------------------------------------------------------------*/




//============[ overloading based on number of parameters ]============

    int addd(int x, int y)
    {
        return x + y;
    }

    int addd(int x, int y, int z)
    {
        return x + y + z;
    }




//============[ overloading based on typ of parameters ]============

    int add(int x, int y);              // integer version
    double add(double x, double y);     // floating point version
    double add(int x, double y);        // mixed version
    double add(double x, int y);        // mixed version

// because type aliases (or typedefs) are not distinct types, overloaded functions using type
// aliases are not distinct from overloads using the aliases type.

    typedef int height_t;
    using age_t = int;

    void print(int value);
    void print(height_t value);     // not differentiated from print(int)
    void print(age_t value);        // not differentiated from print(int)

// for parameter passed by value, the const qualifier is also not considered.

    void print(const int value);    // not differentiated from print(int)




//============[ the return type of a function is not considered for differentiation ]============

// this will result in compile error:

    int getRandomValue();
    double getRandomValue();




//============[ name mangling ]============

// when the compiler compiles a function, it performs name mangling, which means the compiled
// name of the function is altered ("mangled") nased on various criteria, such as the number
// and type of paramters, so the linker has unique names to work with.


//=======================================================================================

int main()
{
    return 0;
}