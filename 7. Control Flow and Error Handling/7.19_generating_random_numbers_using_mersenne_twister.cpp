#include <iostream>
#include <random>       // for random things
#include <chrono>       // for time/clock/tick/etc

//============[ generating random numbers in C++ using Mersenne Twister ]============

// mersenne twister, although it is a bit old by today's standards, it generally produces
// quality results and has decent performance.

// the random library has support for two mersenne twister types:
    // mt19937      generate 32 bit unsigned integers
    // mt19937_64   generate 64 bit unsigned integers

    int main_using_mersenne_twister()
    {
        std::mt19937 mt;    // instantiate a 32-bit mersenne twister

        // print a bunch of random numbers
        for (int count{ 1 }; count <= 40; ++count)
        {
            std::cout << mt() << '\t';    // generate a random number

            if (count % 5 == 0)
                std::cout << '\n';
        }

        return 0;
    }




//============[ rolling a dice using mersenne twister ]============

// PRNG can only generate numbers in their full range.
// if we want to get a lower range (like 1 to 6), we can use random number distribution
// a random number distribution converts the output of a PRNG into some other distribution
// of numbers.

// the random library has many random numbers distributions, most of which you will never
// use unless you're doing some kind of statistical analysis.
// but there's one random number distribution that's extremely useful: a uniform distribution.
// it produces outputs between two numbers X and Y (inclusive) with equal probability


    int main_dice()
    {
        std::mt19937 mt;

        // create a resusable random number generator that generates uniform numbers between 1 and 6
        std::uniform_int_distribution die6{ 1, 6 };

        for (int count{ 1 }; count <= 40; ++count)
        {
            std::cout << die6(mt) << '\t';

            if (count % 10 == 0)
                std::cout << '\n';
        }

        return 0;
    }




//==========[ above function is not as random as it seems ]============

// because we use the same seed (default seed) each time we run the program, it will produce
// the same sequence of number.

// to randomize it, we need to seed the PRNG with an seed number that is not fixed each time
// we run it.
// there are two methods that are commonly used to do this:
    // 1. use the system clock
    // 2. use the system's random device




//============[ seeding with the system clock ]============

// to minimize the chance of two time values being identical if the program is run quickly
// in succession, we want to use some time measurem that changes as quickly as possible.
// for this, we'll ask the clock how much time has passed since the earliest time it can
// measure.
// this time is measured in 'ticks', which is a very small unit of time (usually ns, or ms)

    int main_seeded_by_clock()
    {
        // seed our mersenne twister
        std::mt19937 mt{ static_cast<unsigned int>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        )};

        std::uniform_int_distribution die6{ 1, 6 };

        for (int count{ 1 }; count <= 40; ++count)
        {
            std::cout << die6(mt) << '\t';

            if (count % 10 == 0)
                std::cout << '\n';
        }

        return 0;
    }

// the downside of this approach is that if the program is run several times in quick succession,
// the seeds generated for each run won't be that different, which can impact the quality of
// the random results.

/* tip
    std::chrono::high_resolution_clock   is a popular choice instead of  
    std::chrono::steady_clock .  std::chrono::high_resolution_clock is the clock that uses
    the most granular unit of time, but it may use the system clock for the current time,
    which can be changed or rolled back by users.  std::chrono::steady_clock  may have less
    granular tick time, but is the only clock with a gurantee that users can not adjust it.
*/




//============[ seeding with the random device ]============

// the random library contains a type called   std::random_device   that is an implementation-
// defined PRNG.
// typically   std::random_device   will ask the OS for a random number

    int main_random_device()
    {
        // seed the mt using a number from random device
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution die6{ 1, 6 };

        for (int count{ 1 }; count <= 40; ++count)
        {
            std::cout << die6(mt) << '\t';

            if (count % 10 == 0)
                std::cout << '\n';
        }

        return 0;
    }

// one potential problem with   std::random_device   is it isn't required to be non-deterministic,
// meaning it could, on some systems.

/* best practice
    use   std::random_device   to seed you PRNGs (unless it is not implemented properly for
    your target compiler/architecture)
*/




//============[ only seed a PRNG once ]============

// many PRNGs can be reseeded after the initial seeding.
// this essentially re-initializes the state of the random number generator, causing it to
// generate results starting from the new seed state.
// reseeding should generally avoided unless you have specific reason to do so, as it can
// cause the results to be less random, or not random at all

/* best practice
    only seed a given pseudo-random number generator once, and do not reseed it.
*/

    // here's a common mistake that new programmer make
    int getCard()
    {
        std::mt19937 mt{ std::random_device{}() };     // this gets created and seeded every time the function is called
        std::uniform_int_distribution card{ 1, 52 };
        return card(mt);
    }

    int main_getCard()
    {
        std::cout << getCard();

        return 0;
    }




//============[ random numbers across multiple functions ]============

// one way to do that is to create (and seed) out PRNG in our main() function, and then pass
// it everywhere we need it.
// but that's a lot of passing for something we may only use sporadically, and in different
// places.

// a better option in most cases is to create a global RNG (inside a namespace).
// this is an exception to "avoid non-const global variable"

    namespace Random
    {
        std::mt19937 mt{ std::random_device{}() };
        
        int get(int min, int max)
        {
            std::uniform_int_distribution die{ min, max };      // we can create a distribution in any function that needs it
            return die(mt);                                     // and then generate a random number from our global generator
        }
    }

    int main_multi()
    {
        std::cout << Random::get(1, 6) << '\n';
        std::cout << Random::get(1, 10) << '\n';
        std::cout << Random::get(1, 20) << '\n';

        return 0;
    }




//============[ mersenne twister and underseeding issues ]============

// the internal state of mersenne twister is 624 bytes in size.
// in the examples above, our seed is only a single 32-bit integer (from clock or from
// std::random_device).
// we're underseeded the PRNG.

// to fix this, we can use   std::seed_seq   
// std::seed_seq   can store multiple seed values, it also will generate as many additional
// unbiased seed values an needed to initialize a PRNG's state.

// the more piexes of random data we can give std::seed_seq, the better

    int main_fix_underseeding()
    {
        std::random_device rd;
        std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };    // get 8 int of random numbers from std::random_device
        std::mt19937 mt{ ss };      // intialize our mersenne twister with the std::seed_seq
        std::uniform_int_distribution die6{ 1, 6 };

        for (int count{ 1 }; count <= 40; ++count)
        {
            std::cout << die6(mt) << '\t';

            if (count % 10 == 0)
                std::cout << '\n';
        }

        return 0;
    }

// why not give std::seed_seq 156 int (624 bytes) from std::random_device?
/*
    you can! however, this may be slow, and risks depleting the pool of random numbers that
    std::random_device uses.
*/


//=======================================================================================

int main()
{
    // main_using_mersenne_twister();
    // main_dice();
    // main_seeded_by_clock();
    // main_random_device();
    // main_multi();
    main_fix_underseeding();

    return 0;
}