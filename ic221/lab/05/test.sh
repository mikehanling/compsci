#!/bin/bash
export CFLAGS="-Wall -Wextra -Wno-unused"

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


function test_valgrind(){
    echo "--- TEST valgrind ---"

    cd valgrind
    rm -f memleak memviolation
    gcc -g memleak.c -o memleak
    gcc -g memviolation.c -o memviolation

    cmd="valgrind --leak-check=full ./memleak  2>&1 | grep \"definitely lost\""
    res=$(eval $cmd)
    utest_z "$res" "$cmd"

    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi

    
    cmd="./memleak  2>&1 | grep \"definitely lost\""
    res=$(eval $cmd)
    expect="1 2 3 4 5  ----------- 1 2 3 4 5 1 2 3 4 5  "
    utest "$res" "$exepct" "(consitent output) $cmd"


    cmd="valgrind --leak-check=full ./memleak  2>&1 | grep \"0 errors\""
    res=$(eval $cmd)
    utest_nz "$res" "$cmd"
    if [ -z "$res" ]
    then
	echo
	echo "$(valgrind --leak-check=full ./memleak)"
	echo
    fi

    
    echo
    echo

    cmd="valgrind --leak-check=full ./memviolation 2>&1 | grep  \"0 errors\""
    res=$(eval $cmd)
    utest_nz "$res" "$cmd"

    if [ -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi

    
    cd ..
    echo
}

function ctime(){
    date +"%a %b %e %H:%M:%S %Y"
}


function test_simplefs(){
    echo "--- TEST simplefs ---"
 
    cd simplefs

    make clean 2>&1 >/dev/null
    cmd="make 2>&1 | tr '\n' ' '"
    res=$(eval $cmd)
    echo $res
    expect="gcc -Wall -Wno-unused-variable -g -c -o filesystem.o filesystem.c gcc -Wall -Wno-unused-variable -g -c -o shell.o shell.c gcc -o shell shell.o filesystem.o -lreadline -lncurses"
    echo $expect
    diff $res $expect
    utest "$res" "$expect" "Compiles without warnings or errors ($cmd)"

    
    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi

    echo
    echo "  -touch-"
    echo

    curtime=$(ctime)
    cmd='echo -e "touch a\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch a simplefs > ls   a $curtime simplefs >  "
    utest "$res" "$expect" "Touch one file ($cmd)"

    curtime=$(ctime)
    cmd='echo -e "touch go navy beat army\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go navy beat army simplefs > ls   go $curtime   navy $curtime   beat $curtime   army $curtime simplefs >  "
    utest "$res" "$expect" "Touch multiple filesone file ($cmd)"

    echo
    echo "  -memory touch-"
    echo

    cmd='echo -e "touch a\nexit" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res" "Touch one file memory leaks ($cmd)" 

    cmd='echo -e "touch a\nexit" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 contexts"'
    res=$(eval $cmd)
    utest_nz "$res" "Touch one file memory violations ($cmd)" 

    cmd='echo -e "touch a\nexit" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res" "Touch multiple files memory leaks ($cmd)" 

    cmd='echo -e "touch go navy beat army\nexit" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 contexts"'
    res=$(eval $cmd)
    utest_nz "$res" "Touch multiple files  memory violations ($cmd)" 

    echo
    echo "  -remove-"
    echo

    curtime=$(ctime)
    cmd='echo -e "touch a\nls\nrm a\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch a simplefs > ls   a $curtime simplefs > rm a simplefs > ls simplefs >  "
    utest "$res" "$expect" "Touch and remove one file ($cmd)"

    curtime=$(ctime)
    cmd='echo -e "touch go navy beat army\nls\nrm army\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go navy beat army simplefs > ls   go $curtime   navy $curtime   beat $curtime   army $curtime simplefs > rm army simplefs > ls   go $curtime   navy $curtime   beat $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove last file ($cmd)"

    curtime=$(ctime)
    cmd='echo -e "touch go navy beat army\nls\nrm go\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go navy beat army simplefs > ls   go $curtime   navy $curtime   beat $curtime   army $curtime simplefs > rm go simplefs > ls   navy $curtime   beat $curtime   army $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove first file ($cmd)"

    curtime=$(ctime)
    cmd='echo -e "touch go navy beat army\nls\nrm go\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go navy beat army simplefs > ls   go $curtime   navy $curtime   beat $curtime   army $curtime simplefs > rm go simplefs > ls   navy $curtime   beat $curtime   army $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove middle file ($cmd)"

    curtime=$(ctime)
    cmd='echo -e "touch go navy beat army\nls\nrm beat\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go navy beat army simplefs > ls   go $curtime   navy $curtime   beat $curtime   army $curtime simplefs > rm beat simplefs > ls   go $curtime   navy $curtime   army $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove middle file ($cmd)"

    curtime=$(ctime)
    cmd='echo -e "touch go navy beat army\nrm beat\ntouch goat\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go navy beat army simplefs > rm beat simplefs > touch goat simplefs > ls   go $curtime   navy $curtime   army $curtime   goat $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove middle file and add one more file($cmd)"

    echo
    echo   "-memory remove-"
    echo

    cmd='echo -e "touch a\nls\nrm a\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory leaks for touch and remove one file ($cmd)"

    cmd='echo -e "touch a\nls\nrm a\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 context"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory violations  for touch and remove one file ($cmd)"

    cmd='echo -e "touch go navy beat army\nls\nrm go\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res"  "Memory leaks for touch many remove first ($cmd)"

    cmd='echo -e "touch go navy beat army\nls\nrm go\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 context"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory violations  for touch and remove first ($cmd)"

    cmd='echo -e "touch go navy beat army\nls\nrm army\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res"  "Memory leaks for touch many remove last ($cmd)"

    cmd='echo -e "touch go navy beat army\nls\nrm army\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 context"'
    res=$(eval $cmd)
    utest_nz "$res"  "Memory violations  for touch and remove last ($cmd)"

    echo
    echo   "-touch update time-"
    echo

delay_touch=$(cat <<EOF
echo "touch go navy beat army"
echo "ls"
sleep 1
echo "touch navy"
echo "ls"
EOF
)
    curtime=$(ctime)
    cmd='eval "$delay_touch" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    nexttime=$(ctime)
    expect="simplefs > touch go navy beat army simplefs > ls   go $curtime   navy $curtime   beat $curtime   army $curtime simplefs > touch navy simplefs > ls   go $curtime   navy $nexttime   beat $curtime   army $curtime simplefs >  "
    utest "$res" "$expect" "Touch updates time ($cmd)"

    cmd='eval "$delay_touch" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory leak for touch update time ($cmd)"

    cmd='eval "$delay_touch" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 context"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory violation for touch update time ($cmd)"


#    echo "($res)"
#    echo "($expect)"
    
    
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

test_valgrind
test_simplefs
