----------------------------------------------------------------------------
Name:  Mike Hanling
Alpha: 202430

Collaborator(s):

Resources Used: Course Website

Hours: 02
----------------------------------------------------------------------------
  Replace the X's above with your name and alpha, and also list any collaborator
  or other resources you used. Please also indicate the number of hours
  (including hours in the lab period) you spent on this assignment.

  After completing the assignment, please answer these questions to provide
  feedback.

  * What did you learn from this assignment?
    Mostly review from SI204

  * What part of the assignment was easier then you expected?
    Randomizing

  * What part of the assignment was harder then you expected?
    Just the setup

  * What would you suggest for improving this assignment?
    Have a function to swap individual elements

  * Any additional information you'd like to share regarding this assignment?


----------------------------------------------------------------------------

  Below, fill out this worksheet with the appropriate answers/comments to the
  following questions/prompts.

-------------------------------------------------------------------------

Answer the following questions:

(1) Why do you have to pass the length of the array to the functions?
    To be able to loop over the whole array

(2) What is a random seed used for?
    To define a consistent starting point for the "random generator"
    For debugging and testing purposes

For each of the parts, describe your actions and code and generally
provide any additional information needed to grade your assignment:

Part 1: Check the input for number of numbers by ensuring it can be read
in.  Read in each, if able to, and build the array.  Errors result in
exiting the program. I used a switch statement to control what to do on
user option input.


Part 2: Since the length was passed into the function, a for loop is
used to walk down the array and print each element.


Part 3: Since the length was passed into the function, a for loop is
used to walk down half the array and swap the element there with its
mirror.  The reversed array is then printed.


Part 4: The array is walked down one element at a time.  A random index
to swap with it calculated and used.  The randomized array is then
printed.


Part 5: I used a "before" and sort function I have saved from SI204 to
sort the array from least to greatest. The sorted array is then
printed.

