----------------------------------------------------------------------------
Name:  Mike Hanling
Alpha: 202430

Collaborator(s):

Resources Used: Documentation and course website

Hours: 03
----------------------------------------------------------------------------
  Replace the X's above with your name and alpha, and also list any collaborator
  or other resources you used. Please also indicate the number of hours
  (including hours in the lab period) you spent on this assignment.

  After completing the assignment, please answer these questions to provide
  feedback.

  * What did you learn from this assignment?
The usefulness of valgrind, and the simplicity under filesystems.

  * What part of the assignment was easier then you expected?
Creating a filesystem.  Not fully functional, but pretty good.

  * What part of the assignment was harder then you expected?
Making the extra credit work correctly.  Definitely seemed easier in my
head.

  * What would you suggest for improving this assignment?
Nothing, I think it went well.

  * Any additional information you'd like to share regarding this assignment?
Get Vimio going on Chrome if you have not.

----------------------------------------------------------------------------

  Below, fill out this worksheet with the appropriate answers/comments to the
  following questions/prompts.

-------------------------------------------------------------------------

Part 1: Task 1: Memory Leaks (15 points)

    
    1. Run valgrind on the memleak program, how many bytes does it
       say have been definitely lost?
       60 Bytes

    2. What line does valgrind indicate the memory leak has occurred?
        Lines 19 and 34 (the calloc calls in doubleup and main
        respectively)

    3. Describe the memory leak below.
        20 bytes were lost when calloc was called in main to alloc the
        array.  40 bytes were lost in doubleup as twice the bytes were
        allocated in order to make the new array.

    4. Try and fix the memory leak and verify your fix with
       valgrind. Describe how you fixed the memory leak below. 
        Add "free(a);" before the return in doubleup &
        add "free(a);" before the return in main.


Part 1: Task 2: Memory Violations (15 points)

  1. Describe the output and execution of the program. Does it seem to be consistent?
      Yes, it seems to be consistent in printing "Hello World!".

  2. Run the program under valgrind, identify the line of code that is
     causing the memory violation and its input. What line of code?
      Line 11 - strlen() call

  3. Debug the memory violation and describe the programming bug below. 
      The malloc call only makes enough room for the visible chars of
      hello, not the terminating null byte. In addition, strlen() only
      returns the number of visible chars, so the for loop does not even
      try to copy enough.

  4. Fix the memory violation and verify your fix with valgrind. What was the fix?
      One more byte needs to be added to the malloc call and the
      condition on the for loop in order to copy the null byte to
      terminate the string properly.


Part 2: simplefs (70 points)

    (Provide a general description and any comments about your code below)
  I think errors thrown on something do not take into account normall
  running of gcc on all systems.
  simplefs works as specified in the lab.

Part 2: Extra Credit (+5 points)
  Completed
