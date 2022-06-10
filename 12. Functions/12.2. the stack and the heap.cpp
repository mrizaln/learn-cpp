/*---------------------------------------------------------------------------------------
                            ============[  ]============
---------------------------------------------------------------------------------------*/

/*
    the memory that a program uses is typically divided into a few different areas, called
    segments:
      > the code segment (also called a text segment), where the compiler program sits
        in memory. the code segment is typically read-only.

      > the bss segment (also called the uninitialized data segment), where zero-initialized
        global and static variables are stored.

      > the data segment (also called the initialized data segment), where initialized global
        and static  variables are stored.

      > the heap, where dynamically allocated variables are allocated from.

      > the call stack ,where function paramters, local variables, and other function-related
        information are stored.
*/




/*---------------------------------------------------------------------------------------
                    ============[ the heap segment ]============
---------------------------------------------------------------------------------------*/

/*
  - the heap segment keeps track of memory used for dynamic memory allocation
  - in C++ when you use the new operator to allocate memory, this memory is allocated in
    the application's heap segment.
  - the address of this memory is passed back by operator new, and can be then passed in
    a pointer.

  - it is worth knowing that sequential memory request may not result in sequential memory
    addresses being allocated.

  - when a dynamically allocated variable is deleted, the memory is "returned" to the heap
    and can the be reassigned as future allocation requests are received.

  - the heap has advantages and disadvantage:
      > allocating memory on the heap is comparatively slow.
      > allocated memory stays allocated until it is specifically deallocated or the application
        ends
      > dynamically allocated memory mys be accessed through a pointer. dereferencing a pointer
        is slower tha accessing a variable directly.
      > because the heap is a big pool of memory, large arrays, structures, or classes can
        be allocated here.
*/




/*---------------------------------------------------------------------------------------
                      ============[ the call stack ]============
---------------------------------------------------------------------------------------*/

/*
  - the call stack keeps track of all the active functions from the start of the program
    to the current point of execution, and handles allocation of all function parematers
    and local variables.
  - the call stack is implemented as a stack data structure.

  - the stack has advantages and disadvateges:
      > allocating memory on the stack is comparatively fast.
      > memory allocated on the stack stays in scope as long as it is on the stack. it is
        destroyed wen it is popped off the stack.
      > all memory allocated on the stack is known at compile time. consequently, this memory
        can be accessed directly through a variable.
      > because the stack is relatively small, it is generally not a good idea to do anything
        that eats up lots of stack space. this includes passing by value or creating local
        variables of large arrays or other memory-intensive structures.
*/




/*---------------------------------------------------------------------------------------
                   ============[ the call stack segment ]============
---------------------------------------------------------------------------------------*/

/*
  - the call stack segment hold the memroy used for the call stack. when the application
    starts, the main() function is pushed on the call stack by the operating system.

  - when a function call is encountered, the function is pushed onto the call stack. when
    the current function ends, that function is popped off the call stack.
  - thus, by looking at the functions pused on the call stack, we can see all of the functions
    that were called to get to the current point of execution.

  - the thing that getting pushed into the stack is called stack frame.
  - a stack frame keeps trak of all the data associated with one functoin call.
*/




/*---------------------------------------------------------------------------------------
                  ============[ the call stack in action ]============
---------------------------------------------------------------------------------------*/

/*
  - here's the sequence of steps that takes place when a function is called:
    1. the program encounters a function call.
    2. a stack frame is constructed and pushed on the stack.
       the stack frame consists of:
        + the address of the instruction beyond the function call (return address). this
          is how the cpi remembers where to return to after the called function exits.
        + all function arguments.
        + memory for any local variables.
        + saved copies of any registers modified by the function that need to be restored
          when the function returns.
    3. the cpu jumps to the functions's start point.
    4. the instructions inside of the function begin executing.

  - when the function terminates, the following steps happen:
    1. tegisters are restored from the call stack.
    2. the stack frame is popped off the stack. this frees the memory for all local variables
       and arguments.
    3. the return value is handled.
    4. the cpu resumes execution at the return address.
*/




/*---------------------------------------------------------------------------------------
                      ============[ stack overflow ]============
---------------------------------------------------------------------------------------*/

/*
  - the stack has a limited size, and consequently can only hold a limited amount of information
  - on windows, the default stack is 1MB, on some unix machines, it can be as large as 8MB.
  - if the program tries to put too much information on the stack, stack overflow will result.
  - [stack overflow] happens when all the memory in the stack has been allocated -- in that
    case, further allocations begin overflowing into other sections of memory.

  - stack overflow is generally the result of allocating too many variables on the stack,
    and/or making too many nested function calls.
  - on modern operating systems, overflowing the stack will generally cause your OS to issue
    an access violation and terminate the program.
*/

#include <iostream>
namespace stack_overflow_example
{
    // allocate a huge array on the stack (likely 40MB)
    void example_1()
    {
        int stack[10000000];
        std::cout << "hi" << stack[0];
    }
    // segmentation fault (gcc)

    // infinite recursion
    void example_2()
    {
        example_2();
        std::cout << "hi";
    }
    // segmentation fault
}




//=======================================================================================

int main()
{
    // stack_overflow_example::example_1();
    stack_overflow_example::example_2();

    return 0;
}