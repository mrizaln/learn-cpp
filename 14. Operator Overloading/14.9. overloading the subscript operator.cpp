#include <iostream>


/*---------------------------------------------------------------------------------------
                   ============[ overloading operator[] ]============
---------------------------------------------------------------------------------------*/

/*
  - the subscript operator is one of the operators that mst be overloaded as a member function
  - an overloaded operator[] function will always take one parameter: the subscript that the
    user places between the hard braces.
*/

namespace overloading_subscript_operator
{
    class IntList
    {
    private:
        int m_list[10]{};

    public:
        int& operator[](int index);
    };

    int& IntList::operator[](int index)
    {
        return m_list[index];
    }


    void main()
    {
        IntList list{};
        list[2] = 3;                        // set a value
        std::cout << list[2] << '\n';       // get a value
    }
}




/*---------------------------------------------------------------------------------------
              ============[ why operator[] returns a reference ]============
---------------------------------------------------------------------------------------*/

/*
  - let's take a closer look at how list[2] = 3 evaluates.
  - because the subscript operator has a higher precedence than the assignment operator,
    list[2] evaluates first.
  - list[2] which we've defined to return a reference to list.m_list[2].
  - because operator[] is returning a reference, it returns the actual list.m_list[2] array
    element.
  - our partially evaluated expression becomes list.m_list[2] = 3, which is a straightforward
    integer assignment.
*/




/*---------------------------------------------------------------------------------------
                ============[ dealing with const objects ]============
---------------------------------------------------------------------------------------*/

/*
  - in the above IntList example, operator[] is non-const, and we can use it as an l-value
    to change the state of non-const objects.
  - however, what if our IntList object was const?
  - in this case, we wouldn't be able to call the non-const version of operator[] because
    that would allow us to potentially change the state of a const object.

  - the good news is tat we can define a non-const and a const version of operator[] separately.
*/

namespace dealing_with_const_objects
{
    class IntList
    {
    private:
        int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };     // initial state (for this example)

    public:
        int& operator[](int index);
        int operator[](int index) const;   // could also return const reference if returning a non-fundamental type
    };

    int& IntList::operator[](int index)         // for non-const objects
    {
        return m_list[index];
    }

    int IntList::operator[](int index) const    // for const objects
    {
        return m_list[index];
    }


    void main()
    {
        IntList list{};
        list[2] = 3;        // okay
        std::cout << list[2] << '\n';

        const IntList clist{};
        // clist[2] = 3;       // compile error: calls const version of operator[]
        std::cout << clist[2] << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                      ============[ error checking ]============
---------------------------------------------------------------------------------------*/

/*
  - one other advantage of overloading the subscript operator is that we can make it safer
    than accessing arrays directly.
  - normally, whan accessing arrays, the subscript operator does not check whether the index
    is valid.
  - however, if we know the size of our array, we can make our overloaded subscript operator
    check to ensure the index is within bounds.
*/

#include <cassert>      // for assert();
#include <iterator>     // for std::ssize()

namespace error_checking
{
    class IntList
    {
    private:
        int m_list[10]{};

    public:
        int& operator[](int index);
        const int& operator[](int index) const;
    };

    int& IntList::operator[](int index)
    {
        assert(index >= 0 && index < std::ssize(m_list));        // make sure the index is valid
        return m_list[index];
    }

    const int& IntList::operator[](int index) const
    {
        assert(index >= 0 && index < std::ssize(m_list));        // make sure the index is valid
        return m_list[index];
    }
}




/*---------------------------------------------------------------------------------------
   ============[ pointers to objects and overloaded operator[] don't mix ]============
---------------------------------------------------------------------------------------*/

// if you try to call operator[] on a pointer to an object, C++ will assume you're trying
// to index an array of objects of that type.

namespace pointer_and_overloaded_subscript_operator_dont_mix
{
    class IntList
    {
    private:
        int m_list[10]{};

    public:
        int& operator[](int index);
    };

    int& IntList::operator[](int index)
    {
        return m_list[index];
    }


    void main()
    {
        IntList* list{ new IntList{} };
        // list[2] = 3;                        // error: this will assume we're acessing index 2 of an array of IntLists
        (*list)[2] = 3;         // proper syntax

        delete list;
    }
}




/*---------------------------------------------------------------------------------------
    ============[ the function parameter does not need to be an integer ]============
---------------------------------------------------------------------------------------*/

/*
  - C++ passes what the user types between the hard braces as an argument to the overloaded
    function.
  - in most cases, this will be an integer value.
  - however, this is not required -- and in fact, you can define that your overloaded operator[]
    take a value of any type you desire.

  - overloading operator[] to take a std::string parameter can be useful when writing certain
    kinds of classes, such as tose that use words as indices.
*/




//=======================================================================================

#include <vector>
#include <string_view>
#include <algorithm>

namespace quiz
{
    // [ description ]
    /*
        a map is a class that stores elements as a key-value pair. the key must be unique,
        and is used to access the associated pair.

        in this quiz, we're going to write an application that lets us assign grades to
        students by name, using a simple map class. the student's name will be the key,
        and the grade (as a char) will be the value.

        a) write a struct names [StudentGrade] that contains the student's name (as a
           std::string) and grade (as a char)

        b) add a class named [GradeMap] that contains a [std::vector] of [StudentGrade]
           named [m_map].

        c) Write an overloaded operator[] for this class. This function should take a
           std::string parameter, and return a reference to a char. In the body of the
           function, first see if the student’s name already exists (You can use
           std::find_if from <algorithm>). If the student exists, return a reference to
           the grade and you’re done. Otherwise, use the std::vector::push_back()
           function to add a StudentGrade for this new student. When you do this,
           std::vector will add a copy of your StudentGrade to itself (resizing if
           needed, invalidating all previously returned references). Finally, we need to
           return a reference to the grade for the student we just added to the
           std::vector. We can access the student we just added using the
           std::vector::back() function.
    */

    // a)
    struct StudentGrade
    {
        std::string name{};
        char grade{};
    };

    // b)
    class GradeMap
    {
    private:
        std::vector<StudentGrade> m_map{};

    public:
        // c)
        char& operator[](std::string_view);
    };

    // c)
    char& GradeMap::operator[](std::string_view name)
    {
        // check whether name is exist
        auto index{ std::find_if(m_map.begin(), m_map.end(), [name](StudentGrade& a){ return name == a.name; }) };

        // not found
        if (index == m_map.end())
        {
            StudentGrade studentGrade{ std::string{name} };
            m_map.push_back(studentGrade);

            return m_map.back().grade;
        }
        else    // found
        {
            return index->grade;
        }
    }


    void main()
    {
        GradeMap grades{};

        grades["Joe"] = 'A';
        grades["Frank"] = 'B';

        std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
        std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
    }
}



// [ since maps are common, the standard library offers [std::map]]
//---------------------------------------------------------------------------------------
    // using std::map, we can simplify our code to:
    #include <map>

    void using_map()
    {
        // std::map can be initialized
        std::map<std::string, char> grades{
            { "Joe", 'A' },
            { "Frank", 'B' }
        };

        // and assigned
        grades["Susan"] = 'C';
        grades["Tom"] = 'D';

        std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
        std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
    }
//---------------------------------------------------------------------------------------





//=======================================================================================

int main()
{
    overloading_subscript_operator::main();

    dealing_with_const_objects::main();

    pointer_and_overloaded_subscript_operator_dont_mix::main();


    quiz::main();

    using_map();


    return 0;
}