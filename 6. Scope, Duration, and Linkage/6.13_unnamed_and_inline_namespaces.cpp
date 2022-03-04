//============[ unnamed (anonyomus) namespaces ]============

// an unnamed namespace (also called anonymous namespace) is a namespace that is defined
// without a name, like so:

#include <iostream>

    namespace   // unnamed namespace
    {
        void doSomething()  // can only be accessed in this file
        {
            std::cout << "v1\n";
        }
    }

    int main_unnamed_namespace()
    {
        doSomething();      // we can call doSomething() without a namespace prefix

        return 0;
    }

// all content declared in an unnamed namespace is treated as if it is part of the parent
// namespace
// this might make unnamed namespace seem useless, but the other effect of unnamed namespaces
// is that all identifiers indside an unnamed namespace are treated as if they had internal
// linkage, which means that the content of an unnamed namespace can't be seen outside of
// the file in which the unnamed namespace is defined

// for functions, this is effectively the same as defining all functions in the unnamed
// namespace as static functions

    static void doSomething_alt()   // can only be accessed in this file
    {
        std::cout << "v1\n";
    }

    // doSomething() is effectively identical with doSomething_alt()

// unnamed namespace are typically used when you have a lot of content that you want to
// ensure stays local to a given file,
// unnamed namespace will also keep user-defined types local to the file



//============[ inline namespaces ]============

// let's say you want to improve some functions. but if you do this, you risk breaking
// existing programs using the older version.
// how do you handle this?

// one way would be to create a new version of the function with a different name
// example:     doSomething(), doSomething_v2, doSomething_v3, etc.

// an alternate is to use an inline namespace.
// an inline namespace is a namespace that is typically used to version content.
// like unnamed namespace, anything declared inside an inline namespace is considered
// part of the parent namespace.
// however, inline namespace don't give everything internal linkage

    inline namespace v1     // declare an inline namespace named v1
    {
        void doSomethingSomething()
        {
            std::cout << "v1\n";
        }
    }

    /*inline*/ namespace v2     // uncomment the /*inline*/ to use this instead as default, and remove (or comment) the inline keyword in the other
    {
        void doSomethingSomething()
        {
            std::cout << "v2\n";
        }
    }

    int main_inline_namespace()
    {
        v1::doSomethingSomething();     // calls the v1 version of doSomethingSomething()
        v2::doSomethingSomething();     // calls the v2 version of doSomethingSomething()
        doSomethingSomething();         // calls th inline version of doSomethingSomething() (which is v1)

        return 0;
    }

//=======================================================================================

int main()
{
    main_unnamed_namespace();
    main_inline_namespace();
}