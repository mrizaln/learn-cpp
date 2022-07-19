#include <iostream>


/*
  - unlike the operators you've seen so far, the positive (+), negative (-), and logical
    not (!) operators all are unary operators, which means they only operate on one operand.
  - because they only operate on the object they are applied to, typically unary operator
    overloads are implemented as member functions.
*/


// [ here unary operator- is being overloaded ]

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents } { }

    // overload -Cents as a member function
    Cents operator-() const;

    int getCents() const { return m_cents; }
};

// note: this function is a member function
Cents Cents::operator-() const
{
    return -m_cents;        // does implicit conversion from int to Cents using the Cents(int) constructor
}



// [ here unary operator- and operator! are being overloaded ]

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
        : m_x{ x }, m_y{ y }, m_z{ z }
    {
    }

    // convert a Point into its negtive equivalent
    Point operator-() const;

    // does nothing actually
    Point operator+() const;

    // return true if the point is set at the origin
    bool operator!() const;

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }
};

// convert a Point into its negative equivalent
Point Point::operator-() const
{
    return { -m_x, -m_y, -m_z };
}

// does nothing actually
Point Point::operator+() const
{
    return *this;
}

// return true if the point is set at the origin
bool Point::operator!() const
{
    return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);
}




int main()
{
    // Cents
    const Cents nickel{ 5 };
    std::cout << "A nickle of debt is worth " << (-nickel).getCents() << " cents.\n";

    // Point
    Point point{};  // use default constructor to (0.0, 0.0, 0.0)

    if (!point)
        std::cout << "point is set at the origin.\n";
    else
        std::cout << "point is not set at the origin.\n";

    return 0;
}