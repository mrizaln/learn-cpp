// #define ALLOW_ERROR_INSTANCE_NOT_COMPILE

#include <iostream>

// from previous lesson
template <typename T>
T max(T x, T y)
{
    return (x > y) ? x : y;
}

/*---------------------------------------------------------------------------------------
                ============[ using a function template ]============
---------------------------------------------------------------------------------------*/

// function templates are not actually functions -- their code isn't compiled or executed
// directly.
// instead, function templates have one job: to generate functions

// to use our max<T> function template:
/*-------------------------------------
     max<actual_type>(arg1, arg2);
-------------------------------------*/

namespace using_function_template
{
    int main()
    {
        std::cout << max<int>(1, 2) << '\n';
        std::cout << max<int>(8, 6) << '\n';
        std::cout << max<double>(3, 5) << '\n';

        return 0;
    }
}

// the process of creating functions from function templates is called function template instantiation.
// when this process happens due to a function call, it's called function template instatiation.
// an instantiated function is often called funtion instance or a template function.




/*---------------------------------------------------------------------------------------
               ============[ template argument deduction ]============
---------------------------------------------------------------------------------------*/

// in most cases, the actual types we want to use for instantiation will match the type of
// our function parameters.

// in cases where the type of the arguments match the actual type we want, we do not need
// to specify the actual type -- instead we can use [template argument deduction] to have
// the compiler deduce the actual type.

namespace template_argument_deduction
{
    template <typename T>
    T maxx(T x, T y)
    {
        std::cout << "called maxx<int>(int, int)\n";
        return (x > y) ? x : y;
    }

    int maxx(int x, int y)
    {
        std::cout << "called maxx(int, int)\n";
        return (x > y) ? x : y;
    }

    int main()
    {
        std::cout << maxx<int>(1, 2) << '\n';       // selects max<int>(int, int)
        std::cout << maxx<>(1, 2) << '\n';          // deduces max<int>(int, int) -- non template functions not considered
        std::cout << maxx(1, 2) << '\n';            // calls function max(int, int)

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    favor the normal function call syntax when using function templates
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
      ============[ function templates with non-template parameters ]============
---------------------------------------------------------------------------------------*/

// it's possible to create function templates that have both template types and non-template
// type parameters.
// the template type parameters can be matched to any type, and the non-template parameters
// work like the parameters of normal function

namespace template_with_non_template_param
{
    template <typename T>
    int someFcn(T x, double y)
    {
        return 5;
    }

    int main()
    {
        someFcn(1, 3.4);        // someFcn(int, double)
        someFcn(1, 3.4f);       // someFcn(int, double) -- float promoted to double
        someFcn(1.2, 3.4);      // someFcn(double, double)
        someFcn(1.2, 3.4f);     // someFcn(double, double) -- float promoted to double
        someFcn(1.2f, 3.4);     // someFcn(float, double)
        someFcn(1.2f, 3.4f);    // someFcn(float, double) -- float promoted to double

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
        ============[ instantiated functions may not always compile ]============
---------------------------------------------------------------------------------------*/

#ifdef ALLOW_ERROR_INSTANCE_NOT_COMPILE
namespace instance_not_compile
{
    template <typename T>
    T addOne(T x)
    {
        return x + 1;
    }

    int main()
    {
        std::string hello { "hello world" };
        std::cout << addOne(hello) << '\n';

        return 0;
    }
}
#endif




// [ best practice ]
/*---------------------------------------------------------------------------------------
    use function templates to write generic code that can work with a wide variety of
    types whenever you have the need.
---------------------------------------------------------------------------------------*/




//=======================================================================================

int main()
{
    using_function_template::main();
    template_argument_deduction::main();
    template_with_non_template_param::main();
#ifdef ALLOW_ERROR_INSTANCE_NOT_COMPILE
    instance_not_compile::main();
#endif

    return 0;
}