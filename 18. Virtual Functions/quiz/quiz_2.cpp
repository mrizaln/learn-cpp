#include <iostream>
#include <vector>


// [ description ]
/*---------------------------------------------------------------------------------------
 a) Create an abstract class named Shape. This class should have three functions: a pure
    virtual print function that takes and returns a std::ostream&, an overloaded
    operator<< and an empty virtual destructor.

 b) Derive two classes from Shape: a Triangle, and a Circle. The Triangle should have 3
    Points as members. The Circle should have one center Point, and an integer radius.
    Overload the print() function.
    
 c) 
---------------------------------------------------------------------------------------*/

struct Point
{
    using point_type = int;

    point_type m_first{};
    point_type m_second{};
};

std::ostream& operator<<(std::ostream& out, const Point p)
{
    out << "Point(" << p.m_first << ", " << p.m_second << ')';
    return out;
}


// abstract class
class Shape
{
public:
    virtual std::ostream& print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Shape& s)
    {
        return s.print(out);
    }
    virtual ~Shape() = default;
};


class Triangle : public Shape
{
private:
    Point m_point1{};
    Point m_point2{};
    Point m_point3{};

public:
    Triangle(Point point1, Point point2, Point point3)
        : m_point1{ point1 }
        , m_point2{ point2 }
        , m_point3{ point3 }
    {
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Triangle("
            << m_point1 << ", "
            << m_point2 << ", "
            << m_point3 << ')';
        return out;
    }

    ~Triangle() override = default;
};


class Circle : public Shape
{
private:
    Point m_center{};
    int m_radius{};

public:
    Circle(Point center, int radius)
        : m_center{ center }
        , m_radius{ radius }
    {
    }

    std::ostream& print(std::ostream& out) const override
    {
        out << "Circle("
            << m_center << ", "
            << "radius " << m_radius << ')';
        return out;
    }

    int getRadius() const { return m_radius; }

    ~Circle() override = default;
};

int getLargestRadius(std::vector<Shape*> v)
{
    int largestRadius{};
    for (const auto s: v)
    {
        Circle* temp{};
        temp = dynamic_cast<Circle*>(s);
        if (temp)
        {
            largestRadius= (largestRadius > temp->getRadius() ? largestRadius : temp->getRadius());
        }
    }
    return largestRadius;
}


int main()
{
    std::vector<Shape*> v{
        new Circle{Point{ 1, 2 }, 7},
        new Triangle{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }},
        new Circle{Point{ 7, 8 }, 3}
	};

	// print each shape in vector v on its own line here
    for (const auto s: v)
        std::cout << *s << '\n';

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

	// delete each element in the vector here
    for (auto s: v)
        delete s;

	return 0;
}