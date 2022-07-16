#include <iostream>
#include <cmath>        // for std::sqrt


// description
/*---------------------------------------------------------------------------------------
    a) write a class named Point2d. Point2d should contain two member variables of type
       double: m_x and m_y, both defaulted to 0.0. provide a constructor and a print
       function
    
    b) now add a member function named distanceTo that takes another Point2d as a
       parameter, and calculates the distance between them.

    c) change function distanceTo from a member function to a non-member friend function
       that takes two Points as parameters. also rename it distanceFrom.
---------------------------------------------------------------------------------------*/


// a)
class Point2d
{
private:
    double m_x{};
    double m_y{};

public:
    Point2d(double x=0, double y=0)
        : m_x{ x }
        , m_y{ y }
    {
    }

    void print()
    {
        std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
    }

    // b)
    double distanceTo(Point2d& p)
    {
        return std::sqrt((m_x - p.m_x)*(m_x-p.m_x) + (m_y - p.m_y)*(m_y - p.m_y));
    }

    // c)
    friend double distanceFrom(Point2d& p1, Point2d& p2);
};

// c)
double distanceFrom(Point2d& p1, Point2d& p2)
{
    return std::sqrt((p1.m_x - p2.m_x)*(p1.m_x-p2.m_x) + (p1.m_y - p2.m_y)*(p1.m_y - p2.m_y));
}



int main()
{
    // a)
    Point2d first{};
    Point2d second{ 3.0, 4.0 };
    first.print();
    second.print();

    // b)
    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';

    // c)
    std::cout << "Distance between two points: " << distanceFrom(first, second) << '\n';

    return 0;
}