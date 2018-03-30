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


function test_task1(){
    echo "--- TEST TASK 1 ---"
    
    cd task1

    cmd="./allusers.sh"
    res=$(eval $cmd)
    expect=$(eval $(echo 'Y3V0IC1kICI6IiAtZiA1IC9ldGMvcGFzc3dkCg==' | base64 -d))
    utest "$res" "$expect" "all usernames ($cmd)"

    cd ..
    echo
}

function test_task2(){
    echo "--- TEST TASK 2 ---"

    cd task2
    
    cmd="./getname.sh aviv"
    res=$(eval $cmd)
    expect=$(grep "^aviv:" /etc/passwd | cut -d ":" -f 5)
    utest "$res" "$expect" "($cmd)"

    cmd="./getname.sh rye"
    res=$(eval $cmd)
    expect=$(grep "^rye:" /etc/passwd | cut -d ":" -f 5)
    utest "$res" "$expect" "($cmd)"


    cmd="./getname.sh m17XXXX"
    res=$(eval $cmd)
    expect=$(grep "^m17XXXX:" /etc/passwd | cut -d ":" -f 5)
    utest "$res" "$expect" "($cmd)"

    cmd="./getname.sh missler"
    res=$(eval $cmd)
    expect=$(grep "^missler:" /etc/passwd | cut -d ":" -f 5)
    utest "$res" "$expect" "($cmd)"

    cd ..
    echo

}


function test_task3(){
    echo "--- TEST TASK 3 ---"
    
    cd task3

    cmd="./getsize.sh empty.txt"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "empty test ($cmd)"



    cmd="./getsize.sh medium.txt"
    res=$(eval $cmd)
    expect="1847"
    utest "$res" "$expect" "medium test ($cmd)"

    cmd="./getsize.sh larger.txt"
    res=$(eval $cmd)
    expect="4000"
    utest "$res" "$expect" "larger test ($cmd)"

    let i=$RANDOM%100
    cmd="head -c $i /dev/zero > test.txt ; ./getsize.sh test.txt ; rm -f test.txt"
    res=$(eval $cmd)
    expect="$i"
    utest "$res" "$expect" "random size ($cmd)"

    cmd="./getsize.sh file_does_not_exist 2>&1 | grep -i 'ERROR:.*file_does_not_exist.*'"
    res=$(eval $cmd)
    utest_nz "$res" "prints error and filenmae on nonexistent file ($cmd)"

    cmd="./getsize.sh foobarbaz >/dev/null 2>error.tmp; grep -i 'ERROR:.*foobarbaz.*' error.tmp; rm -f error.tmp"
    res=$(eval $cmd)
    utest_nz "$res" "prints error and filenmae to stderr ($cmd)"

    cd ..
    echo
}

function test_task4(){
    echo "--- TEST TASK 4 ---"
    
    cd task4

    cmd="./getallsizes.sh empty.txt"
    res=$(eval $cmd)
    expect="empty.txt 0"
    utest "$res" "$expect" "empty test ($cmd)"


    cmd="./getallsizes.sh medium.txt"
    res=$(eval $cmd)
    expect="medium.txt 1847"
    utest "$res" "$expect" "medium test ($cmd)"

    cmd="./getallsizes.sh larger.txt"
    res=$(eval $cmd)
    expect="larger.txt 4000"
    utest "$res" "$expect" "larger test ($cmd)"

    cmd="./getallsizes.sh empty.txt larger.txt medium.txt | tr '\n' ' '"
    res=$(eval $cmd)
    expect="empty.txt 0 larger.txt 4000 medium.txt 1847 "
    utest "$res" "$expect" "three files test ($cmd)"

    
    let i=$RANDOM%100
    cmd="head -c $i /dev/zero > test.txt ; ./getallsizes.sh test.txt ; rm -f test.txt"
    res=$(eval $cmd)
    expect="test.txt $i"
    utest "$res" "$expect" "random size ($cmd)"

    cmd="./getallsizes.sh medium.txt file_does_not_exist larger.txt 2>&1 | grep -i 'ERROR:.*file_does_not_exist.*'"
    res=$(eval $cmd)
    utest_nz "$res" "prints error and filenmae on nonexistent file ($cmd)"

    cmd="./getallsizes.sh foobarbaz >/dev/null 2>error.tmp; grep -i 'ERROR:.*foobarbaz.*' error.tmp; rm -f error.tmp"
    res=$(eval $cmd)
    utest_nz "$res" "prints error and filenmae to stderr ($cmd)"

    cd ..
    echo
}

function test_task5(){
    echo "--- TEST TASK 5 ---"
    
    cd task5

    cmd="./isbiggerthan.sh 0 empty.txt"
    res=$(eval $cmd)
    expect="yes"
    utest "$res" "$expect" "empty test 0 ($cmd)"

    cmd="./isbiggerthan.sh 1 empty.txt"
    res=$(eval $cmd)
    expect="no"
    utest "$res" "$expect" "empty test 1 ($cmd)"

    cmd="./isbiggerthan.sh 10 medium.txt"
    res=$(eval $cmd)
    expect="yes"
    utest "$res" "$expect" "medium test 10 ($cmd)"

    cmd="./isbiggerthan.sh 2000 medium.txt"
    res=$(eval $cmd)
    expect="no"
    utest "$res" "$expect" "medium test 2000 ($cmd)"

    cmd="./isbiggerthan.sh 2000 larger.txt"
    res=$(eval $cmd)
    expect="yes"
    utest "$res" "$expect" "larger test 2000 ($cmd)"

    cmd="./isbiggerthan.sh 5000 larger.txt"
    res=$(eval $cmd)
    expect="no"
    utest "$res" "$expect" "larger test 5000 ($cmd)"

    let i=$RANDOM%100
    cmd="head -c $i /dev/zero > test.txt ; ./isbiggerthan.sh 100 test.txt ; rm -f test.txt"
    res=$(eval $cmd)
    expect="no"
    utest "$res" "$expect" "random size 100 ($cmd)"

    let i=$RANDOM%100+10
    cmd="head -c $i /dev/zero > test.txt ; ./isbiggerthan.sh 10 test.txt ; rm -f test.txt"
    res=$(eval $cmd)
    expect="yes"
    utest "$res" "$expect" "random size 10 ($cmd)"

    cmd="./isbiggerthan.sh 2>&1 | grep -i 'ERROR:.*Require path and size.*'"
    res=$(eval $cmd)
    utest_nz "$res" "Error no arguments ($cmd)"

    cmd="./isbiggerthan.sh >/dev/null 2> error.tmp ; grep -i 'ERROR:.*Require path and size.*' error.tmp; rm -f error.tmp"
    res=$(eval $cmd)
    utest_nz "$res" "Error no arguments to stderr ($cmd)"

    cmd="./isbiggerthan.sh num larger.txt 2>&1 | grep -i 'ERROR:.*Require a number.*'"
    res=$(eval $cmd)
    utest_nz "$res" "Error not a number ($cmd)"

    cmd="./isbiggerthan.sh num larger.txt >/dev/null 2> error.tmp ; grep -i 'ERROR:.*Require a number.*' error.tmp; rm -f error.tmp"
    res=$(eval $cmd)
    utest_nz "$res" "Error not a number to stderr ($cmd $res)"

    cmd="./isbiggerthan.sh -1 larger.txt 2>&1 | grep -i 'ERROR:.*Require a positive number.*'"
    res=$(eval $cmd)
    utest_nz "$res" "Error not a positive number ($cmd)"

    cmd="./isbiggerthan.sh -1 larger.txt >/dev/null 2>error.tmp ; grep -i 'ERROR:.*Require a positive number.*' error.tmp; rm -f error.tmp"
    res=$(eval $cmd)
    utest_nz "$res" "Error not a positive number to stderr ($cmd) ($res)"

    

    cd ..
    echo
}

function test_task6(){
    echo "--- TEST TASK 6 ---"
    
    cd task6

    cmd="./isbiggerthanall.sh 0 empty.txt larger.txt medium.txt | tr -s '\n' ' '"
    res=$(eval $cmd)
    expect="empty.txt larger.txt medium.txt "
    utest "$res" "$expect" "bigger than 0 ($cmd)"
    
    cmd="./isbiggerthanall.sh 1 empty.txt larger.txt medium.txt | tr -s '\n' ' '"
    res=$(eval $cmd)
    expect="larger.txt medium.txt "
    utest "$res" "$expect" "bigger than 1 ($cmd)"

    cmd="./isbiggerthanall.sh 2000 empty.txt larger.txt medium.txt | tr -s '\n' ' '"
    res=$(eval $cmd)
    expect="larger.txt "
    utest "$res" "$expect" "bigger than 2000 ($cmd)"

    cmd="./isbiggerthanall.sh 9999 empty.txt larger.txt medium.txt | tr -s '\n' ' '"
    res=$(eval $cmd)
    expect=""
    utest "$res" "$expect" "bigger than 9999 ($cmd)"
    
    cmd="./isbiggerthanall.sh num larger.txt 2>&1 | grep -i 'ERROR:.*Require a number.*'"
    res=$(eval $cmd)
    utest_nz "$res" "Error not a number ($cmd)"

    cmd="./isbiggerthanall.sh -1 larger.txt 2>&1 | grep -i 'ERROR:.*Require a positive number.*'"
    res=$(eval $cmd)
    utest_nz "$res" "Error negative number ($cmd)"

    cmd="./isbiggerthanall.sh 2>&1 | grep -i 'ERROR:.*Require a size and at least one file.*'"
    res=$(eval $cmd)
    utest_nz "$res" "Error no arguments ($cmd)"

    cmd="./isbiggerthanall.sh 1 doesnotexist.txt 2>&1 | grep -i 'ERROR:.*File doesnotexist.txt does not exist.*'"
    res=$(eval $cmd)
    utest_nz "$res" "Error file does not exist ($cmd)"

    
    cd ..
    echo 
}


if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

echo

test_task1
test_task2
test_task3
test_task4
test_task5
test_task6

# test_makefile_multi
# test_mycp
# test_myls
# test_mytouch
# test_makefile_all

# test_term-status
# test_timer
# test_mini-sh
# test_makefile
