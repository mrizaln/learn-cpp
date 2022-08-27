#include <iostream>
#include <string>
#include <string_view>


// [ description ]
/*---------------------------------------------------------------------------------------
 a) write an Apple class and a Banana class that are derived from a a common Fruit class.
    Fruit class should have two members: a name and a color.

 b) add a new class to the previous program called GrannySmith that inhrits from Apple.
---------------------------------------------------------------------------------------*/

class Fruit
{
protected:
    std::string m_name{};
    std::string m_color{};

public:
    Fruit(std::string_view name, std::string_view color)
        : m_name{ name }
        , m_color{ color }
    {
    }

    const std::string& getName() const { return m_name; }
    const std::string& getColor() const { return m_color; }
};

class Apple: public Fruit
{
public:
    Apple()
        : Fruit{ "apple", "red" }
    {
    }

    Apple(std::string_view color)
        : Fruit{ "apple", color }
    {
    }

    Apple(std::string_view name, std::string_view color)
        : Fruit{ name, color }
    {
    }
};

class Banana: public Fruit
{
public:
    Banana()
        : Fruit{ "banana", "yellow" }
    {
    }

    Banana(std::string_view color)
        : Fruit{ "banana", color }
    {
    }
};

class GrannySmith: public Apple
{
public:
    GrannySmith()
        : Apple{ "granny smith apple", "green" }
    {
    }
};


//---------------------------------------------------------------------------------------

int main()
{
	Apple a{ "red" };
	Banana b;
    GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

	return 0;
}