//============[ qualified and unqualified names ]============

// a qualified name is a name that includes an associated scope
// most often, names are qualified with a namespace using the scope resolution operator

#include <iostream>

    int foo {};

    void quialified_names()
    {
        std::cout;      // identifier cout is qualified by namespace std
        ::foo;          // identifier foo is qualified by the global namespace
    }

// an unqualified name is a name that does not include a scoping qualifier
// for example   cout   ,   x   , are unqualified names



//============[ using declarationss ]============

// a using declaration allows us to use an unqualified name (with no scope) as an alias
// for a qualified name

    int main_using_declaration()
    {
        using std::cout;    // this using declaration tells the compiler that cout should resolve to std::cout
        cout << "Hello World!" << '\n';

        return 0;
    } // the using declaration expires here

// if there's a naming collision, between std::cout and other cout function, std::cout
// will be preferred



//============[ using directives ]============

// a using directive imports all of the identifiers from a namespace into the scope of the
// using directive

    int main_using_directive()
    {
        using namespace std;    // this using drective tells the compiler to import all names from namespace std into the current namespace without qualification
        // cout << "Hello world!" << '\n';

        return 0;
    }



//============[ problems with using directives ]============
//++++++[ why you sould avoid "using namesapce std;"" ]++++++

// because using directives import all of the names from a namespace (potentially including
// lots of names you'll never use), the possibility for naming collisionsto occur increases
// significantly (especially if you import the std namespace)

    namespace a
    {
        int x { 10 };
    }

    namespace b
    {
        int x { 20 };
    }

    int main_problem_using_directive()
    {
        using namespace a;
        using namespace b;

        // std::cout << x << '\n';     // ambiguous symbol, x refers to a::x or b::x ?
        std::cout << a::x << '\n';      // explicitly tells the compiler which one to use
        std::cout << b::x << '\n';

        return 0;
    }

// another example

    int cout()      // declares our own "cout" function
    {
        return 5;
    }

    int main_problem_using_directive_cout()
    {
        using namespace std;        // makes std::cout accessible as "cout"
        // cout << "Hello, world!";    // which cout?

        return 0;
    }



//============[ canceling or replacing a using statement ]============

// once a using statemgnt has been declared, there's no way to canel or replace it with a
// different using statememnt within the scope in which it was declared

    namespace goo
    {
        int a{};
    }

    int main_no_way_to_cancel()
    {
        using namespace goo;

        // there's no way to cancel the "using namesapce goo" here!
        // there's also no way to replace "using namespace goo" with a different using statement

        return 0;
    } // using namespace goo ends here

// the best you can do is intentionally limit the scope of the using statement from the outset
// using the block scoping rules

    namespace hoo
    {
        int a{};
    }

    int main_intentionally_limit_using()
    {
        {
            using namespace goo;
            // calls to goo:: stuff here
        } // using namespace goo expires

        {
            using namespace hoo;
            // calls to hoo:: stuff here
        } // using namespace hoo expires

        return 0;
    }



//============[ best practices for using statements ]============

// avoid   using directives   (particularly   using namespace std;  ), except in specific
// circumstances.
// using declarations   are generally considered safe to use inside blocks.
// limit their use in the global namespace of a code file, and never use them in the global
// namesapce of a header file.

/* best practice
    prefer explicit namespaces over using statements. avoid using directive whenever possible.
    using declareations are okay to use inside blocks
*/


//==================+==================+==================+==================+===========

int main()
{
    main_problem_using_directive();
}