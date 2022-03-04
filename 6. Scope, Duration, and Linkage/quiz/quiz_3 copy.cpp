#include <iostream>

bool passOrFail()
{
    static char s_passCount { 3 };

    std::cout << (int)s_passCount;

    if (s_passCount > 0)
        return s_passCount--;       // return the copy of s_passCount, then decrement it

    return s_passCount;
}

bool passOrFail_better()
{
    static char s_passes = 3;
    --s_passes;
    std::cout << (int)s_passes;
    return (s_passes >= 0);     // return the bool
}

int main()
{
	for (int user { 0 }; user < 140; user++)
    {
        std::cout << "User #" << user << " :" << (passOrFail() ? "Pass\n" : "Fail\n");
    }

	return 0;
}