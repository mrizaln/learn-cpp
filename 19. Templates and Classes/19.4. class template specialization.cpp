#include <iostream>


/*---------------------------------------------------------------------------------------
                               ============[ ]============
---------------------------------------------------------------------------------------*/

namespace example
{
    template <typename T>
    class Storage8
    {
    private:
        T m_array[8];

    public:
        void set(int index, const T& value)
        {
            m_array[index] = value;
        }

        const T& get(int index) const
        {
            return m_array[index];
        }
    };

    // efficient Storage8<bool>
    template<>
    class Storage8<bool>
    {
    private:
        unsigned char m_data{};

    public:
        void set(int index, bool value)
        {
            auto mask{ 1 << index };

            if (value)
                m_data |= mask;
            else
                m_data &= ~mask;
        }

        bool get(int index)
        {
            auto mask{ 1 << index };
            return (m_data & mask);
        }
    };


    void main()
    {
        // Storage8 for int
        Storage8<int> intStorage;

        for (int count{ 0 }; count < 8; ++count)
            intStorage.set(count, count);

        for (int count{ 0 }; count < 8; ++count)
            std::cout << intStorage.get(count) << '\n';

        // Storage8 for bool
        Storage8<bool> boolStorage;

        for (int count{ 0 }; count < 8; ++count)
            boolStorage.set(count, count & 3);
        
        for (int count{ 0 }; count < 8; ++count)
            std::cout << boolStorage.get(count) << '\n';
    }
}




//=======================================================================================

int main()
{
    example::main();

    return 0;
}