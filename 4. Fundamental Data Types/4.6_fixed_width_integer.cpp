//============[ Fixed-length integers ]============

/*
std:int8_t      1 B signed
std:uint8_t     1 B unsigned
std:int16_t     2 B signed
std:uint16_t    2 B unsigned  
std:int32_t     4 B signed
std:uint32_t    4 B unsigned  
std:int64_t     8 B signed
std:uint64_t    8 B unsigned
*/

#include <cstdint> // for fixed-width integers
#include <iostream>

int main_0()
{
    std::int16_t i{5};
    std::cout << i;
    return 0;
}

//  The fixed-width integers are not guaranteed to be defined on all architectures.
// They only exist on systems where there are fundamental types matching their widths and
// following a certain binary representation

//  If you use a fixed-width integer, it may be slower than a wider type on some
// architectures. For example, if you need an integer that is guaranteed to be 32-bits,
// you might decide to use std::int32_t


//============p[ Fast and least integers ]============
//      std::int_fast#_t        # 8, 16, 32, 64
//      std::int_least#_t

#include <cstdint> // for fixed-width integers
#include <iostream>

int main_1()
{
	std::cout << "least 8:  " << sizeof(std::int_least8_t) * 8 << " bits\n";
	std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
	std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
	std::cout << '\n';
	std::cout << "fast 8:  " << sizeof(std::int_fast8_t) * 8 << " bits\n";
	std::cout << "fast 16: " << sizeof(std::int_fast16_t) * 8 << " bits\n";
	std::cout << "fast 32: " << sizeof(std::int_fast32_t) * 8 << " bits\n";

	return 0;
}


//============[ std::int8_t and uint8_t behave like chars instead of integers ]============

//  Due to an oversight in the C++ specification, most compilers define and treat std::int8_t and std::uint8_t
// (and the corresponding fast and least fixed-width types) identically to types signed char and unsigned
// char respectively. This means these 8-bit types may (or may not) behave differently than the rest of the
// fixed-width types, which can lead to errors. This behavior is system-dependent, so a program that behaves
// correctly on one architecture may not compile or behave correctly on another architecture.

//  For consistency, it’s best to avoid std::int8_t and std::uint8_t (and the related fast and least types)
// altogether (use std::int16_t or std::uint16_t instead).


/*
Best practice

    Prefer int when the size of the integer doesn’t matter (e.g. the number will always fit within the range of a 2-byte signed integer). For example, if you’re asking the user to enter their age, or counting from 1 to 10, it doesn’t matter whether int is 16 or 32 bits (the numbers will fit either way). This will cover the vast majority of the cases you’re likely to run across.
    Prefer std::int#_t when storing a quantity that needs a guaranteed range.
    Prefer std::uint#_t when doing bit manipulation or where well-defined wrap-around behavior is required.

Avoid the following when possible:

    Unsigned types for holding quantities
    The 8-bit fixed-width integer types
    The fast and least fixed-width types
    Any compiler-specific fixed-width integers -- for example, Visual Studio defines __int8, __int16, etc…
*/


// What is std::size_t?
int main()
{
    std::cout << sizeof(int) << '\n';
    std::cout << sizeof(std::size_t) << '\n';

    return 0;
}