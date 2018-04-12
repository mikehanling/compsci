#!/bin/bash

red='\e[0;31m'
green='\e[0;32m'
nc='\e[0m'     

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}


function utest( ){

    if [ "$1" == "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -ne "\t\t "
    echo "$3"
}

function utest_ne( ){

    if [ "$1" != "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -ne "\t\t "
    echo "$3"
}

function utest_nz( ){
    if [ ! -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -ne "\t\t "
    echo "$2"
}

function utest_z( ){
    if [ -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -ne "\t\t "
    echo "$2"
}

function ctime(){
    date +"%a %b %e %H:%M:%S %Y"
}


function test_logger(){
    echo "--- TEST logger ---"

    cd logger

    
    cmd="clang -g -Wall write-log.c -o write-log > /dev/null 2>&1" 
    res=$(eval $cmd)
    utest_z "$res" "write-log compiles without warnings or errors ($res)"

    cmd="clang -g -Wall read-log.c -o read-log > /dev/null 2>&1" 
    res=$(eval $cmd)
    utest_z "$res" "read-log compiles without warnings or errors ($res)"

    chmod u+s write-log
    chmod u+s read-log

    cmd="ls -l $HOME/ic221-lab10-log.txt  | cut -d \" \"  -f 1 | grep -e \"-rw-------\""
    res=$(eval $cmd)
    utest_nz "$res" "log file is only read/write by user ($cmd)"

    v1=$RANDOM
    cur_time1=$(ctime)
    cmd="./write-log \"$v1\"; tail -1 $HOME/ic221-lab10-log.txt"
    res=$(eval $cmd)
    expect="[$cur_time1] ($UID) $v1"
    utest "$res" "$expect" "Random Value 1 properly written to file"

    v2=$RANDOM
    cur_time2=$(ctime)
    cmd="./write-log \"$v2\"; tail -1 $HOME/ic221-lab10-log.txt"
    res=$(eval $cmd)
    expect="[$cur_time2] ($UID) $v2"
    utest "$res" "$expect" "Random Value 2 properly written to file ($cmd)"

    cmd="tail -2 $HOME/ic221-lab10-log.txt | tr \"\n\" \" \""
    res=$(eval $cmd)
    expect="[$cur_time1] ($UID) $v1 [$cur_time2] ($UID) $v2 "
    utest "$res" "$expect" "Check last 2 values ($cmd)"

    test_write_log="/home/mids/m999999/lab-10-test/test-write-log"
    test_read_log="/home/mids/m999999/lab-10-test/test-read-log"

    v3=$RANDOM
    cur_time3=$(ctime)
    cmd="$test_write_log $v3 ; tail -1 $HOME/ic221-lab10-log.txt"
    res=$(eval $cmd)
    expect="[$cur_time3] ($(id -u m999999)) $v3"
    utest "$res" "$expect" "Other users can write to the log - value 1 ($cmd)"

    v4=$RANDOM
    cur_time4=$(ctime)
    cmd="$test_write_log $v4 ; tail -1 $HOME/ic221-lab10-log.txt"
    res=$(eval $cmd)
    expect="[$cur_time4] ($(id -u m999999)) $v4"
    utest "$res" "$expect" "Other users can write to the log - value 2 ($cmd)"

    cmd="$test_read_log | tr \"\\n\" \" \" | sed \"s/ \$//g\" | sed \"s/^ //g\""
    res=$(eval $cmd)
    expect="[$cur_time4] ($(id -u m999999)) $v4"
    utest "$res" "$expect" "Other can read last line of log ($cmd)"


    cmd="$test_read_log 2 | tr \"\\n\" \" \" | sed \"s/ \$//g\" | sed \"s/^ //g\""
    res=$(eval $cmd)
    expect="[$cur_time3] ($(id -u m999999)) $v3 [$cur_time4] ($(id -u m999999)) $v4"
    utest "$res" "$expect" "Other can read last 2 line of log ($cmd)"

    cmd="$test_read_log 4 | tr \"\\n\" \" \" | sed \"s/ \$//g\" | sed \"s/^ //g\""
    res=$(eval $cmd)
    expect="[$cur_time1] ($UID) $v1 [$cur_time2] ($UID) $v2 [$cur_time3] ($(id -u m999999)) $v3 [$cur_time4] ($(id -u m999999)) $v4"
    utest "$res" "$expect" "Other can read last 4 line of log ($cmd)"
    
    cmd="$test_write_log CLEAR >/dev/null 2>&1 ; tail -1 $HOME/ic221-lab10-log.txt"
    res=$(eval $cmd)
    expect="[$cur_time4] ($(id -u m999999)) $v4"
    utest "$res" "$expect" "Others cannot clear the log file ($cmd)"


    cmd="$test_write_log CLEAR 2>&1 | grep \"ERROR: Unauthorized user attempting to clear the log file\""
    res=$(eval $cmd)
    utest_nz "$res" "Error message to stderr when others try to clear log file ($cmd)"

    cd ..
    echo
}


function test_secret(){
    echo "--- TEST SECRET ---"
    
    cd secret
    
    
    cmd="cat hackme-1/secret | tr \"\\n\" \" \" | sed \"s/ //g\" | sha1sum"
    expect="90bee8b9a3584d8aeed389d689f7d91c60e4b28d  -"
    res=$(eval $cmd)
    utest "$res" "$expect" "Hackme-1: Do you know the secret? ($cmd) ($res)"


    cmd="cat hackme-2/secret | tr \"\\n\" \" \" | sed \"s/ //g\" | sha1sum"
    expect="3a8ee221b2f17908c8b0e59ce7171b743df28475  -"
    res=$(eval $cmd)
    utest "$res" "$expect" "Hackme-1: Do you know the secret? ($cmd) ($res)"


    cmd="cat hackme-3/secret | tr \"\\n\" \" \" | sed \"s/ //g\" | sha1sum"
    expect="392580009890ff9033f41e99ceb42ad174402b2e  -"
    res=$(eval $cmd)
    utest "$res" "$expect" "Hackme-1: Do you know the secret? ($cmd) ($res)"


    cmd="cat hackme-4/secret | tr \"\\n\" \" \" | sed \"s/ //g\" | sha1sum"
    expect="7883131d93221699e5611900da567bc41f4c21d0  -"
    res=$(eval $cmd)
    utest "$res" "$expect" "Hackme-1: Do you know the secret? ($cmd) ($res)"



    echo -e "\t\t (- Don't forget to include the description of your hack in your README. Find more than one in each for extra credit :-)"
    cd ..
}

if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

test_logger
test_secret



