#!/usr/bin/perl
#######################################################################
# PROGRAM: This program prints "MATCH!" or "NO MATCH!" dependiing on
# whether or not a line contains a string like "<67B>", i.e. number
# followed by A or B, all in <>'s and without spaces.  When a match is
# found, the numeric and letter values are printed out.
#######################################################################

# Loop over each line of input
while(<>)
{
  # Parse line (the "$_" variable containins the current line)
  $match_query = $_ =~ /<([0-9]*)(A|B)>/x;

  # Print "MATCH!" or "NO MATCH!"
  if ($match_query)
  {
    print "MATCH! Value was: ($1,$2)\n";
  }
  else
  {
    print "NO MATCH!\n";
  }
}

