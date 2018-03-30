#!/bin/bash

# isbiggerthan.sh size path
#
# Print the path

if [ $# -lt 2 ]
then
    echo "isbiggerthan.sh: ERROR: Require path and size " 1>&2
    exit 2
fi

#check if it is a number
if [ "$1" -eq "$1" ] 2> /dev/null # check for a number
then
    echo -n #it's a number
else
    echo "isbiggerthan.sh: ERROR: Require a number for $1" 1>&2
    exit 3
fi

if [ $1 -lt 0 ]
then 
    echo "isbiggerthan.sh: ERROR: Require a positive number for $1" 1>&2
    exit 4
fi

if [ ! -e $2 ]
then
    echo "isbiggerthan.sh: ERROR: $1 does not exist" 1>&2
    exit 5
fi

s=$(wc -c $2 | cut -d " " -f 1 -)

if [ $s -lt $1 ]
then
    exit 1
else
    echo 0
fi

