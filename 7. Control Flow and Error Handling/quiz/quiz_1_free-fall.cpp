#include <iostream>
#include "constants_quiz_1.h"

double calculateHeight(double initialHeight, int seconds)
{
    double distanceFallen { myConstants::gravity * seconds * seconds / 2 };
    double heightNow { initialHeight - distanceFallen };

    if (heightNow < 0.0)
        return 0.0;
    else
        return heightNow;
}

bool calculateAndPrintHeight(double initialHeight, int time)
{
    double currentHeight { calculateHeight(initialHeight, time) };
    std::cout << "At " << time << " seconds, the ball is at height: " << currentHeight << '\n';

    return (currentHeight == 0.0);
}

int main()
{
    std::cout << "Enter the initiali height of the tower in meters: ";
    double initialHeight {};
    std::cin >> initialHeight;

    int time { 0 };
    while(!calculateAndPrintHeight(initialHeight, time))
        ++time;

    return 0;
}