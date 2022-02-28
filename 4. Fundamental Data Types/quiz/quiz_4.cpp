// Simulate a ball being dropped off of a tower

#include <iostream>

constexpr float grav = 9.8;

float getTowerHeight()
{
    std::cout << "Enter the height of the tower in meters: ";
    float height{};
    std::cin >> height;
    return height;
}

float getDistanceFallen(int sec)
{
    return (grav * sec * sec) / 2;
}

void printBallHeight(float towerHeight, int sec)
{
    float ballHeight { towerHeight - getDistanceFallen(sec) };
    if (ballHeight > 0){
        std::cout << "At " << sec << " seconds, the ball is at height: " << ballHeight<< " meters\n";
    }
    else {
        std::cout << "At " << sec << " seconds, the ball is on the ground.\n";
    }
}

int main()
{
    float towerHeight{ getTowerHeight() };

    // ball is falling
    printBallHeight(towerHeight, 0);
    printBallHeight(towerHeight, 1);
    printBallHeight(towerHeight, 2);
    printBallHeight(towerHeight, 3);
    printBallHeight(towerHeight, 4);
    printBallHeight(towerHeight, 5);
}