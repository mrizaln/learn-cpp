#include <iostream>


/*---------------------------------------------------------------------------------------
                      ============[ friend functions ]============
---------------------------------------------------------------------------------------*/

/*
  - a [friend function] is a function that can access the private members of a class as though
    it was a member of that class.
  - in all other regards, the friend function is just like a normal function.
  - a friend function may be either a normal function, or a member function of another class.
  - to declare a friend function, simply use the /friend/ keyword in front of the prototype
    of the function you wish to be a friend of the class.
  - it does not matter whether you declare the friend function in the private or public section
    of the class.
*/

namespace friend_function_example
{
    class Accumulator
    {
    private:
        int m_value{ 0 };

    public:
        void add(int value) { m_value += value; }

        // make the reset() function a friend of this class
        friend void reset(Accumulator& accumulator);
    };

    // reset() is now a friend of the accumulator class
    void reset(Accumulator& accumulator)
    {
        // and can access the private data of Accumulator objects
        accumulator.m_value = 0;
    }

    void main_acc()
    {
        Accumulator acc;
        acc.add(5);
        reset(acc);
    }
}

/* 
  - note that we have to pass an Accumulator object to reset().
  - this is because reset() is not a member function; it does not have a *this pointer, nor
    does it have an Accumulator object to work with, unless given one.
*/

namespace friend_function_example
{
    class Value
    {
    private:
        int m_value{};

    public:
        Value(int value)
            : m_value{ value }
        {
        }

        friend bool isEqual(const Value& value1, const Value& value2);
    };

    bool isEqual(const Value& value1, const Value& value2)
    {
        return (value1.m_value == value2.m_value);
    }

    void main_val()
    {
        Value v1{ 5 };
        Value v2{ 6 };
        std::cout << std::boolalpha << isEqual(v1, v2) << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                      ============[ multiple friends ]============
---------------------------------------------------------------------------------------*/

// a function can be a friend of more than one class at the same time

namespace multiple_friends
{
    class Humidity;

    class Temperature
    {
    private:
        int m_temp{};

    public:
        Temperature(int temp=0)
            : m_temp{ temp }
        {
        }

        friend void printWeather(const Temperature& temp, const Humidity& hum);
    };

    class Humidity
    {
    private:
        int m_humidity{};

    public:
        Humidity(int humidity=0)
            : m_humidity{ humidity }
        {
        }

        friend void printWeather(const Temperature& temp, const Humidity& hum);
    };

    void printWeather(const Temperature& temp, const Humidity& hum)
    {
        std::cout << "The temperature is " << temp.m_temp
                  << " and the humidity is " << hum.m_humidity << '\n';
    }

    void main()
    {
        Humidity hum{ 10 };
        Temperature temp{ 12 };

        printWeather(temp, hum);
    }
}




/*---------------------------------------------------------------------------------------
                       ============[ friend classes ]============
---------------------------------------------------------------------------------------*/

// it is also possible to make an entire class a friend of another class.
// this gives all of the members of the friend class access to private members of the other class.

namespace friend_classes
{
    class Storage
    {
    private:
        int m_nValue{};
        double m_dValue{};

    public:
        Storage(int nValue, double dvalue)
            : m_nValue{ nValue }, m_dValue{ dvalue }
        {
        }

        friend class Display;
    };

    class Display
    {
    private:
        bool m_displayIntFirst;

    public:
        Display(bool displayIntFirst)
            : m_displayIntFirst{ displayIntFirst }
        {
        }

        void displayItem(const Storage& storage)
        {
            if (m_displayIntFirst)
                std::cout << storage.m_nValue << '\t' << storage.m_dValue << '\n';
            else
                std::cout << storage.m_dValue << '\t' << storage.m_nValue << '\n';
        }
    };

    void main()
    {
        Storage storage{ 5, 6.7 };
        Display display{ false };

        display.displayItem(storage);
    }
}

/*
  - a few additional notes on friend classes.
    1. even though Display is a friend of Storage, Display has no direct acces to the *this
       pointer of Storage objects.
    2. just because Display is a friend of Storage, that does not mean Storage is also a friend
       of Display.
    3. if class A is a friend of B, and B is a friend of C, that does not mean A is friend
       of C.

  - be careful when using friend functions and classes, because it allows the friend function
    or class to violate encapsulation.
  - if the detauls of the class change, the details of the friend will also be forced to change.

  - limit your use of friend functions and classes to minimum.
*/




/*---------------------------------------------------------------------------------------
                   ============[ friend member functions ]============
---------------------------------------------------------------------------------------*/

/*
  - instead of making an entire class a friend, you can make a single member function a friend.
  - in actuality, this can be alittle trickier than expected: the compiler has to have seen
    the full definition for the class of the friend member function .
*/

namespace friend_member_functions
{
    class Storage;          // forward declaration for class Storage

    class Display
    {
    private:
        bool m_displayIntFirst{};

    public:
        Display(bool displayIntFirst)
            : m_displayIntFirst{ displayIntFirst }
        {
        }

        void displayItem(const Storage& storage);       // forward declaration above needed for this declaration line
    };

    class Storage
    {
    private:
        int m_nValue{};
        double m_dValue{};

    public:
        Storage(int nvalue, double dValue)
            : m_nValue{ nvalue }, m_dValue{ dValue }
        {
        }

        // make the Display::displayItem member function a friend of the Storage class
        // (requires seeing the full declaration of class Display, as above)
        friend void Display::displayItem(const Storage& storage);
    };

    // now we can define Display::displayItem(), which needs to have seen the full definition of class Storage
    void Display::displayItem(const Storage& storage)
    {
        if (m_displayIntFirst)
            std::cout << storage.m_nValue << '\t' << storage.m_dValue << '\n';
        else
            std::cout << storage.m_dValue << '\t' << storage.m_nValue << '\n';
    }


    void main()
    {
        Storage storage{ 5, 6.7 };
        Display display{ false };

        display.displayItem(storage);
    }
}

/*
  - if this seems like a pain -- it is.
  - fortunately, this dance is only necessary because we're trying to do everything in a single
    file.
  - a better solution is to put each class definition in a separate header file, with the member
    function definition in corresponding .cpp files.
*/




//=======================================================================================

//------------
//    quiz
//------------

namespace quiz
{
    class Vector3d;

    class Point3d
    {
    private:
        double m_x{};
        double m_y{};
        double m_z{};

    public:
        Point3d(double x = 0.0, double y = 0.0, double z = 0.0)
            : m_x{x}, m_y{y}, m_z{z}
        {

        }

        void print() const
        {
            std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
        }

        void moveByVector(const Vector3d& v);
    };

    class Vector3d
    {
    private:
        double m_x{};
        double m_y{};
        double m_z{};

    public:
        Vector3d(double x = 0.0, double y = 0.0, double z = 0.0)
            : m_x{x}, m_y{y}, m_z{z}
        {

        }

        void print() const
        {
            std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
        }

        friend void Point3d::moveByVector(const Vector3d& v);
    };

    void Point3d::moveByVector(const Vector3d& v)
    {
        m_x += v.m_x;
        m_y += v.m_y;
        m_z += v.m_z;
    }

    int main()
    {
        Point3d p{1.0, 2.0, 3.0};
        Vector3d v{2.0, 2.0, -3.0};

        p.print();
        p.moveByVector(v);
        p.print();

        return 0;
    }
}



//=======================================================================================

int main()
{
    friend_function_example::main_acc();
    friend_function_example::main_val();

    multiple_friends::main();

    friend_classes::main();

    friend_member_functions::main();

    quiz::main();

    return 0;
}