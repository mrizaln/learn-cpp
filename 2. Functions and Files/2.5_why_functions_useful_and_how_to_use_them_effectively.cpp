/*
Why use functions?
    1. Organization -- 
       As programs grow in complexity, having all the code live inside the
       main() function becomes increasingly complicated. A function is almost like a mini-
       program that we can write separately from the main program, without having to think
       about the rest of the program while we write it. This allows us to reduce a complicated
       program into smaller, more manageable chunks, which reduces the overall complexity
       of our program.

    2. Reusability -- 
       Once a function is written, it can be called multiple times from within
       the program. This avoids duplicated code (“Don’t Repeat Yourself”) and minimizes the
       probability of copy/paste errors. Functions can also be shared with other programs,
       reducing the amount of code that has to be written from scratch (and retested) each time.

    3. Testing -- 
       Because functions reduce code redundancy, there’s less code to test in the first place.
       Also because functions are self-contained, once we’ve tested a function to ensure it
       works, we don’t need to test it again unless we change it. This reduces the amount of
       code we have to test at one time, making it much easier to find bugs (or avoid them in
       the first place).

    4. Extensibility -- 
       When we need to extend our program to handle a case it didn’t handle before, functions
       allow us to make the change in one place and have that change take effect every time
       the function is called.

    5. Abstraction -- 
       In order to use a function, you only need to know its name, inputs, outputs, and where
       it lives. You don’t need to know how it works, or what other code it’s dependent upon
       to use it. This lowers the amount of knowledge required to use other people’s code
       (including everything in the standard library).
*/

/*
Effectively using functions
    1. Groups of statements that appear more than once in a program should generally be made
       into a function. For example, if we’re reading input from the user multiple times in
       the same way, that’s a great candidate for a function. If we output something in the
       same way in multiple places, that’s also a great candidate for a function.

    2. Code that has a well-defined set of inputs and outputs is a good candidate for a function,
       (particularly if it is complicated). For example, if we have a list of items that we
       want to sort, the code to do the sorting would make a great function, even if it’s only
       done once. The input is the unsorted list, and the output is the sorted list. Another
       good prospective function would be code that simulates the roll of a 6-sided dice. Your
       current program might only use that in one place, but if you turn it into a function, it’s
       ready to be reused if you later extend your program or in a future program.

    3. A function should generally perform one (and only one) task.

    4. When a function becomes too long, too complicated, or hard to understand, it can be split
       into multiple sub-functions. This is called refactoring. We talk more about refactoring
       in lesson 3.10 -- Finding issues before they become problems.
*/