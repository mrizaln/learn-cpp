#include <iostream>
#include <array>
#include <algorithm>    // std::shuffle
#include <numeric>      // std::reduce
#include <random>
#include <ctime>

/*---------------------------------------------------------------------------------------
            ============[ introducing a couple of new algorithm ]============
---------------------------------------------------------------------------------------*/

// std::reduce applies a function, by default the operator+, to all elements in a list,
// resulting in a single value.
// note that there's also std::accumulate, but it cannot be parallelized unlike std::reduce.

// std::shuffle takes a list and randomly re-orders its elements.

int main()
{
    std::array arr{ 1, 2, 3, 4 };

    // reduce
    std::cout << std::reduce(arr.begin(), arr.end()) << '\n';

    // reduce with initial value 5
    std::cout << std::reduce(arr.begin(), arr.end(), 5) << '\n';

    // shuffle
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(arr.begin(), arr.end(), mt);

    // print
    for (int i : arr)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}