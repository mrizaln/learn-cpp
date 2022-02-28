//========[ string output ]========
#include <iostream>
#include <string>

int main_0()
{
    std::string myName{ "Rizal" };
    std::cout << "My name is: " << myName << '\n';

    return 0;
}

//========[ string input with std::cin ]========
int main_1()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::cin >> name;   // this won't work as expected since std::cin breaks on whitespace

    std::cout << "Enter your age: ";
    std::string age{};
    std::cin >> age;
    
    std::cout << "Your name is " << name << " and your age is " << age << std::endl;

    return 0;
}

//========[ use std::getline() to input text ]========
int main_2()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name);    // read a full line of text into name

    std::cout << "Enter your age: ";
    std::string age{};
    std::getline(std::cin >> std::ws, age);     // read a full line of text into name

    std::cout << "Your name is " << name << " and your age is " << age << std::endl;

    return 0;
}

// what the heck is std::ws
    // the   std::ws   is an input manipulator that tells   std::cin   to ignore any leading whitespace
int main_3()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;             // suppose we input 2

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin, name); // note: no std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
/*
     It turns out, when you enter a value using operator>>, std::cin not only captures the
    value, it also captures the newline character ('\n') that occurs when you hit the enter
    key. So when we type 2 and then hit enter, std::cin gets the string "2\n". It then
    extracts the 2 to variable choice, leaving the newline character behind for later. Then,
    when std::getline() goes to read the name, it sees "\n" is already in the stream, and
    figures we must have previously entered an empty string! Definitely not what was intended.

     We can amend the above program to use the std::ws input manipulator, to tell std::getline()
    to ignore any leading whitespace characters:
*/
int main_3_fixed()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // note: added std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}

// string length
int main_4()
{
    std::string myName{ "Maiuna" };
    int length { myName.length() };     // will give off warning: unsigned int to signed int conversion
    std::cout << myName << " has " << myName.length() << " characters\n";
    return 0;
}




int main()
{
    main_4();
}
