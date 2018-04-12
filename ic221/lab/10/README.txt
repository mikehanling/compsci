----------------------------------------------------------------------------
Name:  Mike Hanling
Alpha: 202430

Collaborator(s): Chris Daves

Resources Used:

Hours: 04
----------------------------------------------------------------------------
  Replace the X's above with your name and alpha, and also list any collaborator
  or other resources you used. Please also indicate the number of hours
  (including hours in the lab period) you spent on this assignment.

  After completing the assignment, please answer these questions to provide
  feedback.

  * What did you learn from this assignment?
I really learned how to look at program's vulnerabilities.

  * What part of the assignment was easier then you expected?
I thought that messing with the file pointer head was easier than I
thought it was going to be.

  * What part of the assignment was harder then you expected?
Some of the exploits were hard.  I have not done this type of thing
before too much, so it made me think differently.

  * What would you suggest for improving this assignment?
Nothing, I really liked it.

  * Any additional information you'd like to share regarding this assignment?
No

----------------------------------------------------------------------------

  Below, fill out this worksheet with the appropriate answers/comments
  to the following questions/prompts. If there are no direct
  questions, please provide some basic comments about each part of the
  assignment.

-------------------------------------------------------------------------

Part 1: logger 

Reading from the log was a matter of counting the newlines as I moved my
way backwards through the file.  One note is that since any function
that gets a character from a stream moves the pointer, I had to move it
back two every tim e to actually get anywhere.
Writing to the log just had to check to make sure that deleting was done
by the correct person.  Set bits had to be used.

Part 2: hackme
*Chris and I worked closely on 2 and 3 together, and 1 and 4 we talked
about together.*

1 - I used my own "sort" because that was hard coded and then execvp'ed.
I added my directory to the front of the PATH and then my "sort" which
just cat'ed the secret file, was run.

2 - I believed that I could do an injection attack.  Give /dev/null as a
file and then put a : and then "exploit" for my own code to cat the
secret file (I updated the PATH).  This did not work until I put all of
that in quotes at the command line.  Bash is scary and I do not truly
understand, but somehow it worked.  

3 - Similar to 1, I saw that cat was system'ed.  I wrote my own cat,
added my directory to the front of PATH, and then getting the secret
file was trivial.

4 - Since this section had user input that was used unchecked (the
command line argument for the output file), I gave the output file as
/dev/null then placed a ; immediately after that and "exploit"
immediately after that (no spaces).  I wrote "exploit", added my
directory to the front of PATH, and that was how the secret was gained.
