#!/usr/bin/perl

while(<>) {
  $match_query = $_ =~ /<b>(.*?)<\/b>/x;
  
  if ($match_query) {
    print "$1\n";
  }
}
