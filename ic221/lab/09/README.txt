----------------------------------------------------------------------------
Name:  Mike Hanling
Alpha: 202430


Collaborator(s): Ben Birney

Resources Used: Ben Birney's mind, and the man pages

Hours: 06
----------------------------------------------------------------------------
  Replace the X's above with your name and alpha, and also list any collaborator
  or other resources you used. Please also indicate the number of hours
  (including hours in the lab period) you spent on this assignment.

  After completing the assignment, please answer these questions to provide
  feedback.

  * What did you learn from this assignment?
That I was really confusing some key concepts when implementing multiple
forks under the same parent program.  I believe that Ben cleared it up
though.

  * What part of the assignment was easier then you expected?
The first half was not too bad.

  * What part of the assignment was harder then you expected?
The second part seriously confused me, but I finally got it after some
structure rework.  I had all the right segments of code, just not put in
an order that would logically work.

  * What would you suggest for improving this assignment?
I think some more clarification of part 2 would have been nice.  It was
probably just me coming back from break and not thinking right, but just
saying that all the coding should be in the parent was kinda wrong and
misleading.

  * Any additional information you'd like to share regarding this assignment?
It kicked my butt.

----------------------------------------------------------------------------

  Below, fill out this worksheet with the appropriate answers/comments
  to the following questions/prompts. If there are no direct
  questions, please provide some basic comments about each part of the
  assignment.

-------------------------------------------------------------------------

Task 1: shredder
An alarm for one second was set, and then the child was waited on.  The
handler counted the ticks and reset a 1 second alarm.  Once the child
returned, the number of ticks was analyzed to see which witty comment to
print to the screen.


Task 2: collisions
A for loop was used to set up the pipes and then do the child and parent
(giving the hash and first char) work for each fork.  Outside of the for
loop, monitoring of the children to send work or kill was implemented.
The sigaction was registered before the for loop, and its sole job was
to print the four chars to the screen when a child said it did its work.
