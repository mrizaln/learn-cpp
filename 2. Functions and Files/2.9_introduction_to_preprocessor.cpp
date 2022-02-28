// The preprocessor is best thought of as a separate program that manipulates the text in
// each code file. When the preprocessor runs, it scans through the code file (from top to
// bottom), looking for preprocessor directives. Preprocessor directives (often just called
// directives) are instructions that start with a # symbol and end with a newline (NOT a
// semicolon). These directives tell the preprocessor to perform specific particular text
// manipulation tasks. 

// ==========[ Includes ]==========
    // When you #include a file, the preprocessor replaces the #include directive with the
    // contents of the included file. The included contents are then preprocessed (along
    // with the rest of the file), and then compiled

#include <iostream>

void cout_something()
{
    std::cout << "something" << '\n';
}

// ==========[ Macro defines ]==========
    // The #define directive can be used to create a macro. In C++, a macro is a rule that
    // defines how input text is converted into replacement output text.

    // There are two basic types of macros: object-like macros, and function-like macros.
        // Function-like macros act like functions, and serve a similar purpose.

        // Object-like macros can be defined in one of two ways:
            //      #define identifier
                        // Any further occurrence of the identifier is removed and replaced
                        // by nothing!

            #define NOTHING
            void cout_nothing()
            {
                std::cout << NOTHING 'a' << '\n';   // is the same as std::cout << 'a';
            }

            //      #define identifier substitution_text
                        // When the preprocessor encounters this directive, any further
                        // occurrence of the identifier is replaced by substitution_text.

            #define MY_NAME "Maiuna"
            void cout_my_name()
            {
                std::cout << "My name is " << MY_NAME << '\n';
            }

// ==========[ Conditional compilation ]==========
    // The conditional compilation preprocessor directives allow you to specify under what
    // conditions something will or won’t compile.

    // ------[ #ifdef   and   #endif ]------
        // The #ifdef preprocessor directive allows the preprocessor to check whether an
        // identifier has been previously #defined. If so, the code between the #ifdef and
        // matching #endif is compiled. If not, the code is ignored.
    
    #define PRINT_JOE
    void conditional()
    {
    #ifdef PRINT_JOE
        std::cout << "Joe\n";   // will be compiled since PRINT_JOE is defined
    #endif

    #ifdef PRINT_BOB
        std::cout << "Bob\n";   // will be ignored since PRINT_BOB is not defined
    #endif
    }
    
    // ------[ #ifndef   and   #endif ]------
        // The #ifndef is the opposite of #ifdef, in that it allows you to check whether
        // an identifier has NOT been #defined yet.
    void conditional_too()
    {
    #ifndef PRINT_BOB
        std::cout << "Bob\n";
    #endif
    }

    // ------[ #if 0 and #endif ]------
        // excludes a block of code from being compiled
    void compilation()
    {
        std::cout << "a compilation\n";
    #if 0
        std::cout << "hey";
        std::cout << "this block of code will be ignored";
        std::cout << "have a good day!";
        std::cout << "starting from #if 0 to #endif";
    #endif
    }