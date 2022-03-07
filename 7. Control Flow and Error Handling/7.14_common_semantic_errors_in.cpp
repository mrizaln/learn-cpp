//============[ conditional logic errors ]============

// a conditional logic error occurs when the programmer incorrectly codes the logic of a
// conditional statement or loop condition.

#include <iostream>

    int main_conditional_logic_error()
    {
        std::cout << "Enter an integer: ";
        int x {};
        std::cin >> x;

        if (x >= 5)     // oops, we used operator>= instead of operator>
            std::cout << x << " is greater than than 5\n";

        return 0;
    }



//============[ infinite loop ]============

    int main_infinite()
    {
        int count { 1 };
        while (count <= 10)     // this condition will never be false
        {
            std::cout << count << ' ';      // this line will repeatedly execute
        }

        return 0;   // this line will never execute
    }

// in this case, we forgot to increment count, so the loop condition will never be false

    int main_infinite_too()
    {
        for (unsigned int count { 5 }; count >= 0; --count)
        {
            if (count == 0)
                std::cout << "blastoff! ";
            else
                std::cout << count << ' ';
        }

        return 0;
    }

// in the above, count >= can never be false when count is an unsigned integer



//============[ off-by-one errors ]============

// an off-by-one error is an error that occurs when a loop executes one too many ot one
// too few times

    int main_off_by_one()
    {
        for (unsigned int count{ 1 }; count < 5; ++count)
        {
            std::cout << count << ' ';
        }

        return 0;
    }

// the program supposed to print  1 2 3 4 5 , but it only prints  1 2 3 4 because the wrong
// relational operatur was used



//============[ incorrect operator precedence ]============

    int main_incorrect_precedence()
    {
        int x { 5 };
        int y { 5 };

        if (!x > y)     // oops: operator precedence issue
            std::cout << x << " is not greater than " << y << '\n';
        else
            std::cout << x << " is greater than " << y << '\n';

        return 0;
    }

// logical NOT has higher precedence tha operator>, the conditional evaluates as if it was
// written (!x) > y, which isn't what the programmer intended.



//============[ precision issues with foating point types ]============

// the followin g floating point variable doesn't have enough precision to store the entire
// number:

    int main_not_enough()
    {
        float f { 0.123456789f };
        std::cout << f << '\n';

        return 0;
    }

// because of this lack of precision, the number is rounded slightly:   0.1234567

    int main_equal()
    {
        double d{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 }; // should sum to 1.0

        if (d == 1.0)
            std::cout << "equal\n";
        else
            std::cout << "not equal\n";

        return 0;
    }

// operator== and operator!= can be problematic with floating point numbers due to small
// rounding errors 



//============[ integer division ]============

// in this followingg example, we mean to do a floating point division, but because both
// operands are integers, we end up5 doing integer division instead.

    int main_int_division()
    {
        int x { 3 };
        int y { 5 };

        std::cout << x << " divided by " << y << " is: " << x / y << '\n';  // integer division
        // std::cout << x << " divided by " << y << " is: " << static_cast<float>(x) / y <<'\n';  // this is (one of) the correct way

        return 0;
    }



//============[ aciidental null statements ]============

// in the below program, we only want to blow up the world if we have the user's permission

    void blowUpWorld()
    {
        std::cout << "Kaboom!\n";
    }

    int main_blowUpWorld()
    {
        std::cout << "Should we blow up the world again? (y/n): ";
        char c {};
        std::cin >> c;

        if (c == 'y');          // accidental null statement here
            blowUpWorld();      // so this will always execute since it's not part of the if-statement

        return 0;
    }



//============[ not using a compound statement when one is required ]============

// another variant of the above program

    int main_forgot()
    {
        std::cout << "Should we blow up the world again? (y/n): ";
        char c {};
        std::cin >> c;

        if (c == 'y')
            std::cout << "Okay, here we go...\n";
            blowUpWorld();      // oops, will always execute. should be inside compound statement

        return 0;
    }

// a dangling else also falls into this category



//=======================================================================================

int main()
{
    main_conditional_logic_error();
    // main_infinite();
    // main_infinite_too();
    main_incorrect_precedence();
    main_not_enough();
    main_equal();
    main_int_division();
    main_blowUpWorld();

    return 0;
}