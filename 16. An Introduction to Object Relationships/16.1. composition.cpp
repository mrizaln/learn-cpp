#include <iostream>
#include <string>
#include <string_view>


/*---------------------------------------------------------------------------------------
                    ============[ object composition ]============
---------------------------------------------------------------------------------------*/

/*
  - in real-life, complex objects are often built from smaller, simpler objects.
  - for example, you are build from smaller pars: you have a head, body, legs, arms, etc.
  - the process of building complex object from simpler ones is called [object composition].

  - object composition models a ["has-a"] relationship between two object.
  - the complex object is sometimes called the whole, or the parent.
  - the simpler object is often called the part, child, or component.

  - in C++, structs and classes can have data members of various types.
  - when we build classes with data members, we're essestially constructing a complex object
    from simpler parts, which is object composition.
  - thus, structs and classes are sometimes referred to as [composite types].
*/




/*---------------------------------------------------------------------------------------
                ============[ types of object composition ]===========
---------------------------------------------------------------------------------------*/

/*
  - there two subtypes of object composition:
    1. composition      (discussed in this lesson)
    2. aggregate        (next lesson)
*/




/*---------------------------------------------------------------------------------------
                        ============[ composition ]===========
---------------------------------------------------------------------------------------*/

/*
  - to qualify as a [composition], an object and a part must have the following relationship:
    1. the part (member) is part of the object (class)
    2. the part (member) can only belong to one object (class) at a time
    3. the part (member) has its existence managed by the object (class)
    4. the part (member) does not know about the existence of the object (class)

  - composition models ["part-of"] relationships.
  - example: a heart is part-of a body.

  - the parts of a composition can be singular or multiplicative.

  - conposition is often used to model physical relationships, were one object is physically
    contained inside another.
  - in a composition relationship, the whole object is responsible for the existence of the
    part.

  - compositions are typically created as structs or classes with normal data members.
*/



/*---------------------------------------------------------------------------------------
                        ============[ example ]============
---------------------------------------------------------------------------------------*/

/*
    Many games and simulations have creatures or objects that move around a board, map,
    or screen. One thing that all of these creatures/objects have in common is that they
    all have a location. In this example, we are going to create a creature class that uses
    a point class to hold the creature’s location.
*/

namespace composition
{
    // location
    class Point2D
    {
    private:
        int m_x{};
        int m_y{};

    public:
        Point2D() = default;

        Point2D(int x, int y)
            : m_x{ x }
            , m_y{ y }
        {
        }

        void setPoint(int x, int y)
        {
            m_x = x;
            m_y = y;
        }

        friend std::ostream& operator<<(std::ostream& out, const Point2D& p)
        {
            out << '(' << p.m_x << ", " << p.m_y << ')';
            return out;
        }
    };

    // creature
    class Creature
    {
    private:
        std::string m_name{};
        Point2D m_location{};

    public:
        Creature(const std::string_view name, const Point2D& location)
            : m_name{ name }
            , m_location{ location }
        {
        }

        void moveTo(int x, int y)
        {
            m_location.setPoint(x, y);
        }

        friend std::ostream& operator<<(std::ostream& out, const Creature& p)
        {
            out << p.m_name << " is at " << p.m_location;
            return out;
        }
    };

    void main()
    {
        std::string name{};
        std::cout << "Enter a name for your creature: ";
        std::cin >> name;
        Creature creature{ name, { 4, 7} };

        while (true)
        {
            std::cout << creature << '\n';

            int x{};
            std::cout << "Enter new X location for creature (-1 to quit): ";
            std::cin >> x;
            if (x == -1) break;

            int y{};
            std::cout << "Enter new Y location for creature (-1 to quit): ";
            std::cin >> y;
            if (y == -1) break;

            creature.moveTo(x, y);
        }
    }
}


/*
  - one question that new programmers often ask when it comes to object composition is,
    "when should i use a class member instead of direction implementation of a feature?".
*/

// [ tip ]
/*---------------------------------------------------------------------------------------
    a good rule of thum is that each class should be built to accomplish a single task.
    that task should either be the storage and manipulation of some kind of data, or the
    coordination of its members. ideally not both.
---------------------------------------------------------------------------------------*/




//=======================================================================================

int main()
{
    composition::main();

    return 0;
}