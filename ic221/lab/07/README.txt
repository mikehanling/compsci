----------------------------------------------------------------------------
Name:  Mike Hanling
Alpha: 202430

Collaborator(s):

Resources Used:

Hours: 01
----------------------------------------------------------------------------
  Replace the X's above with your name and alpha, and also list any collaborator
  or other resources you used. Please also indicate the number of hours
  (including hours in the lab period) you spent on this assignment.

  After completing the assignment, please answer these questions to provide
  feedback.

  * What did you learn from this assignment?
TIL how shells fundamentally operate.

  * What part of the assignment was easier then you expected?
The timer was actually quite easy to do.

  * What part of the assignment was harder then you expected?
Remembering to NULL terminate the argv array.

  * What would you suggest for improving this assignment?
The lab did not take long, but I know that the next project dives into
this more, I think that this lab served its purpose well.

  * Any additional information you'd like to share regarding this assignment?
No.

----------------------------------------------------------------------------

  Below, fill out this worksheet with the appropriate answers/comments
  to the following questions/prompts. If there are no direct
  questions, please provide some basic comments about each part of the
  assignment.

-------------------------------------------------------------------------


Part 1: timer
Grabbing the times before and after the wait call tells how long it
takes the child to perform its task.

Part 2: mini-sh
Using the code from timer to do the timer piece, a while loop
continually asking for commands works.  Tokenize each word, adding to
the cmd_argv.  NULL terminate, and then fork-exec-wait to execute the
specified task.
