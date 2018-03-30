#!/usr/bin/perl

while(<>) {
  $match_query = $_ =~ /SI(\d\d\d([A-Z])?)/x;
  
  if ($match_query) {
    print "$1\n";
  }
}
