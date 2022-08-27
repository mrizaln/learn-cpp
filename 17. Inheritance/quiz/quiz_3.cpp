#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <random>
#include <ctime>
#include <cstdlib>


// [ description ]
/*---------------------------------------------------------------------------------------
    we're going to write a simple game where you fight monsters. the goal of the game is
    to collect as much gold as you can before you die or get to level 20.

    our program is going to conststs of 3 classes: a Creature class, a Player class, and
    a Monster class. Player and Monster both inherit from Creature.

 a) First create the Creature class. Creatures have 5 attributes: A name (std::string),
    a symbol (a char), an amount of health (int), the amount of damage they do per attack
    (int), and the amount of gold they are carrying (int). Implement these as class
    members. Write a full set of getters (a get function for each member). Add three
    other functions: void reduceHealth(int) reduces the Creature’s health by an integer
    amount. bool isDead() returns true when the Creature’s health is 0 or less. void
    addGold(int) adds gold to the Creature.

 b) Now we’re going to create the Player class. The Player class inherits from Creature.
    Player has one additional member, the player’s level, which starts at 1. The player
    has a custom name (entered by the user), uses symbol ‘@’, has 10 health, does 1
    damage to start, and has no gold. Write a function called levelUp() that increases
    the player’s level and damage by 1. Also write a getter for the level member.
    Finally, write a function called hasWon() that returns true if the player has reached
    level 20.

 c) Next up is the Monster class. Monster also inherits from Creature. Monsters have no
    non-inherited member variables.
    First, write an empty Monster class inheriting from Creature, and then add an enum
    inside the Monster class named Type that contains enumerators for the 3 monsters that
    we’ll have in this game: DRAGON, ORC, and SLIME (you’ll also want a max_types
    enumerator, as that will come in handy in a bit).

 d) Each Monster type will have a different name, symbol, starting health, gold, and
    damage. Here is a table of stats for each monster Type:

    Type    Name    Symbol  Health  Damage  Gold
    --------------------------------------------
    dragon  dragon  D       20      4       100
    orc     orc     o       4       2       25
    slime   slime   s       1       1       19

    Next step is to write a Monster constructor, so we can create monsters. The Monster
    constructor should take a Type enum as a parameter, and then create a Monster with
    the appropriate stats for that kind of monster. Because all of our monster attributes
    are predefined (not random), we’ll use a lookup table.

 e) Finally, add a static function to Monster named getRandomMonster(). This function
    should pick a random number from 0 to max_types-1 and return a monster (by value)
    with that Type (you’ll need to static_cast the int to a Type to pass it to the
    Monster constructor).

 f) We’re finally set to write our game logic!

    Here are the rules for the game:

    - The player encounters one randomly generated monster at a time.
    - For each monster, the player has two choices: (R)un or (F)ight.
    - If the player decides to Run, they have a 50% chance of escaping.
    - If the player escapes, they move to the next encounter with no ill effects.
    - If the player does not escape, the monster gets a free attack, and the player
      chooses their next action.
    - If the player chooses to fight, the player attacks first. The monster’s health is
      reduced by the player’s damage.
    - If the monster dies, the player takes any gold the monster is carrying. The player
      also levels up, increasing their level and damage by 1.
    - If the monster does not die, the monster attacks the player back. The player’s
      health is reduced by the monster’s damage.
    - The game ends when the player has died (loss) or reached level 20 (win)
    - If the player dies, the game should tell the player what level they were and how
      much gold they had.
    - If the player wins, the game should tell the player they won, and how much gold
      they had.
---------------------------------------------------------------------------------------*/

int getRandomNumber(int min, int max)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    return std::uniform_int_distribution{ min, max }(mt);
}

//---------------------------------------------------------------------------------------

// a)
class Creature
{
protected:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_damage{};
    int m_gold{};

public:
    Creature(
        std::string_view name,
        char symbol,
        int health,
        int damage,
        int gold
    )
        : m_name{ name }
        , m_symbol{ symbol }
        , m_health{ health }
        , m_damage{ damage }
        , m_gold{ gold }
    {
    }

    void setName(std::string_view name) { m_name = name; }
    void setSymbol(char symbol) { m_symbol = symbol; }
    void setHealth(int health) { m_health = health; }
    void setDamage(int damage) { m_damage = damage; }
    void setGold(int gold) { m_gold = gold; }

    const auto& getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    int getHealth() const { return m_health; }
    int getDamage() const { return m_damage; }
    int getGold() const { return m_gold; }

    bool isDead() { return m_health == 0; }

    void reduceHealth(int reduction)
    {
        m_health -= reduction;

        if (m_health < 0) m_health = 0;
    }

    void addGold(int gold) { m_gold += gold; }
};

// b)
class Player: public Creature
{
private:
    int m_level{};

public:
    Player(std::string_view name)
        : Creature{ name, '@', 10, 1, 0 }
        , m_level{ 1 }
    {
    }

    void leveUp()
    {
        ++m_level;
        ++m_damage;
    }

    int getLevel() const { return m_level; }
    bool hasWon() { return m_level >= 20; }
};

// c)
class Monster: public Creature
{
public:
    enum Type
    {
        dragon,
        orc,
        slime,

        max_types
    };

    static Monster getRandomMonster()
    {
        // static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
        // return { static_cast<Type>(
        //     std::uniform_int_distribution{ 0, static_cast<int>(Type::max_types)-1 }(mt)
        // ) };

        return {
            static_cast<Type>(getRandomNumber(0, static_cast<int>(Type::max_types)-1))
        };
    }

    Monster(Type type)
        : Creature{ getDefaultCreature(type) }
    {
    }

private:
    static const Creature& getDefaultCreature(Type type)
    {
        using MonsterArray = std::array<Creature, static_cast<std::size_t>(Type::max_types)>;
        static const MonsterArray monsterData{ {
            { "dragon", 'D', 20, 4, 100},
            { "orc", 'o', 4, 2, 25 },
            { "slime", 's', 1, 1, 10}
        } };

        return monsterData.at(static_cast<std::size_t>(type));
    }
};


//---------------------------------------------------------------------------------------

Player playerCreation()
{
    std::string name{};
    std::cout << "Enter your name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Welcome, " << name << '\n';
    Player player{ name };

    std::cout << "You have "
              << player.getHealth()
              << " health and are carrying "
              << player.getGold()
              << " gold.\n";

    return player;
}

void attackPlayer(Player& player, Monster& monster)
{
    player.reduceHealth(monster.getDamage());
    std::cout << "The "
              << monster.getName()
              << " hit you for "
              << monster.getDamage()
              << " damage.\n";
}

void attackMonster(Player& player, Monster& monster)
{
    monster.reduceHealth(player.getDamage());
    std::cout << "You hit the "
              << monster.getName()
              << " for "
              << player.getDamage()
              << " damage.\n";

    if (monster.isDead())
    {
        std::cout << "You killed the "
                  << monster.getName()
                  << ".\n";
        player.leveUp();
        std::cout << "You are now level "
                  << player.getLevel()
                  << ".\n";
        player.addGold(monster.getGold());
        std::cout << "You found "
                  << monster.getGold()
                  << "gold.\n";
    }
    else
        attackPlayer(player, monster);
}

// return false if player fled
bool fight(Player& player, Monster& monster)
{
    while (!monster.isDead() && !player.isDead())
    {
        char answer{};
        do
        {
            std::cout << "(R)un or (F)ight: ";
            std::cin >> answer;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (std::tolower(answer) != 'f' && std::tolower(answer) != 'r');

        switch (answer)
        {
        case 'f':
            attackMonster(player, monster);
            break;

        case 'r':
            bool fleeSuccessful{ static_cast<bool>(getRandomNumber(0, 1)) };
            if (fleeSuccessful)
            {
                std::cout << "You successfully fled.\n";
                return false;
            }
            else
            {
                std::cout << "You failed to flee.\n";
                attackPlayer(player, monster);
            }
            break;
        }
    }

    return true;
}

//---------------------------------------------------------------------------------------

int main()
{
    Player player{ playerCreation() };
    Monster monster{ Monster::getRandomMonster() };

    while (!player.hasWon() && !player.isDead())
    {
        std::cout << "You have encountered a "
                  << monster.getName()
                  << " ("
                  << monster.getSymbol()
                  << ").\n";
        
        bool fled { !fight(player, monster) };  

        if (monster.isDead() || fled)
            monster = Monster::getRandomMonster();
    }

    if (player.hasWon())
    {
        std::cout << "You've reached level 20!\n"
                  << "You've won!\n"
                  << "You have "
                  << player.getGold()
                  << " gold now!\n";
    }
    else if (player.isDead())
    {
        std::cout << "You died at level "
                  << player.getLevel()
                  << " and with "
                  << player.getGold()
                  << " gold.\n"
                  << "Too bad you can't take it with you!\n";
    }
}