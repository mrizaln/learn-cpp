/*---------------------------------------------------------------------------------------
                ============[ introduction to C++ templates ]============
---------------------------------------------------------------------------------------*/

// in C++, the template system was designed to simplify the process of creating functions
// (or classes) that are able to work with different data types.
// a [template] describes what function or class looks like.

// once a template is defined, the compiler can use the template to generate as many overloaded
// functions (or classes) as needed.




/*---------------------------------------------------------------------------------------
    ============[ function templates ]============
---------------------------------------------------------------------------------------*/

// a function template is a function-like definition that is used to generate one or more
// overloaded functions.
// when we create our function template, we use placeholder types (also called template types)
// for any parameter types, return types, or types used int function body that we want to
// be specified later.

namespace templated_max_function
{
    template <typename T>
    T max(T x, T y)
    {
        return (x > y) ? x : y;
    }
}

// it is a common convention to use single capital letters (starting with T) to represent
// template types.




//=======================================================================================

int main()
{
    return 0;
}