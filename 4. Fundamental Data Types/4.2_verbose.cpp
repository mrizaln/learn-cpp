// signed integer (positive and negative)
short s;    // 2 B
int i;      // 4 B   but min is 2 B
long l;     // 8 B
long ll;    // 16 B

// unsigned integer (positive only)
unsigned short us;    // 2 B
unsigned int ui;      // 4 B   but min is 2 B
unsigned long ul;     // 8 B
unsigned long ull;    // 16 B

// unexpected behaviour of unsigned integer
    #include <iostream>
    // this function expects to be called with unsigned integer
    void doSomething(unsigned int x)
    {
        // Run some code x times

        std::cout << "x is " << x << '\n';
    }

    int main()
    {
        unsigned int x{ 3 };
        unsigned int y{ 5 };

        // unexpected behaviour, the result wraps around
        std::cout << x - y << '\n';
        
        // mixing signed and unsigned integers
        signed int s { -1 };
        unsigned int u { 1 };

        if (s < u) // -1 is implicitly converted to 4294967295, and 4294967295 < 1 is false
            std::cout << "-1 is less than 1\n";
        else
            std::cout << "1 is less than -1\n"; // this statement executes

        // this function that expects an unsigned integer is called with a negative integer
        doSomething(-1);    // it will gets implicitly converted to unsigned

        return 0;
    }