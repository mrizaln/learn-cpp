#include <iostream>

/*---------------------------------------------------------------------------------------
               ============[ the protected access specifier ]============
---------------------------------------------------------------------------------------*/

/*
  - C++ has a third access specifier (besides public and private), that only useful in an
    inheritance context.
  - the [protected] access specifier allows the class members belongs to, friend, and derived
    classes to access the member.
  - however, protected members are not accessible from outside.
*/

class Base
{
public:
    int m_public{};         // can be accessed by anybody
    
protected:
    int m_protected{};      // can be accessed by Base members, friends, and derived classes

private:
    int m_private{};        // can only be accessed by Base members, and friends, (but not derived classes)
};


namespace access_specifiers
{
    class Derived : public Base
    {
    public:
        Derived()
        {
            m_public = 1;       // allowed
            m_protected = 2;    // allowed
            // m_private = 3;      // not allowed
        }
    };


    void main()
    {
        Base base;
        base.m_public = 1;      // allowed
        // base.m_protected = 2;   // not allowed
        // base.m_private = 3;     // not allowed
    }
}




/*---------------------------------------------------------------------------------------
    ============[ so when should I use the protected access specifier? ]============
---------------------------------------------------------------------------------------*/

/*
  - with a protected attribute in a base class, derived classes can access that member directly.
  - this means that if you later change anything about that protected attribute you'll probably
    need to change both the base class AND all of the derived class.

  - therefore, using the protected access specifier is most useful when you (or your team)
    are going to be the ones deriving from your own classes, and the number of derived classes
    is reasonable.

  - in general, it's better to make your members private if you can, and only use protected
    when derived classes are planned and the cost to build and maintain an interface to those
    private members is too high.
*/


// [ best practice ]
/*---------------------------------------------------------------------------------------
    favor private members over protected members
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
  ============[ different kinds of inheritance, and their impact on access ]============
---------------------------------------------------------------------------------------*/

// there are three different ways for classes to inherit from other classes: public, protected,
// and private.

class Pub: public Base{};           // inherit from Base publicly
class Pro: protected Base{};        // inherit from Base protectedly
class Pri: private Base{};          // inherit from Base privately

/*
  - if you do not choose an inheritance type, C++ defaults to private inheritance.

  - in a nutshell, when members are inherited, the access specifier for an inherited member
    may be changedged (in the derived class only) depending on the type of inheritance used.
  - members that were public or protected in tha base class may change access specifiers
    in the derived class.
*/




/*---------------------------------------------------------------------------------------
                     ============[ public inheritance ]============
---------------------------------------------------------------------------------------*/

/*
  - public inheritance is the most common method of inheritance.
  - when we inherit a base class publicly, inherited public members stay public, and inherited
    protected members stay protected, and inherited private memebers stay inaccessible.

    base            derived
    -------------------------
    public      ->  public
    protected   ->  protected
    private     ->  private
*/

namespace public_inheritance
{
    class Pub: public Base
    {
    public:
        Pub()
        {
            m_public = 1;           // okay
            m_protected = 2;        // okay
            // m_private = 3;          // not okay
        }
    };

    void main()
    {
        Base base;
        base.m_public = 1;          // okay
        // base.m_protected = 2;       // not okay
        // base.m_private = 3;         // not okay

        Pub pub;
        pub.m_public = 1;          // okay
        // pub.m_protected = 2;       // not okay
        // pub.m_private = 3;         // not okay
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    use public inheritance unless you have a specific reason to do otherwise.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                    ============[ protected inheritance ]============
---------------------------------------------------------------------------------------*/

/*
  - protected inheritance is the least common method of inheritance

    base            derived
    -------------------------
    public      ->  protected
    protected   ->  protected
    private     ->  private
*/




/*---------------------------------------------------------------------------------------
                    ============[ private inheritance ]============
---------------------------------------------------------------------------------------*/

/*
  - with private inheritance, all members from the bae class are inherited as private.

    base            derived
    -----------------------
    public      ->  private
    protected   ->  private
    private     ->  private
*/

namespace private_inheritance
{
    class Pub: private Base
    {
    public:
        Pub()
        {
            m_public = 1;           // okay
            m_protected = 2;        // okay
            // m_private = 3;          // not okay
        }
    };

    void main()
    {
        Base base;
        base.m_public = 1;          // okay
        // base.m_protected = 2;       // not okay
        // base.m_private = 3;         // not okay

        Pub pub;
        // pub.m_public = 1;          // okay
        // pub.m_protected = 2;       // not okay
        // pub.m_private = 3;         // not okay
    }
}