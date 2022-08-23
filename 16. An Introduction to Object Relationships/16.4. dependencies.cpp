#include <iostream>


/*---------------------------------------------------------------------------------------
                    ============[ dependencies ]===========
---------------------------------------------------------------------------------------*/

/*
  - a [dependency] occurs when one object invokes another object's functionality in order
    to accomplish some specific task.
  - this is a weaker relationship than an association, but still, any change to object
    being depended upon may break functionality in the (dependent) caller.
  - a dependency is always a unidirectional relationship.

  - a good example of a dependency is std::ostream.
  - our classes that use std::ostream use it in order to accomplish the task of printing
    something to the console, but not otherwise.
*/

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0): m_x{x}, m_y{y}, m_z{z}
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point& point); // Point has a dependency on std::ostream here
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';

    return out;
}

int main()
{
    Point point1 { 2.0, 3.0, 4.0 };

    std::cout << point1; // the program has a dependency on std::cout here

    return 0;
}




/*---------------------------------------------------------------------------------------
              ============[ dependencies vs association in C++ ]============
---------------------------------------------------------------------------------------*/

/*
  - in C++, associations are a relationships between two classes at the class level.
  - that is, one class keeps a direct or indirect "link" to the associated class as a member.

  - dependencies typically are not represented at the class level -- that is, the object being
    depended on is not linked as a member.
*/