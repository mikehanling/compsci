----------------------------------------------------------------------------
Name:  Mike Hanling
Alpha: 202430

Collaborator(s): Talked casually about it with Ben Birney and Chris
                    Daves

Resources Used: Course website, heavily

Hours: 05
----------------------------------------------------------------------------
  Replace the X's above with your name and alpha, and also list any collaborator
  or other resources you used. Please also indicate the number of hours
  (including hours in the lab period) you spent on this assignment.

  After completing the assignment, please answer these questions to provide
  feedback.

  * What did you learn from this assignment?
I learned that timing for when to execute different things is not
natural.

  * What part of the assignment was easier then you expected?
The majority of babypipe was easily than I expected (the edge cases a
big tougher).

  * What part of the assignment was harder then you expected?
Sleep unroll took me a very long time to understand and implement.

  * What would you suggest for improving this assignment?
I think that just having the lab time with you would have made it go a
bit smoother, but that was clearly not intended.

  * Any additional information you'd like to share regarding this assignment?
This lab was definitely tough for me.  It me the most amount of time to
do, and I was genuinely at a loss a couple of times.  I do think it made
me understand it better in the end.

----------------------------------------------------------------------------

  Below, fill out this worksheet with the appropriate answers/comments
  to the following questions/prompts. If there are no direct
  questions, please provide some basic comments about each part of the
  assignment.

-------------------------------------------------------------------------

Task 1: unroll
I checked if it was the first child off of cpgid being 0 or not.  It was
then swapped with the first child's pid, and the rest of the child got
to tag along to its older brother.  I tokenized each command and then
fed it into an execvp.  The parent simply check for first child or not
and then set that child's group id appropriately.  The provided waitpid
line was very useful.



Task 2: babypipe
Properly widowing was not easy.  Once I drew it out, I understood that I
needed to close many more times than I did.  My submission now following
the outline very closely.  I checked for it being the first, last,
middle, or only task to properly handle it. 
