// a constants is a fixed value that may not be changed
// C++ has two kinds of it: literal constants, and symbolic constants

//========[ literal constants ]========
// literal constants (usually just called literals) are unnamed values inserted directly into the code
#include <iostream>
int example()
{
    bool myNameIsMaiuna { true };   // true is a boolean literal
    std::cout << 3.4;               // 3.4 is a double literal
    return 5;                       // 5 is an integer literal
}

/* literal suffixes
    int     u or U          unsigned int
    int     l or L          long
    int     [uU][lL]        unsigned long
    int     ll or LL        long long
    int     [uU][lL]{2}     unsigned long long
    double  f or F          float
    double  l or L          long double      
*/

// octal and hexadecimal literals
#include <bitset>   // std::bitset for binary printing
void using_oct_n_hex_literals()
{
    int octal{ 012 };   // 0 before the number means this is octal
    std::cout << octal << '\n';
    std::cout << std::oct << octal << '\n';

    int hex{ 0xF2AC };  // 0x before the number means this is hex
    std::cout << std::dec << hex << '\n';
    std::cout << std::hex << hex << '\n';

    int bin{ 0b1010100010101000 };   // 0b means binary
    std::bitset<16> binn{ 0b1010100010101000 };   
    std::cout << std::dec << bin << '\n';
    std::cout << std::dec << binn << '\n';
    std::cout << std::dec << std::bitset<16>{ bin } << '\n';    // will give off a warning: int to bin conversion

    // quotation mark can be used as digit separator
    int bin_too{ 0b101'0001'0000'1111'1101 };
    int value{ 2'132'232 };
}


int main()
{
    using_oct_n_hex_literals();
}