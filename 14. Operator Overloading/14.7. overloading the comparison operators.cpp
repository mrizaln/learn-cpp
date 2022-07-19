#include <iostream>
#include <string>
#include <string_view>


/*
  - there are 6 comparsion operators.
  - because the comparison operatos are all binary operators that do not modify their left
    operands, we will make our overloaded comparison operators friend functions.
*/


class Car
{
private:
    std::string m_make{};
    std::string m_model{};

public:
    Car(std::string_view make, std::string_view model)
        : m_make{ make }, m_model{ model }
    {
    }

    friend bool operator==(const Car& c1, const Car& c2);
    friend bool operator!=(const Car& c1, const Car& c2);
};

bool operator==(const Car& c1, const Car& c2)
{
    return (c1.m_make == c2.m_make && c1.m_model == c2.m_model);
}

bool operator!=(const Car& c1, const Car& c2)
{
    return (c1.m_make != c2.m_make || c1.m_model != c2.m_model);
}


int main()
{
    Car corolla{ "Toyota", "Corolla" };
    Car camry{ "Toyota", "Camry" };

    if (corolla == camry)
        std::cout << "a Corolla and Camry are the same.\n";

    if (corolla != camry)
        std::cout << "a Corolla and Camry are not the same.\n";

    return 0;
}

/*
  - we defined operator== and operator!= above, what about operator> and operator<?
  - what would it mean for a Car to be grater or less than another Car?
  - since the results of operator< and operator> would not be immediately intuitive, it may
    be better to leave these operators undefined.

  - however, there is one common exception to the above recommendation.
  - what if we wanted to sort a list of Cars? in such a case, we might want to overload the
    comparison operator to return the member (or members) you're most likely to want to sort on.
  - for example, an overloaded operator< for Cars might sort based on make and model alphabetically.
*/




/*---------------------------------------------------------------------------------------
              ============[ minimizing comparative redundancy ]============
---------------------------------------------------------------------------------------*/

/*
  - overloaded comparison operators tend to have a high degree of redundancy, and the more
    complex the implementation, the more redundacy there will be.

  - fortunately, many of the copmarison operators can be implemented using the other comparison
    operators:
      > operator!= can be implemented as !(operator==)
      > operator>  can be implemented as operator< with the order of the parameters flipped
      > operator>= can be implemented as !(operator<)
      > operator<= can be implemented as !(operator>)
*/