#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

// [ description ]
/*---------------------------------------------------------------------------------------
    Create a struct that holds a student’s first name and grade (on a scale of 0-100).
    Ask the user how many students they want to enter. Create a std::vector to hold all
    of the students. Then prompt the user for each name and grade. Once the user has
    entered all the names and grade pairs, sort the list by grade (highest first). Then
    print all the names and grades in sorted order.
---------------------------------------------------------------------------------------*/

struct Student
{
    std::string firstName{};       // no whitespace
    int grade{};                   // in 0-100 scale
};


std::vector<Student> getStudents(int numStudents)
{
    // create students vector to hold the values
    std::vector<Student> students(numStudents);

    // input name and grade
    for (int count{ 1 }; auto& student : students)
    {
        // input name
        std::cout << "Enter name  (" << count << "): ";
        std::cin >> student.firstName;

        // input grade
        int grade{};
        std::cout << "Enter grade (" << count << "): ";
        std::cin >> student.grade;

        std::cout << '\n';
        ++count;
    }

    return students;
}


bool compareGradeGreater(const Student& a, const Student& b)
{
    return (a.grade > b.grade);
}


int main()
{
    // ask how many students to enter
    int numStudents{};
    std::cout << "How many students you want to enter? ";
    std::cin >> numStudents;

    // students list
    auto students{ getStudents(numStudents) };

    // sort
    std::ranges::sort(students, compareGradeGreater);

    // print
    for (auto& student : students)
    {
        std::cout << student.firstName
                  << " got a grade of "
                  << student.grade << '\n';
    }

    return 0;
}