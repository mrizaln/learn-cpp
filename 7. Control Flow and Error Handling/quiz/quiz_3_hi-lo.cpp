#include <iostream>
#include <random>
#include <limits>

namespace Random
{
    constexpr int MIN { 1 };
    constexpr int MAX { 100 };

    std::random_device rd;
    std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 mt { ss };

    // returns a number between Random::MIN and Random::MAX
    int getRandomNumber()
    {
        std::uniform_int_distribution num { MIN, MAX };
        return num(mt);
    }
}

// get guesss number from user
int getGuessNumber(int guess)
{
    while (true)
    {
        int num {};
        std::cout << "Guess #" << guess << ": ";
        std::cin >> num;

        if (std::cin.fail() || num < Random::MIN || num > Random::MAX)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please input an integer from " << Random::MIN << " to " << Random::MAX << ".\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return num;
        }
    } 
}

// ask user whether to play again or not. returns true if user accepts
bool askToPlayAgain()
{
    while (true)
    {
        char confirmation {};
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> confirmation;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (confirmation)
        {
        case 'y': return true;
        case 'n': return false;
        }
    }
}

// evaluate user guess number
bool evaluate(int randomNumber, int guessNumber)
{
    if (guessNumber > randomNumber)
    {
        std::cout << "Your guess is too high.\n";
        return false;
    }
    else if (guessNumber < randomNumber)
    {
        std::cout << "Your guess is too low.\n";
        return false;
    }
    else
        return true;
}


int main()
{
    constexpr int MAX_GUESS { 7 };

    bool finished { false };
    while (! finished)
    {
        std::cout << "Let's play a game. I'm thinking of a number. You have 7 tries to guess what it is.\n";
        int randomNumber { Random::getRandomNumber() };

        int guessCount { 1 };
        bool win { false };
        while (! win && guessCount <= MAX_GUESS)
        {
            int guessNumber { getGuessNumber(guessCount) };
            win = evaluate(randomNumber, guessNumber);
            ++guessCount;
        }

        switch (win)
        {
        case true: std::cout << "Correct! You win!\n"; break;
        case false: std::cout << "Sorry, you lose. The correct number was " << randomNumber << ".\n"; break;
        }

        finished = ! askToPlayAgain();
    }

    std::cout << "Thank you for playing.\n";

    return 0;
}