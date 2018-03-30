#!/usr/bin/perl

while(<>) {
  $match_query = $_ =~ /((M|T|W|R|F){1,5}(\d|10){1,2})/x;
  
  if ($match_query) {
    print "$1\n";
  }
}
