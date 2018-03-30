#!/usr/bin/perl
#######################################################################
# PROGRAM: This program reads input and prints "MATCH!" for each line #
# containing "b0b" or "b1b", and "NO MATCH!" for each line that       #
# doesn't.  When a match is found, the program also tells you what    #
# the bit in between the b's was.                                     #
#######################################################################

# Loop over each line of input
while(<>)
{
  # Parse line (the "$_" variable containins the current line)
  $match_query = $_ =~ /b(0|1)b/x;

  # Print "MATCH!" or "NO MATCH!"
  if ($match_query)
  {
    print "MATCH! Bit was: $1\n";
  }
  else
  {
    print "NO MATCH!\n";
  }
}

