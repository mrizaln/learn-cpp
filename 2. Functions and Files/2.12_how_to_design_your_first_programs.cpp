//================[ Design ]================

// Design step 1: Define your goal
    // ideally you should be able to state this in a sentence or two
    // it is often useful to express this as a user-facing outcome:
        // 1. allow the user to organize a list of names and associated phone numbers
        // 2. generate randomize dungeons that will produce interesting looking caverns
        // 3. generate a list of stocl recommendations for stocks that have high demands
        // 4. model how long it takes for a ball dropped off a tower to hit the ground

// Design step 2: Define requirements
    // constraints that your solution need to abide
    // capabilities that the program must exhibit in order to meet the user's needs
    // think about 'what' not 'how'
        // 1. phone numbers should be saved, so they can be recalled later
        // 2. the randomized dungeon should always contain a way to get from the entrance to an exit
        // 3. the stock recommendations should leverage historical pricing data
        // 4. the user should be able to enter the height of the tower
        // 5. we need a testable version within 7 days
        // 6. the program should produce results within 10 seconds of the user submitting their request
        // 7. the program shouold crash in less than 0.1% of user sessions

// Design step 3: Define your tools, targets, and backup plan
    // something like:
        // 1. defining what target architecture and/or OS your program will run on
        // 2. determining what set of tools you will be using
        // 3. determining whether you will write your program alone or as part of a team
        // 4. defining your testing/feedback/release strategy
        // 5. determining how you will back up your code
    
// Design step 4: Break hard problems down into easy problems
    // instead of solving asingle complex task, we break that task into multiple subtask, each of which is individually easier to solve
    // if those subtasks are still too difficult to solve, they can be broken down further

// Design step 5: Figure out the sequence of events
    // for example, we were writing a calculator:
        // 1. get first number from user
        // 2. get mathematical operation from user
        // 3. get second number from user
        // 4. calculate result
        // 5. print result


//================[ Implementation ]================

// Implementation step 1: Outliing your main function
    int pretend_this_is_the_main_function()
    {
        // get first number from user
    //    getUserInput();

        // get mathematical operation from user
    //    getMathematicalOperation();

        // get second number from user
    //    getUserInput();

        // calculate result();
    //    calculateResult();

        // print result
    //    printResult();

        return 0;
    }

// Implementation step 2: Implement each function
    // in this step, for each function, you'll do:
        // 1. define the function prototype (inputs and outputs)
        // 2. write the function
        // 3. test the function

    #include <iostream>

    int getUserInput()
    {
        std::cout << "Enter an integer: ";
        int input {};
        std::cin >> input;
        return input;
    }

    int the_main_function()
    {
        // get first number from user
       int value = getUserInput();
       std::cout << value;      // debug

        // get mathematical operation from user
    //    getMathematicalOperation();

        // get second number from user
    //    getUserInput();

        // calculate result();
    //    calculateResult();

        // print result
    //    printResult();

        return 0;
    }

// Implementation step 3: Final testing
    // once your program is "finished", the last step is to test the whole program
    // and ensure it works as intended
    // if it doesn't work, fix it

// Word of advice when writing programs
    // 1. keep your programs simple to start
    // 2. add features over time
    // 3. focus on one area at a time
    // 4. test each piece of code as you go
    // 5. don't invest in perfecting early code