/*---------------------------------------------------------------------------------------
              ============[ why make member variables private? ]============
---------------------------------------------------------------------------------------*/

// to hide the inner works of a class (implementation), and only show the interfaces to the
// user.




/*---------------------------------------------------------------------------------------
                        ============[ encapsulation ]============
---------------------------------------------------------------------------------------*/

/*
  - in OOP, [encapsulation] (also called information hiding) is the process of keeping the
    detauls about how an object is implemented hidden away from users of the object.
  - instead, users of the object access the object through a public interface.

  - in C++, we implement encapsulation via access specifiers.
  - typically, all member variables of the class are made private and most member functions
    are made public.

  - benefits:
    1. encapsulated classes are easier to use and reduce the complexity of your program.
    2. encapsulated classes help protect your data and prevent misuse.
    3. encapsulated classes are easier to change.
    4. encapsulated classes are easier to debug.
*/




/*---------------------------------------------------------------------------------------
                      ============[ access functions ]============
---------------------------------------------------------------------------------------*/

/*
  - an [access function] is a short public function whose job is to retrieve or change the
    value of a private member variable.
  - access functions typically come in two flavors: getters and setters.
  - [getters] (accessors) are functions that return the value of a private member variable.
  - getters should provide "read-only" access to data (return by value or const reference).
  - [setters] (mutators) are functions that set the value of a private member variable.
*/




/*---------------------------------------------------------------------------------------
                  ============[ access functions concerns ]============
---------------------------------------------------------------------------------------*/

/*
  - there's a fair bit of discussion around in which cases access functinos should be used
    or avoided.

  - as you create your classes, consider the following:
      1. if nobody outside your class needs to access a member, don'r provide access functions
         for that member.
      2. if someone outside your class needs to access a member, think about whether you can
         expose a behavior or action insted (e.g. rather than a setAlive(bool) setter, implement
         a kill() function instead).
      3. if you can't, consider whether you can provide only a getter.
*/