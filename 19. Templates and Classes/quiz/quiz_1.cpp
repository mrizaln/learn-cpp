#include <iostream>
#include <string>


// [ description ]
/*---------------------------------------------------------------------------------------
 a) write a templated class named Pair1 that allows the user to define one template type
    that is used for both values in the pair.

 b) write a Pair class that allows you to specify separate types for each of the values
    in the pair.

 c) a string-value pair is a special type of pair where the first value is always a
    string type, and the second value can be any type. write a template class named
    StringValuePair that inherits from a partially specialized Pair class (using
    std::string) as the first type, and allowing the user to specify the second type.

---------------------------------------------------------------------------------------*/

// a)   [obsolete; replaced with Pair<T,T>]
template <typename T>
class Pair1
{
private:
    T m_first{};
    T m_second{};

public:
    Pair1(T value1, T value2)
        : m_first{ value1 }
        , m_second{ value2 }
    {
    }

    T& first() { return m_first; }
    T& second() { return m_second; }
    const T& first() const { return m_first; }
    const T& second() const { return m_second; }
};


// b)
template <typename T_1, typename T_2=T_1>       // second parameter default argument is first parameter
class Pair
{
private:
    T_1 m_first{};
    T_2 m_second{};

public:
    Pair(T_1 value1, T_2 value2)
        : m_first{ value1 }
        , m_second{ value2 }
    {
    }

    T_1& first() { return m_first; }
    T_2& second() { return m_second; }
    const T_1& first() const { return m_first; }
    const T_2& second() const { return m_second; }
};

// c)
template <typename T>
class StringValuePair : public Pair<std::string, T>
{
public:
    StringValuePair(const std::string& string, T value)
        : Pair<std::string, T>::Pair{ string, value }
    {
    }
};


int main()
{
    // a)
	Pair<int> p1 { 5, 8 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double> p2 { 2.3, 4.5 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    // b)
    Pair<int, double> pp1 { 5, 6.7 };
	std::cout << "Pair: " << pp1.first() << ' ' << pp1.second() << '\n';

	const Pair<double, int> pp2 { 2.3, 4 };
	std::cout << "Pair: " << pp2.first() << ' ' << pp2.second() << '\n';

    // c)
    StringValuePair<int> svp { "Hello", 5 };
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

	return 0;
}