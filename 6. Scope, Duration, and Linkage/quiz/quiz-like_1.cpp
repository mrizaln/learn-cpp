#include <iostream>

int getInput(std::string prompt)
{
    std::cout << prompt;
    int theInput {};
    std::cin >> theInput;
    return theInput;
} // theInput dies here

int main()
{
    int smaller = getInput("Enter an integer: ");
    int larger = getInput("Enter a larger integer: ");

    if (smaller > larger)
    {
        std::cout << "Swapping the values\n";
        int temp { smaller };
        smaller = larger;
        larger = temp;
    } // temp dies here

    std::cout << "The smaller value is " << smaller << '\n';
    std::cout << "The bigger value is " << larger << '\n';
} // smaller and larger dies here