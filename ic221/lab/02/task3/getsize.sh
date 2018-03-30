#!/bin/bash

# getsize.sh path
#
# Print the path

if [ $# -lt 1 ]
then
    echo "getsize.sh: ERROR: Require file" 1>&2
elif [ $# -gt 1 ]
then
    echo "getsize.sh: ERROR: Only one file" 1>&2
elif [ ! -e $1 ]
then
    echo "getsize.sh: ERROR: $1 does not exist" 1>&2
else
    wc -c $1 | cut -d " " -f 1 -
fi

