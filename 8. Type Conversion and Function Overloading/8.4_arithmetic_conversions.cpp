#include <iostream>
#include <typeinfo>

//============[ the operators that require operands of the same type ]============

// the following operators require their operands to be of the same type:
    // 1. binary arithmetic operators         : +, -, *, /, %
    // 2. binary relational operators         : <, >, <=, >=, ==, !=
    // 3. binary bitwise arithmetic operators : &, ^, |
    // 4. conditional operator                : ? (excl. condition, which is bool)




//============[ the usual arithmetic conversion rules ]============

// the rules are pretty simple.
// the compiler has a prioritized list of types that looks something like this:
    // 1. long double (highes)
    // 2. double
    // 3. float
    // 4. unsigned long long
    // 5. long long
    // 6. unsigned long
    // 7. long
    // 8. unsigned int
    // 9. int (lowest)

// there are only two rules:
    // 1. if the type of at least one of the operands is on the priority list, the operand with
    //    lower priority is converted to the type of the operand with higher priority.

    // 2. otherwise (the type of neither operand is on the list), both operands are numerically
    //    promoted




//============[ some examples ]============

// in the following examples, we'll use the typeid operator (included in the <typeinfo> header),
// to show the resulting type of an expression.

    int main_examples()
    {
    // add an int and a double
        int i { 2 };
        double d { 3.5 };
        std::cout << typeid(i + d).name() << ' ' << i + d << '\n';          // output a value of type double
    
    // add two short
        short s1 { 4 };
        short s2 { 5 };
        std::cout << typeid(s1 + s2).name() << ' ' << s1 + s2 << '\n';      // output a value of type int

        return 0;
    }




//============[ signed and unsigned issue ]============

// this priorization hierarchy can cause some problematic issues when mixing signed and unsigned
// values

    int main_mixing_signed_and_unsigned()
    {
    // int with unsigned int on arithmetic operator
        std::cout << typeid(5u - 10).name() << ' ' << 5u - 10 << '\n';      // expected: returns -5
                                                                            // reality : returns an unsigned value of 2^sizeof(int) - 5

    // because the unsigned int operand has higher priority, the int operand is converted
    // to an unsigned int. and since the value of -5 is out of range of an unsigned int,
    // we get a result we don't expect


    // int with unsigned int on relational operator
        std::cout << std::boolalpha << (-3 < 5u);       // expected: true
                                                        // reality : false

    // when the expression above evaluates, -3 is converted to a large unsigned int that is
    // larger than 5.
    // thus the above prints false

        return 0;
    }

// this is one of the primary reasons to avoid unsigned integers.




//=======================================================================================

int main()
{
    main_examples();
    main_mixing_signed_and_unsigned();

    return 0;
}