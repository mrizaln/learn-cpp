#include <iostream>
#include <ctime>        // for std::time()
#include <cstdlib>      // for std::rand() and std::srand()


// description
/*---------------------------------------------------------------------------------------
    random monster generator

    a) create an enumeration of monster types named MonsterType. include the following
       monster types: Dragon, Goblin, Ogre, Orc, Skeleton, Troll, Vampire, and Zombie.
       add an additional max_monster_types enum so we can count how many enumerators
       there are.

    b) create a Monster class. It will have 4 attributes: a type (MonsterType), a name
       (std::string), a roar (std::string), and the number of hit points (int).

    c) move the MonsterType enumeration inside Monster class, rename to Type

    d) create a constructor that allows you to initialize all of the member variables.

    e) write a function called getTypeString to get a string representation of 
       Monster::Type and a print function that prints the class' object.

    f) now we can create a random monster generator: create a static function named
       generateMonster(). this should return a Monster. For now, make it return anonymous
       Monster(Monster::Type::skeleton, "Bones", "*rattle*", 4).

    g) now, monster generator needs to generate some random attributes. to do that make a
       function that returns a random number. then put it as a static function inside
       MonsterGenerator class.

    h) now edit function generateMonster() to generate a random Monster::Type (between 0
       and Monster::Type::max_mosnter_types-1) and a random hit points (between 1 and
       100). once you've done that, define two static fixed arrays of size 6 inside the
       function (named s_names and s_roars) and initialize them with 6 names and 6 sounds
       of your choice. pick a random name and roar from these arrays.
---------------------------------------------------------------------------------------*/


// b)
class Monster
{
public:
    // a), c)
    enum class Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,

        max_monster_types
    };

private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_hitPoints{};

public:
    // d)
    Monster(Type type, std::string name, std::string roar, int hitPoints)
        : m_type{ type }
        , m_name{ name }
        , m_roar{ roar }
        , m_hitPoints{ hitPoints }
    {
    }

    // e)
    std::string getTypeString()
    {
        switch (m_type)
        {
        case Type::dragon  : return "dragon";
        case Type::goblin  : return "goblin";
        case Type::ogre    : return "ogre";
        case Type::orc     : return "orc";
        case Type::skeleton: return "skeleton";
        case Type::troll   : return "troll";
        case Type::vampire : return "vampire";
        case Type::zombie  : return "zombie";
        default            : return "???";
        }
    }

    void print()
    {
        std::cout << m_name
                  << " the "
                  << getTypeString()
                  << " has "
                  << m_hitPoints
                  << " hit points and says "
                  << m_roar
                  << '\n';
    }
};

// f)
class MonsterGenerator
{
public:
    // f) h)
    static Monster generateMonster()
    {
        static std::string s_names[6]{ "dsf", "awesr", "fyutd", "ers ye", "jenr", "gfih" };
        static std::string s_roars[6]{ "a", "erwqzacxxzzz", "douysssss", "efgroiusss", "kxzckjkz", "zazazaza" };

        auto type{ static_cast<Monster::Type>(getRandomNumber(0, static_cast<int>(Monster::Type::max_monster_types)-1)) };
        int hp{ getRandomNumber(1, 100) };
        auto name{ s_names[getRandomNumber(0, std::size(s_names)- 1)] };
        auto roar{ s_roars[getRandomNumber(0, std::size(s_roars)- 1)] };

        return Monster(type, name, roar, hp);
    }

private:
    // g)       assuming srand() has been called
    static int getRandomNumber(int min, int max)
    {
        static constexpr double fraction{ 1.0 / (static_cast<double>(RAND_MAX) + 1.0) };
        return static_cast<int>(std::rand() * fraction * (max - min + 1) + min);
    }
};



int main()
{
    // e)
    Monster skeleton{ Monster::Type::skeleton, "Bones", "*rattle*", 4 };
    skeleton.print();

    // f) h)
    std::srand( static_cast<unsigned int>(std::time(nullptr)));     // set initial seed value to system clock
    std::rand();        // if using visual studio, discard first random value

    Monster m{ MonsterGenerator::generateMonster() };
    m.print();

    return 0;
}