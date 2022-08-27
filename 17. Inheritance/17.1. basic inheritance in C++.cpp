#include <iostream>
#include <string>
#include <string_view>


/*
  - inheritance in C++ takes place between classes.
  - the class being inherited from is called the parent class, base class, or superclas.
  - the class doing the inheriting is called the child class, derived class, or subclass.
*/

class Person
{
// all members public for now for the sake of simplicity
public:
    std::string m_name{};
    int m_age{};

    Person(const std::string& name="", int age=0)
        : m_name{ name }
        , m_age{ age }
    {
    }

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }
};


// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage=0.0, int homeRuns=0)
        : m_battingAverage{ battingAverage }
        , m_homeRuns{ homeRuns }
    {
    }
};


// Employee publicly inherits from Person
class Employee : public Person
{
public:
    double m_hourlySalary{};
    long m_employeeID{};

    Employee(double hourlySalary=0.0, long employeeID=0)
        : m_hourlySalary{ hourlySalary }
        , m_employeeID{ employeeID }
    {
    }

    void printNameAndSalary() const
    {
        std::cout << m_name << ": " << m_hourlySalary << '\n';
    }
};

// it is possible to inherit from a class that is itself derived from another class.
// Supervisor publicly inherits from Employee
class Supervisor : public Employee
{
public:
    long m_overseesIDs[5]{};    // can oversee a max of 5 employees
};



//=======================================================================================

int main()
{
    // BaseballPlayer
    BaseballPlayer joe{};
    joe.m_name = "Joe";
    std::cout << joe.getName() << '\n';

    // Employee
    Employee frank{ 20.25, 12345 };
    frank.m_name = "Frank";
    frank.printNameAndSalary();

    return 0;
}