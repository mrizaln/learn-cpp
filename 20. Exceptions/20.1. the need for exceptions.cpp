#include <iostream>
#include <string>
#include <string_view>


/*---------------------------------------------------------------------------------------
                   ============[ when return codes fail ]============
---------------------------------------------------------------------------------------*/

/*
  - when writing reusable code, error handling is a necessity.
  - one of the most common ways to handle potential errors is via return codes.
*/

namespace return_code
{
    int findFirstChar(std::string_view string, char ch)
    {
        for (std::size_t index{ 0 }; index < string.length(); ++index)
            if (string[index] == ch)
                return index;
        
        // if no match was found, return -1
        return -1;
    }
}

/*
  - the primary issue with return codes is that the error handling code ends up intricately
    linked to the normal control flow of the code.
  - this in turn ends up constraining both how the code is laid out, and how errors can be
    reasonably handled.
*/




/*---------------------------------------------------------------------------------------
                        ============[ exceptions ]============
---------------------------------------------------------------------------------------*/

/*
  - exception handling provides a mechanism to decouple handling of errors or other exceptional
    circumstances from the typical control flow of your code.
  - this allows more freedom to handle errors when and how ever is most useful for a given
    situation, alleviating most (if not all) of the messiness that return codes causes.
*/