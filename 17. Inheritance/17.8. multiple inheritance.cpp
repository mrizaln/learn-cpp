#include <iostream>
#include <string>
#include <string_view>


/*---------------------------------------------------------------------------------------
                   ============[ multiple inheritance ]============
---------------------------------------------------------------------------------------*/

/*
  - C++ provides the ability to do multiple inheritance.
  - [multiple iheritance] enables a derived class to inherit members from more than one
    parent.
  - to use multiple inheritance, simply specify each base class, separated by a comma.
*/

namespace multiple_inheritance
{
    class Person
    {
    private:
        std::string m_name{};
        int m_age{};

    public:
        Person(std::string_view name, int age)
            : m_name{ name }
            , m_age{ age }
        {
        }

        const std::string& getName() const { return m_name; }
        int getAge() const { return m_age; }
    };

    class Employee
    {
    private:
        std::string m_employer{};
        double m_wage{};

    public:
        Employee(std::string_view employer, double wage)
            : m_employer{ employer }
            , m_wage{ wage }
            {
            }
        
        const std::string& getEmployer() const { return m_employer; }
        double getWage() const { return m_wage; }
    };

    class  Teacher: public Person, public Employee
    {
    private:
        int m_teachesGrade{};

    public:
        Teacher(std::string_view name, int age, std::string_view employer, double wage, int teachesGrade)
            : Person{ name, age }
            , Employee{ employer, wage }
            , m_teachesGrade{ teachesGrade }
        {
        }
    };

    void main()
    {
        Teacher t{ "Mary", 45, "Boo", 14.3, 8 };
    }
}




/*---------------------------------------------------------------------------------------
    ============[ mixins ]============
---------------------------------------------------------------------------------------*/

/*
  - a [mixin] (also spelled mix-in) is a small class that can be inherited from in order to
    ad propeties to a class.
  - the name mixin indicates that the class is intended to be mixed into other classes, not
    instantiated on its own.

  - in the following example, the Box and Labe classes are mixins that we inherit from in
    order to create a new Button class.
*/

namespace mixin
{
    struct Point2D
    {
        int x;
        int y;
    };

    class Box       // mixin box class
    {
    private:
        Point2D m_topLeft{};
        Point2D m_bottomRight{};

    public:
        void setTopLeft(Point2D point) { m_topLeft = point; }
        void setBottomRight(Point2D point) { m_bottomRight = point; }
    };

    class Label     // mixin label class
    {
    private:
        std::string m_text{};
        int m_fontSize{};

    public:
        void setText(std::string_view str) { m_text = str; }
        void setFontSize(int fontSize) { m_fontSize = fontSize; }
    };

    class Button: public Box, public Label {};

    void main()
    {
        Button button{};
        button.Box::setTopLeft({1, 1 });
        button.Box::setBottomRight({ 10, 10 });
        button.Label::setText("Username: ");
        button.Label::setFontSize(6);
    }
}




/*---------------------------------------------------------------------------------------
              ============[ problems with multiple inheritance ]============
---------------------------------------------------------------------------------------*/

/*
  - multiple inheritance introduces a lot of issues that can markedly increase the complexity
    of programs and make them a maintenance nightmare.

  - first ambiguity can result when multiple base classes contain a function with the same
    name.
*/

namespace ambiguity_problem
{
    class USBDevice
    {
    private:
        long m_id {};

    public:
        USBDevice(long id)
            : m_id { id }
        {
        }

        long getID() const { return m_id; }
    };

    class NetworkDevice
    {
    private:
        long m_id {};

    public:
        NetworkDevice(long id)
            : m_id { id }
        {
        }

        long getID() const { return m_id; }
    };

    class WirelessAdapter: public USBDevice, public NetworkDevice
    {
    public:
        WirelessAdapter(long usbId, long networkId)
            : USBDevice { usbId }, NetworkDevice { networkId }
        {
        }
    };

    void main()
    {
        WirelessAdapter c54G { 5442, 181742 };
        // std::cout << c54G.getID();      // Which getID() do we call?

        // using workaroud: explicitly specify which function we want
        std::cout << c54G.USBDevice::getID();
    }
}

/*
  - Second, and more serious problem is the diamond problem.
  - this occurs when a class multiply inherits from two classes which each inherit from a
    single base class.
  - this leads to a diamond shaped inheritance pattern.
*/

namespace diamond_problem
{
    class PoweredDevice {};

    class Scanner: public PoweredDevice {};
    class Printer: public PoweredDevice {};

    class Copier: public Scanner, public Printer {};
}

/*
  - there are many issues that arise in this context, including whether Copier should have
    one or two copies of PoweredDevice, and how to resolve certain types of ambiguous references.
  - while most of these issues can be addressed through explicit scoping, the maintenance
    overhead added to your classes in order to deal with the added complexity can cause
    development time to skyrocket.
*/


// [ best practice ]
/*---------------------------------------------------------------------------------------
    avoid multiple inheritance unless alternatives lead to more complexity.
---------------------------------------------------------------------------------------*/



//=======================================================================================

int main()
{
    multiple_inheritance::main();
    mixin::main();
    ambiguity_problem::main();

    return 0;
}