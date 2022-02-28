#include <iostream>
//          ^ this thing

int main()
{
    // ======[ std::cout ]======
    // send data to the console to be printed as text using << (insertion operator)
    // stand for: character output
    std::cout << "Heeyyyy\n";

    // ======[ std::endl ]======
    // prints newline character
    std::cout << "Hello :)" << std::endl;

    // ======[ std::endl vs '\n' ]======
    // using std::endl can be abit inefficient, as it actually does two jobs:
    // it moves the cursor to the next line, and it "flushes" the output (makes
    // sure that it shows up on the screen immediately). When writing text to the
    // console using std::cout, std::cout often flushes output anyway (and if it
    // doesn’t, it usually doesn’t matter), so having std::endl perform a flush
    // is rarely important.
    // Because of this, use of the ‘\n’ character is typically preferred instead.
    // The ‘\n’ character moves the cursor to the next line, but doesn’t request
    // a flush,
    // conclusion:
    //==================[ prefer '\n' over std::endl ]==================

    // ======[ std::cin ]======
    // reads input from keyboard using extraction operator (>>)
    int x {}, y {};
    std::cout << "Try to input a number: ";
    std::cin >> x;
    std::cout <<  "You entered: " << x << '\n';

    // it is possible to input more than one value on a single line
    std::cout << "Try to input 2 numbers separataed by space: ";
    std::cin >> x >> y;
    std::cout << "You entered: " << x << " and " << y << '\n';

    return 0;
}