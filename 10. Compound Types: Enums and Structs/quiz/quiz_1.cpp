// [ Description ]
/*---------------------------------------------------------------------------------------
    In designing a game, we decide we want to have monsters, because everyone likes
    fighting monsters. Declare a struct that represents your monster. The monster should
    have a type that can be one of the following: an ogre, a dragon, an orc, a giant
    spider, or a slime. Use an enum class for this.

    Each individual monster should also have a name (use a std::string or
    std::string_view), as well as an amount of health that represents how much damage
    they can take before they die. Write a function named printMonsterMonster() that printMonsters out
    all of the struct’s members. Instantiate an ogre and a slime, initialize them using
    an initializer list, and pass them to printMonsterMonster().
---------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <string_view>

enum class MonsterTypes
{
    ogre,
    dragon,
    orc,
    giant_spider,
    slime,
};

constexpr std::string_view getMonsterTypeName(const MonsterTypes monsterType)
{
    switch (monsterType)
    {
        case MonsterTypes::ogre:         return "Ogre";
        case MonsterTypes::dragon:       return "Dragon";
        case MonsterTypes::orc:          return "Orc";
        case MonsterTypes::giant_spider: return "Giant Spider";
        case MonsterTypes::slime:        return "Slime";
        default:                         return "????";
    }
}

struct Monster
{
    MonsterTypes type {};
    std::string name {};
    int health {};
};

void printMonster(const Monster& m)
{
    std::cout << "This "      << getMonsterTypeName(m.type)\
              << " is named " << m.name\
              << " and has "  << m.health << '\n';
}

int main()
{
    Monster monster1 { MonsterTypes::ogre, "Torg", 145 };
    Monster monster2 { MonsterTypes::slime, "Blurp", 23 };

    printMonster(monster1);
    printMonster(monster2);

    return 0;
}