#include <iostream>

bool passOrFail()
{
    static int s_passCount { 3 };

    if (s_passCount > 0)
        return s_passCount--;       // return the copy of s_passCount, then decrement it

    return s_passCount;
}

bool passOrFail_better()
{
    static int s_passes = 3;
    --s_passes;
    return (s_passes >= 0);     // return the bool
}

int main()
{
	std::cout << "User #1: " << (passOrFail() ? "Pass\n" : "Fail\n");
	std::cout << "User #2: " << (passOrFail() ? "Pass\n" : "Fail\n");
	std::cout << "User #3: " << (passOrFail() ? "Pass\n" : "Fail\n");
	std::cout << "User #4: " << (passOrFail() ? "Pass\n" : "Fail\n");
	std::cout << "User #5: " << (passOrFail() ? "Pass\n" : "Fail\n");

	return 0;
}