#!/bin/bash

# isbiggerthan.sh size [path [path [...]]]
#
# print the files that are bigger than the size

if [ $# -lt 2 ]
then
    echo "isbiggerthanall.sh: ERROR: Require a size and at least one file" 1>&2
    exit 2
fi

i=1
for f in $*
do
    if [ $i -ne 1 ]  #not for first argument which is the size
    then
	./isbiggerthan.sh $1 $f > /dev/null  2>&1  #run isbiggerthan.sh
	case $? in #check exit statuses
	    0)
		echo $f ;;
            1)
		echo -n ;;
	    2) 
		echo "isbiggerthanall.sh: ERROR: isbiggerthan.sh" 1>&2 ;;
	    3)
		echo "isbiggerthanall.sh: ERROR: Require a number for size not $1 " 1>&2 ;;
	    4)
		echo "isbiggerthanall.sh: ERROR: Require a positive number " 1>&2 ;;
	    5)
		echo "isbiggerthanall.sh: ERROR: File $f does not exist" 1>&2 ;;
	    *)
		echo "HUH? $?" ;; #got an invalid exit status
	esac
    fi

    let i++ #increment i
done
