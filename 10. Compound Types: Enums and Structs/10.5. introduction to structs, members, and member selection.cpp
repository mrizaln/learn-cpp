#include <iostream>

// A [struct] (short for structure) is a program-defined data type that allows us to bundle
// multiple variables together into a single type.

/*---------------------------------------------------------------------------------------
                      ============[ defining structs ]============
---------------------------------------------------------------------------------------*/

// an example of a struct definition of an employee

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

// the variables that are part of the struct are called [data members] (or [member variables]).
// the empty curly braces here ensure that the variables inside our [Employee] are value
// initialized when an [Employee] is created.




/*---------------------------------------------------------------------------------------
                   ============[ defining struct objects ]============
---------------------------------------------------------------------------------------*/

Employee joe;       // create an Employee struct for joe
Employee frank;     // create an Employee struct for frank




/*---------------------------------------------------------------------------------------
                      ============[ accessing members ]============
---------------------------------------------------------------------------------------*/

// to access a specific member variable, we use [member selection operator] (.) in between
// the struct variable name and the member name.

int main()
{
    Employee kevin;

    kevin.id = 15;          // use member selection operator to select id member
    kevin.age = 32;
    kevin.wage = 40000.0;

    Employee john;

    john.id = 16;
    john.age = 25;
    john.wage = 30000.0;

    if (john.age > kevin.age)
        std::cout << "kevin is younger than john\n";
    else if (john.age < kevin.age)
        std::cout << "john is younger than kevin\n";
    else
        std::cout << "john and kevin is in the same age: " << kevin.age << '\n';

    return 0;
}