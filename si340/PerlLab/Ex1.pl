#!/usr/bin/perl
#######################################################################
# PROGRAM: This program reads input and prints "MATCH!" for each line #
# containing "b#b"(where # is int 0-9), "NO MATCH!" for each line that doesn't.#  
#######################################################################

# Loop over each line of input
while(<>)
{
  # Parse line (the "$_" variable is the current line)
  $match_query = $_ =~ /b([0-9])b/x;

  # Print "MATCH!" or "NO MATCH!"
  if ($match_query) 
  {
    print "MATCH!\n";
  }
  else
  {
    print "NO MATCH!\n";
  }
}
