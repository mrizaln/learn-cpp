#include <iostream>
#include <cstdint>      // for fixed width integers
#include <cmath>        // for std::round()


// [ description ]
/*---------------------------------------------------------------------------------------
    a floating point number is a number with a decimal where the number of digits after
    the decimal can be variable. a fixed point number is a number with a fractional
    component where the number of digits in the fractional portion is fixed.

    write a class named FixedPoint2 that implements a fixed point number with two
    fractional digits. if either (or both) of the non-fractional and fractional part of
    the number are negative, the number should be treated as negative.
---------------------------------------------------------------------------------------*/

class FixedPoint2
{
private:
    std::int16_t m_base{};        // non-fractional part
    std::int8_t m_fraction{};     // fractional part

    void checkNegative()
    {
        if (m_base < 0 && m_fraction > 0)
            m_fraction = -m_fraction;
        else if (m_base > 0 && m_fraction < 0)
            m_base = -m_base;
    }

    void normalize()
    {
        if (m_fraction >= 100)
        {
            m_base += 1;
            m_fraction -= 100;
        }
        else if (m_fraction <= -100)
        {
            m_base -= 1;
            m_fraction += 100;
        }
    }

public:
    FixedPoint2(std::int16_t base, std::int8_t fraction)
        : m_base{ base }
        , m_fraction{ fraction }
    {
        checkNegative();
        normalize();
    }

    FixedPoint2(double number)
        : m_base{ static_cast<std::int16_t>(std::round(number)) }
        , m_fraction{ static_cast<std::int8_t>(std::round(100*(number - m_base))) }
    {
    }

    operator double() const
    {
        return static_cast<double>(m_fraction)/100 + m_base;
    }

    FixedPoint2 operator-() const
    {
        return {
            static_cast<std::int16_t>(-m_base),         // we need the cast because the operator-
            static_cast<std::int8_t>(-m_fraction)       // narrow integer types to int.
        };
    }

    friend bool operator==(const FixedPoint2& p1, const FixedPoint2& p2);
    friend std::ostream& operator<<(std::ostream& out, const FixedPoint2& p);
    friend std::istream& operator>>(std::istream& in, FixedPoint2& p);
    friend FixedPoint2 operator+(const FixedPoint2& p1, const FixedPoint2& p2);
};

bool operator==(const FixedPoint2& p1, const FixedPoint2& p2)
{
    return (p1.m_base == p2.m_base && p1.m_fraction == p2.m_fraction);
}

std::ostream& operator<<(std::ostream& out, const FixedPoint2& p)
{
    // out.precision(2);
    out << static_cast<double>(p);
    return out;
}

std::istream& operator>>(std::istream& in, FixedPoint2& p)
{
    double number{};
    in >> number;
    p = number;     // implicit conversion from double to FixedPoint2 using FixedPoint2(double) constructor
    return in;
}

FixedPoint2 operator+(const FixedPoint2& p1, const FixedPoint2& p2)
{
    return { static_cast<double>(p1) + static_cast<double>(p2) };
}


void testAddition()
{
	// h/t to reader Sharjeel Safdar for this function
	std::cout << std::boolalpha;
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 }) << '\n';        // both positive,   no decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 }) << '\n';        // both positive,   with decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }) << '\n';     // both negative,   no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }) << '\n';     // both negative,   with decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 }) << '\n';      // second negative, no decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 }) << '\n';      // second negative, possible decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 }) << '\n';       // first negative,  no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 }) << '\n';       // first negative,  possible decimal overflow
}



int main()
{
    // using FixedPoint2(std::int16_t, std::int8_t) constructor
    //----------------------------------------------------------
	FixedPoint2 a{ 34, 56 };
	std::cout << a << '\n';

	FixedPoint2 b{ -2, 8 };
	std::cout << b << '\n';

	FixedPoint2 c{ 2, -8 };
	std::cout << c << '\n';

	FixedPoint2 d{ -2, -8 };
	std::cout << d << '\n';

	FixedPoint2 e{ 0, -5 };
	std::cout << e << '\n';

	std::cout << static_cast<double>(e) << '\n';

    // using FixedPoint2(double) constructor
    //---------------------------------------
    // Handle cases where the argument is representable directly
	FixedPoint2 aa{ 0.01 };
	std::cout << aa << '\n';

	FixedPoint2 bb{ -0.01 };
	std::cout << bb << '\n';

	// Handle cases where the argument has some rounding error
	FixedPoint2 cc{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	std::cout << cc << '\n';

	FixedPoint2 dd{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	std::cout << dd << '\n';

	// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	FixedPoint2 ee{ 106.9978 }; // should be stored with base 107 and decimal 0
	std::cout << ee << '\n';

    // operators
    //-----------
    testAddition();

	FixedPoint2 aaa{ -0.48 };
	std::cout << aaa << '\n';

	std::cout << -aaa << '\n';

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> aaa;

	std::cout << "You entered: " << aaa << '\n';

	return 0;
}