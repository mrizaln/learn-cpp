#include <iostream>
#include <string>


/*---------------------------------------------------------------------------------------
                    ============[ the diamond problem ]============
---------------------------------------------------------------------------------------*/

namespace the_diamond_problem
{
    class PoweredDevice
    {
    public:
        PoweredDevice(int power)
        {
            std::cout << "PoweredDevice: " << power << '\n';
        }
    };

    class Scanner: public PoweredDevice
    {
    public:
        Scanner(int scanner, int power)
            : PoweredDevice{ power }
        {
            std::cout << "Scanner: " << scanner << '\n';
        }
    };

    class Printer: public PoweredDevice
    {
    public:
        Printer(int printer, int power)
            : PoweredDevice{ power }
        {
            std::cout << "Printer: " << printer << '\n';
        }
    };

    class Copier: public Scanner, public Printer
    {
    public:
        Copier(int scanner, int printer, int power)
            : Scanner{ scanner, power }, Printer{ printer, power }
        {
        }
    };


    void main()
    {
        Copier copier{ 1, 2, 3 };

        // will output:
        /*------------------------
            PoweredDevice: 3
            Scanner: 1
            PoweredDevice: 3
            Printer: 2
        ------------------------*/
        // PoweredDevice class got constructed twice (which should be not)

        /*
        what happened:

            [PoweredDevice]     [PoweredDevice]
                   ↑                   ↑
                   |                   |
               [Scanner]           [Printer]
                        ⬉         ⬈
                          \     /
                          [Copier]
            
        what should have happenned:

                      [PoweredDevice]
                          ⬈     ⬉
                        /         \
               [Scanner]           [Printer]
                        ⬉         ⬈
                          \     /
                          [Copier]
        */
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ virtual base classes ]============
---------------------------------------------------------------------------------------*/

/*
  - to share a base class, simply insert the "virtual" keyword in the inheritance list of
    the derived class.
  - this creates what is called a [virtual base class], which means there is only one base
    object.
  - the base object is shared between all objects in the inheritance tree an it is only
    constructed once.
*/

namespace virtual_base_class
{
    class PoweredDevice
    {
    public:
        PoweredDevice(int power)
        {
            std::cout << "PoweredDevice: " << power << '\n';
        }
    };

    class Scanner: virtual public PoweredDevice // note: PoweredDevice is now a virtual base class
    {
    public:
        Scanner(int scanner, int power)
            : PoweredDevice{ power } // this line is required to create Scanner objects, but ignored in this case
        {
            std::cout << "Scanner: " << scanner << '\n';
        }
    };

    class Printer: virtual public PoweredDevice // note: PoweredDevice is now a virtual base class
    {
    public:
        Printer(int printer, int power)
            : PoweredDevice{ power } // this line is required to create Printer objects, but ignored in this case
        {
            std::cout << "Printer: " << printer << '\n';
        }
    };

    class Copier: public Scanner, public Printer
    {
    public:
        Copier(int scanner, int printer, int power)
            : PoweredDevice{ power }, // PoweredDevice is constructed here
            Scanner{ scanner, power }, Printer{ printer, power }
        {
        }
    };


    void main()
    {
        Copier copier{ 1, 2, 3, };

        // no problem happened :)
    }
}

// The Copier constructor is responsible for creating PoweredDevice. Consequently, this is
// one time when Copier is allowed to call a non-immediate-parent constructor directly




//=======================================================================================

int main()
{
    the_diamond_problem::main();
    virtual_base_class::main();

    return 0;
}