#!/bin/bash

# getallsizes.sh [path [path [..]]]
#
# Print the size of all the files in the path

for f in $* #iterate through all command line arguments
do
    if [ ! -e $f ]
    then
        echo "getallsizes.sh: ERROR: File $f does not exist" 1>&2
    else  
        s=$(wc -c $f | cut -d " " -f 1 -)
        echo $f $s
    fi
done
