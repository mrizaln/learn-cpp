#include <iostream>

/*---------------------------------------------------------------------------------------
                ============[ passing structs {by reference} ]=============
---------------------------------------------------------------------------------------*/

// structs are generally passed by (const) reference to avoid making copies.

namespace passing_structs
{
    struct Employee
    {
        int id {};
        int age {};
        double wage {};
    };

    void printEmployee(const Employee& employee)
    {
        std::cout << "ID   : " << employee.id << '\n';
        std::cout << "Age  : " << employee.age << '\n';
        std::cout << "Wage : " << employee.wage << '\n';
    }

    int main()
    {
        Employee joe { 14, 32, 24.15 };
        Employee frank { 15, 28, 18.27 };

        printEmployee(joe);
        std::cout << '\n';
        printEmployee(frank);

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                      ============[ returning structs ]============
---------------------------------------------------------------------------------------*/

namespace returning_structs
{
    struct Point3d
    {
        double x { 0.0 };
        double y { 0.0 };
        double z { 0.0 };
    };

    Point3d getZeroPoint()
    {
        Point3d temp { 0.0, 0.0, 0.0 };
        return temp;
    }

    int main()
    {
        Point3d zero { getZeroPoint() };

        if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0)
            std::cout << "The point is zero\n";
        else
            std::cout << "The point is not zero\n";

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                  ============[ returning unnamed structs ]============
---------------------------------------------------------------------------------------*/

// let's optimize getZeroPoint() function above

namespace returning_unnamed_structs
{
    using returning_structs::Point3d;

    Point3d getZeroPoint()
    {
        return Point3d { 0.0, 0.0, 0.0 };       // return an unnamed Point3d

        // since we're returning all ero values, we can also do this:
        return {};                              // return a value-initialized Point3d 
    }

    int main()
    {
        Point3d zero { getZeroPoint() };

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
            ============[ structs with program-defined members ]============
---------------------------------------------------------------------------------------*/

namespace struct_with_custom_type_members
{
    using passing_structs::Employee;

    struct Company
    {
        int numberOfEmployee {};
        Employee CEO {};
    };

    int main()
    {
        Company myCompany { 7, {1, 32, 55000.0 } };     // nested initialization
        std::cout << "myCompany CEO wage: " << myCompany.CEO.wage << '\n';

        return 0;
    }
}

// types can also be nested inside other types, like nested namespaces




/*---------------------------------------------------------------------------------------
           ============[ struct size and data structure alignment ]============
---------------------------------------------------------------------------------------*/

// typically, the size of a struct is the sum of the size of all its members, but not always.

namespace struct_size
{
    struct Foo
    {
        short a {};         // 2 B
        int b {};           // 4 B
        double c {};        // 8 B
    };

    int main()
    {
        std::cout << "The size of Foo is " << sizeof(Foo) << '\n';      // 16 B

        return 0;
    }
}

// the size of a struct will be /at least/ as large as the size of all variables it contains.
// but it could be larger by adding gaps into structures.

// this can actually have a pretty significant impact on the size of the struct.

namespace size_of_struct_different
{
    struct Foo1
    {
        short a{};
        short qq{}; // note: qq is defined here
        int b{};
        double c{};
    };

    struct Foo2
    {
        short a{};
        int b{};
        double c{};
        short qq{}; // note: qq is defined here
    };

    int main()
    {
        std::cout << "The size of Foo1 is " << sizeof(Foo1) << '\n';    // 16 B
        std::cout << "The size of Foo2 is " << sizeof(Foo2) << '\n';    // 24 B

        return 0;
    }
}




//=======================================================================================

/*----------
    quiz
----------*/

namespace quiz_1
{
    /*
        You are running a website, and you are trying to keep track of how much money you
        make per day from advertising. Declare an advertising struct that keeps track of
        how many ads you’ve shown to readers, what percentage of ads were clicked on by
        users, and how much you earned on average from each ad that was clicked. Read in
        values for each of these fields from the user. Pass the advertising struct to a
        function that prints each of the values, and then calculates how much you made
        for that day (multiply all 3 fields together).
    */


    struct Advertising
    {
        int numberOfAdsShown {};
        float percentageOfAdsClicked {};
        double earningPerClick {};
    };

    Advertising getAdvertising()
    {
       Advertising ad;

        std::cout << "Number of ads shown      : ";
        std::cin >> ad.numberOfAdsShown;

        std::cout << "Percentage of ads clicked: ";
        std::cin >> ad.percentageOfAdsClicked;

        std::cout << "Earning per ad clicked   : ";
        std::cin >> ad.earningPerClick;

        return ad;
    }

    void printAdvertisingInformation(const Advertising& ad)
    {
        std::cout << "Number of advertisement shown:   " << ad.numberOfAdsShown << '\n';
        std::cout << "Percentage of ads clicked    :   " << ad.percentageOfAdsClicked << " %\n";
        std::cout << "Reveue from clicked ads      :   " << ad.earningPerClick << '\n';
    }

    int main()
    {
        Advertising ad { getAdvertising() };
        printAdvertisingInformation(ad);

        double totalEarning { ad.numberOfAdsShown * ad.percentageOfAdsClicked * ad.earningPerClick };
        std::cout << "Total earnings               : $ " << totalEarning << '\n';

        return 0;
    }
}


namespace quiz_2
{
    struct Fraction
    {
        int numerator {};
        int denominator { 1 };
    };

    Fraction getFraction()
    {
        using namespace std;

        Fraction fraction {};
        
        cout << "Enter value for numerator  : "; 
        cin >> fraction.numerator;
        cout << "Enter value for denumerator: ";
        cin >> fraction.denominator;

        return fraction;
    }

    Fraction multiplyFraction(const Fraction& frac1, const Fraction& frac2)
    {
        return { frac1.numerator * frac2.numerator, frac1.denominator * frac2.denominator };
    }

    void printFraction(const Fraction& fraction)
    {
        std::cout << "Your fraction is: " << fraction.numerator << '/' << fraction.denominator << '\n';
    }

    int main()
    {
        Fraction fraction1 { getFraction() };
        Fraction fraction2 { getFraction() };

        Fraction multipliedFraction { multiplyFraction(fraction1, fraction2) };
        printFraction(multipliedFraction);

        return 0;
    }
}




//=======================================================================================

void quiz()
{
    quiz_1::main();
    quiz_2::main();
}

int main()
{
    passing_structs::main();
    returning_structs::main();
    struct_with_custom_type_members::main();

    struct_size::main();
    size_of_struct_different::main();

    // quiz();

    return 0;
}