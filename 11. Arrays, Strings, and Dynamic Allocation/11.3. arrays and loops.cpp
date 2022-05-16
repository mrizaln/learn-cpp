#include <iostream>
#include <iterator>

/*---------------------------------------------------------------------------------------
                    ============[ loops and arrays ]============
---------------------------------------------------------------------------------------*/

// when a loop is used access each array element in turn, this is often called [iterating]
// through the array.

namespace iterating_through_an_array
{
    int main()
    {
        constexpr int scores[] { 84, 92, 76, 81, 56 };
        constexpr int numStudents { static_cast<int>(std::size(scores)) };

        int totalScore { 0 };

        for (int student { 0 }; student < numStudents; ++student)
            totalScore += scores[student];

        auto averageScore { static_cast<double>(totalScore) / numStudents };

        std::cout << averageScore << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                  ============[ mixing loops and arrays ]============
---------------------------------------------------------------------------------------*/

/*
    loops are typically used with arrays to do one of three things:
        - calculate a value (e.g. average, total value)
        - search for a value (e.g. highest value, lowest value)
        - reorganize the array (e.g. ascending order, descending order)
*/




//=======================================================================================

/*----------
    quiz    
----------*/

namespace quiz_1
{
    /*
        print an array
    */
    
    constexpr int array[] { 4, 5, 6, 7, 3, 8, 2, 1, 9, 5 };
    constexpr int arraySize { static_cast<int>(std::size(array)) };

    void print()
    {
        for (int arrIndex { 0 }; arrIndex < arraySize; ++arrIndex)
            std::cout << array[arrIndex] << ' ';
            
        std::cout << '\n';
    }
}


namespace quiz_2
{
    /*
        Ask the user for a number between 1 and 9. If the user does not enter a number
        between 1 and 9, repeatedly ask for an integer value until they do. Once they
        have entered a number between 1 and 9, print the array. Then search the array for
        the value that the user entered and print the index of that element.
    */

    using quiz_1::array;    // use array in quiz 1

    int getInteger()
    {
        int inputInt { 0 };
        while (!(inputInt <= 9 && inputInt >= 1))
        {
            std::cout << "Please enter an integer between 1 and 9: ";
            std::cin >> inputInt;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input\n";
            }
        }

        return inputInt;
    }

    int main()
    {
        int inputInt { getInteger() };

        int inputtedIntIndex { -1 };
        for (int arrIndex { 0 }; arrIndex < static_cast<int>(std::size(array)); ++arrIndex)
            {
                std::cout << array[arrIndex] << ' ';
                if (inputInt == array[arrIndex])
                    inputtedIntIndex = arrIndex;
            }
        
        std::cout << '\n';
        
        std::cout << "Number " << inputInt << " has index " << inputtedIntIndex << '\n';

        return 0;
    }
}


namespace quiz_3
{
    int main()
    {
        constexpr int scores[] { 84, 92, 76, 81, 56 };
        
        int maxIndex { 0 };

        for (int student { 0 }; student < static_cast<int>(std::size(scores)); ++student)
        {
            if (scores[student] > scores[maxIndex]) maxIndex = student;
        }

        std::cout << "The best score was " << scores[maxIndex] << '\n';

        return 0;
    }
}


//=======================================================================================

int main()
{
    iterating_through_an_array::main();
    quiz_1::print();
    // quiz_2::main();
    quiz_3::main();

    return 0;
}