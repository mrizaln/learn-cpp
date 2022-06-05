#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>

// [ description ]
/*---------------------------------------------------------------------------------------
    Pretend you’re writing a game where the player can hold 3 types of items: health
    potions, torches, and arrows. Create an enum to identify the different types of
    items, and an std::array to store the number of each item the player is carrying (the
    enumerators are used as indexes of the array). The player should start with 2 health
    potions, 5 torches, and 10 arrows. Write a function called countTotalItems() that
    returns how many items the player has in total. Have your main() function print the
    output of countTotalItems() as well as the number of torches.
---------------------------------------------------------------------------------------*/

enum ItemTypes
{
    item_health_potion,
    item_torch,
    item_arrow,

    max_items
};

using inventory_t = std::array<int, max_items>;

int countTotalItems(const inventory_t& items)
{
    return std::reduce(items.begin(), items.end());
}

int main()
{
    // player inventory
    inventory_t items{ 2, 5, 10 };   // 2 health potions, 5 torches, 10 arrows
    
    std::cout << "The player has a total of "
              << countTotalItems(items) 
              << " item(s)\n";
    
    std::cout << "Including "
              << items[item_torch]
              << " torche(s) in it\n";

    return 0;
}