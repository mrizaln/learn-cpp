#include <iostream>
#include <cstdint>      // for fixed width integers


// [ description ]
/*---------------------------------------------------------------------------------------
    write a class named Average that will keep track of the average of all integers
    passed to it. use two members: the first one should be type [std::int_least32_t],
    and used to keep track of the sum of all the numbers you've seen so far. the
    second should be of type std::int_least8_t, and used to keep track of how many
    numbers you've seen so far. you can divide them to find your average.
---------------------------------------------------------------------------------------*/


class Average
{
private:
    std::int_least32_t m_sum{};
    std::int_least8_t m_num{};

public:
    Average() = default;

    Average& operator+=(const int& x)
    {
        m_sum += static_cast<std::int_least32_t>(x);
        ++m_num;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Average& average);
};

std::ostream& operator<<(std::ostream& out, const Average& average)
{
    out << static_cast<double>(average.m_sum)/average.m_num;
    return out;
}



int main()
{
	Average avg{};

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}