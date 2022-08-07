#include <iostream>
#include <string>
#include <string_view>


/*---------------------------------------------------------------------------------------
                        ============[ aggregation ]============
---------------------------------------------------------------------------------------*/

/*
  - to qualify as an [aggregation] a whole object and its parts must have the following
    relationships:
    1. the part (member) is part of the object (class)
    2. the part (member) can belong to more than one object (class) at a time
    3. the part (member) does not have its existence managed by the object (class)
    4. the part (member) does not know about the existence of the object (class)

  - like a composition, an aggregation is still a par-whole relationship, where the parts
    are contained within the while, and it is a unidirectional relationship.
  - howeveer, unlike a composition, parts can belong to more than one object at a time, and
    the whole object is not responsible for the existence and lifespan of the parts.

  - aggregation models ["has-a"] relationships.
  - example: a department has teachers.

  - the parts of an aggregation can be singular or multiplicative.

  - because aggregations are similar to compositions in that they are both part-whole
    relationships, they are implemented almost identically, and the difference between them
    is mostly semantic.
*/




/*---------------------------------------------------------------------------------------
                          ============[ example ]============
---------------------------------------------------------------------------------------*/

/*
  - in a composition, we typically add our parts to the composition using normal member
    variables.
  - in aggregation, we also add parts as member variables, however, these member variables
    are typically either references or pointers that are used to point at objects that has
    been created outside the scope of the class.
  - consequently, an aggregation usually either takes the objects it is going to point to as
    constructor parameters, or it begins empty and the subobjects are added later via access
    functions or operators.

  - because these parts exist outside of the scope of the class, when the class is destroyed,
    the pointer or reference member variable will be destoryed (but not delted).
  - consequently, the parts themselves will still exist.
*/

namespace example
{
    class Teacher
    {
    private:
        std::string m_name{};

    public:
        Teacher(const std::string_view name)
            : m_name{ name }
        {
        }

        const std::string& getName() const { return m_name; }
    };

    class Department
    {
    private:
        const Teacher& m_teacher;       // this dept holds only one teacher for simplicity, but it could hold many teachers

    public:
        Department(const Teacher& teacher)
            : m_teacher{ teacher }
        {
        }
    };

    void main()
    {
        Teacher bob{ "Bob" };

        {
            Department department{ bob };
        } // department gets destoryed

        // bob still exist here
        std::cout << bob.getName() << " still exists!\n";
    }
}




/*---------------------------------------------------------------------------------------
                   ============[ std::reference_wrapper ]============
---------------------------------------------------------------------------------------*/

/*
  - in the Department/Teacher example above, we used a reference in the Department to store
    the Teacher.
  - this works fine if there is only one Teacher, but what if Department has multiple Teachers?
  - we'd like to store those Teachers in a list of some kind, but fixed arrays and the various
    standard library lists can't hold references.

        std::vector<const Teacher&> m_teachers{};       // illegal

  - instead of references, we could use pointers, but that would open the possibility to
    store or pass null pointers.

  - to solve this, there's [std::reference_wrapper]
  - it is a class that acts like a reference, but also allows assignment and copying, so it
    is compatible with lists like std::vector.

  - all you need to know to use [std::reference_wrapper] are three things:
    1. [std::reference_wrapper] lives in the <functional> header.
    2. when you create your [std::reference_wrapper] wrapped object, the object can't be an
       anonymous object.
    3. when you want to get your object back out of [std::reference_wrapper], you use the
       [get()] member function.
*/

#include <vector>
#include <functional>       // for std::reference_wrapper

namespace reference_wrapper
{
    void main()
    {
        std::string tom{ "Tom" };
        std::string berta{ "Berta" };

        std::vector<std::reference_wrapper<std::string>> names{ tom, berta };   // these strings are stored by reference, not value

        // to create a vector of const references, we'd have to add const before the std::string
        std::vector<std::reference_wrapper<const std::string>> const_names{ tom, berta };

        std::string jim{ "Jim" };

        names.push_back(jim);

        for (auto name: names)
            name.get() += " Beam";

        std::cout << jim << '\n';       // Jim Beam;
    }
}




//=======================================================================================

namespace quiz
{
    // [ description ]
    /*
        update the [Department/Teacher] example so the [Department] can handle multiple
        Teachers.
    */

    using example::Teacher;

    class Department
    {
    private:
        std::vector<std::reference_wrapper<const Teacher>> m_teachers{};

    public:
        Department() = default;

        void add(const Teacher& teacher)
        {
            m_teachers.push_back(teacher);
        }

        friend std::ostream& operator<<(std::ostream& out, const Department& dept);
    };

    std::ostream& operator<<(std::ostream& out, const Department& dept)
    {
        out << "Department: ";
        for (const auto& teacher: dept.m_teachers)
            out << teacher.get().getName() << ' ';
        return out;
    }

    void main()
    {
        Teacher t1{ "Bob" };
        Teacher t2{ "Frank" };
        Teacher t3{ "Beth" };

        {
            // Create a department and add some Teachers to it
            Department department{}; // create an empty Department

            department.add(t1);
            department.add(t2);
            department.add(t3);

            std::cout << department << '\n';

        } // department goes out of scope here and is destroyed

        std::cout << t1.getName() << " still exists!\n";
        std::cout << t2.getName() << " still exists!\n";
        std::cout << t3.getName() << " still exists!\n";
    }
}


//=======================================================================================

int main()
{
    example::main();
    reference_wrapper::main();
    quiz::main();

    return 0;
}