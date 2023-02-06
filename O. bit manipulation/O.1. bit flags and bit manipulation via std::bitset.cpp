/*------------------------------------------------------------------------------
                      ============[ bit flags ]============
------------------------------------------------------------------------------*/

// when individual bits of an object are used as boolean values, the bits are called
// bit flags.
// to define a set of bit flags, we'll typically use an unsigned integer of the
// aprropriate size (8 bits, 16 bits, 32 bits, etc.), ot std::bitset

#include <bitset>

std::bitset<8> mybitset{};





/*------------------------------------------------------------------------------
         ============[ manipulating bits via std::bitset ]============
------------------------------------------------------------------------------*/

// 76543210     bit position
// 10110101     bit sequence

/*
  - std::bitset provides 4 key functions that are useful for doing bit manipulation:
    1. test()       query whether a bit is 0 or 1
    2. set()        turn a bit on
    3. reset()      turn a bit off
    4. flip()       flip a bit value
*/

#include <iostream>
#include <bitset>

namespace bit_manipulation
{
    void main()
    {
        std::bitset<8> bits{ 0b0000'0101 };
        bits.set(3);        // set bit position 3 to 1
        bits.flip(4);       // flip bit 4
        bits.reset(4);      // set bit 4 to 0

        std::cout << "All the bits: " << bits << '\n';
        std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
        std::cout << "Bit 4 has value: " << bits.test(4) << '\n';
    }
}




/*------------------------------------------------------------------------------
              ============[ the size of std::bitset ]============
------------------------------------------------------------------------------*/

/*
  - std::bitset if optimized for speed, not memory savings.
  - the size of a std::bitset is typically the number of bytes needed to hold the
    bits, rounded up to the nearest [sizeof(size_t), which is 4 bytes on 32-bit
    machines, and 8 bytes on 64-bit machines.

  - std::bitset is most useful when we desire convenience, not memory savings.
*/




//==============================================================================

int main()
{
    bit_manipulation::main();

    return 0;
}
