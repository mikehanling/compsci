#!/bin/bash
export CFLAGS="-Wall -Wextra -Wno-unused"
red='\e[0;31m'
green='\e[0;32m'
nc='\e[0m'     

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}

function ctime(){
    date +"%a %b %_d %H:%M:%S %Y" | tr -s " "
}

function stattime(){
    date +"%Y-%m-%d %H:%M:%S"
}

function compile_mycp(){
    if [ "$(basename $PWD)"  == "mycp" ]
    then
	clang -g -Wall    mycp.c   -o mycp
    else
	cd mycp
	clang -g -Wall    mycp.c   -o mycp
	cd ..
    fi
}

function compile_myls(){
    if [ "$(basename $PWD)"  == "myls" ]
    then
	clang -g -Wall -lbsd   myls.c   -o myls
    else
	cd myls
	clang -g -Wall -lbsd   myls.c   -o myls
	cd ..
    fi
}

function compile_mytouch(){
    if [ "$(basename $PWD)"  == "mytouch" ]
    then
	clang -g -Wall   mytouch.c   -o mytouch
    else
	cd mytouch
	clang -g -Wall   mytouch.c   -o mytouch
	cd ..
    fi
}


function clean_mycp(){
    if [ "$basename $PWD)"  == "mycp" ]
    then
	rm -f mycp
    else
	cd mycp
	rm -f mycp
	cd ..
    fi
}

function clean_myls(){
    if [ "$basename $PWD)"  == "myls" ]
    then
	rm -f myls
    else
	cd myls
	rm -f myls
	cd ..
    fi
}

function clean_mytouch(){
    if [ "$basename $PWD)"  == "mytouch" ]
    then
	rm -f mytouch
    else
	cd mytouch
	rm -f mytouch
	cd ..
    fi
}


function compile(){
    compile_mycp
    compile_myls
    compile_mytouch
}

function clean(){
   clean_mycp
   clean_myls
   clean_mytouch
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


function test_makefile_simple(){
    echo "--- TEST MAKEFILE SIMPLE ---"
    
    cd makefile/simple
    rm -f compileme

    make 1>/dev/null 2>&1
    cmd="ls -l compileme 2>/dev/null | cut -d \" \" -f 1 | grep x"
    res=$(eval $cmd)
    utest_nz "$res" "make ($cmd)"

    cmd="./compileme | grep \"You compiled me!\""
    res=$(eval $cmd)
    #expect="You compiled me! .... Hurray!"
    utest_nz "$res" "./compileme correct execution ($cmd)"

    make clean 1>/dev/null 2>&1
    cmd="ls compileme 2>/dev/null"
    res=$(eval $cmd)
    utest_z "$res" "make clean ($cmd)"

    cd ../..
    
    echo
}

function test_makefile_multi(){
    echo "--- TEST MAKEFILE MULTI ---"
    
    cd makefile/multi
    rm -f runme runme_too *.o *~

    make runme >/dev/null 2>&1
    cmd="ls -l runme | cut -d \" \" -f 1 | grep x"
    res=$(eval $cmd)
    utest_nz "$res" "make runme ($cmd)"

    cmd="ls runme.o library.o | grep \"ls: cannot access\""
    res=$(eval $cmd)
    utest_z "$res" "object files ($cmd)"

    cmd="./runme | grep \"\!dlroW olleH\""
    res=$(eval $cmd)
    utest_nz "$res" "runme expected execution ($cmd)"

    rm -f runme runme_too *.o *~
    make runme_too >/dev/null 2>&1
    cmd="ls -l runme_too | cut -d \" \" -f 1 | grep x"
    res=$(eval $cmd)
    utest_nz "$res" "make runmetoo ($cmd)"

    cmd="ls runme_too.o library.o fun.o 2>&1 | grep \"ls: cannot access\""
    res=$(eval $cmd)
    utest_z "$res" "object files ($cmd)"

    cmd="./runme_too | grep \"\!d\!r0W 0\!\!3H\""
    res=$(eval $cmd)
    utest_nz "$res" "runme_too expected execution ($cmd)"

    
    rm -f runme runme_too *.o *~
    make >/dev/null 2>&1
    cmd="ls -l runme | cut -d \" \" -f 1 | grep x"
    res=$(eval $cmd)
    utest_nz "$res" "make all -runme- ($cmd)"

    cmd="ls -l runme_too | cut -d \" \" -f 1 | grep x"
    res=$(eval $cmd)
    utest_nz "$res" "make all -runme_too- ($cmd)"

    cmd="ls runme.o library.o fun.o runme_too.o 2>&1 | grep \"ls: cannot access\""
    res=$(eval $cmd)
    utest_z "$res" "make all -object files- ($cmd)"

    cmd="./runme | grep \"\!dlroW olleH\""
    res=$(eval $cmd)
    utest_nz "$res" "make all -runme expected execution- ($cmd)"

    cmd="./runme_too | grep \"\!d\!r0W 0\!\!3H\""
    res=$(eval $cmd)
    utest_nz "$res" "make all -runme_too expected execution- ($cmd)"

    make clean >/dev/null 2>&1
    cmd="ls runme runme_too runme.o library.o fun.o runme_too.o 2>&1 | wc -l "
    res=$(eval $cmd)
    expect="6"
    utest "$res" "$expect" "make clean ($cmd)"

    rm -f runme runme_too *.o *~

    cd ../..
    
    echo
}


function test_makefile_all(){
    echo "--- TEST MAKEFILE (others)---"

    clean_term-status
    cd term-status
    make 1>/dev/null 2>&1
    res=$(ls foursons)
    utest_nz "$res" "term-status (make)"

}


function test_mycp(){
    echo "--- TEST MYCP ---"
    
    cd mycp

    head -c 5000 /dev/urandom > test.dat
    ./mycp test.dat test.cp.dat
    cmd="diff test.dat test.cp.dat"
    res=$(eval $cmd)
    utest_z "$res" "mycp copy random file ($cmd)"
    
    cmd="egrep -e \"read.*\(.*fd_src.*,.*buf.*,.*BUFFSIZE.*\)\" -e \"read.*\(.*fd_src,.*buf,.*4096.*\)\" mycp.c"
    res=$(eval $cmd)
    utest_nz "$res" "mycp buffered read ($cmd)"

    rm -f test.cp.dat
    chmod 440 test.dat
    ./mycp test.dat test.cp.dat
    cmd="ls -l test.cp.dat | cut -d \" \" -f 1 | grep -e '-r--r-----'"
    res=$(eval $cmd)
    utest_nz "$res" "mycp preserve mode ($cmd)"
    
    mkdir test_dir 2>/dev/null #incase it doesn't exist
    cmd="./mycp test_dir testdir.cp 2>&1 | grep './mycp: test_dir: Is a directory'"
    res=$(eval $cmd)
    utest_nz "$res" "mycp dir error ($cmd)"

    cmd="./mycp test_dir testdir.cp >/dev/null 2> err; cat err | grep './mycp: test_dir: Is a directory'; rm -f err"
    res=$(eval $cmd)
    utest_nz "$res" "mycp dir error to stderr ($cmd)"

    cmd="[ -e tesdir.cp ]; echo \$?"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect"  "mycp does not create destination file on bad copy ($cmd)"
    rm -rf testdir.cp

    rm -f test.cp.dat
    cmd="./mycp BAD_FILE test.cp.dat 2>&1 | grep '\./mycp: No such file or directory'"
    res=$(eval $cmd)
    utest_nz "$res" "mycp error on BAD_FILE ($cmd)"

    rm -f test.cp.dat
    cmd="./mycp BAD_FILE test.cp.dat >/dev/null 2>err; cat err | grep '\./mycp: No such file or directory'; rm -f err"
    res=$(eval $cmd)
    utest_nz "$res" "mycp error on BAD_FILE to stderr ($cmd)"

    cmd="[ -e test.cp.dat ]; echo \$?"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "mycp does not create destination on BAD_FILE ($cmd)"

    rm -f test.dat 
    
    cd ..
    echo
}

function test_myls(){
    echo "--- TEST MYLS ---"

    cd myls

    #create a testing directory
    rm -rf _test_dir >/dev/null ; mkdir _test_dir >/dev/null
    mkdir _test_dir/subdir >/dev/null
    cat < /dev/null > _test_dir/a.txt
    chmod 777 _test_dir/a.txt
    cat < /dev/null > _test_dir/empty.txt
    chmod 643 _test_dir/empty.txt
    head -c 7896 < /dev/urandom > _test_dir/rand.txt
    chmod 644 _test_dir/rand.txt

    cd _test_dir

    cur_time=$(ctime)
    touch -d "$cur_time" a.txt empty.txt subdir rand
    
    user=$USER
    group=$(groups | cut -d " " -f 1)

    cmd="../myls  | cut -f 1 | sort | tr '\\n' ' ' | tr -s ' ' "
    res=$(eval $cmd)
    expect=$(ls -Cla | awk '{print $1}' | grep -v total | sort | tr "\n" " " | tr -s ' ' )
    utest "$res" "$expect" "myls prints modes ($cmd) "

    cmd="../myls  | cut -f 2 | sort | tr '\\n' ' '"
    res=$(eval $cmd)
    expect=$(ls -a | sort | tr '\n' ' ')
    utest "$res" "$expect" "myls prints file names ($cmd)"


    cmd="../myls  | cut -f 3 | sort | tr '\\n' ' ' | tr -s ' '"
    res=$(eval $cmd)
    expect=$(ls -Cla | awk '{print $3}' | grep -v '^$' | sort | tr "\n" " " | tr -s ' ')
    utest "$res" "$expect" "myls prints usernames ($cmd) "

    cmd="../myls  | cut -f 4 | sort | tr '\n' ' ' | tr -s ' '"
    res=$(eval $cmd)
    expect=$(ls -Cla | awk '{print $4}' |  grep -v '^$' | sort | tr "\n" " " | tr -s ' ')
    utest "$res" "$expect" "myls prints groups ($cmd)"

    cmd="../myls  | cut -f 5 | sort | tr '\n' ' '"
    res=$(eval $cmd)
    expect=$(ls -Cla | awk '{print $5}' |  grep -v '^$' | sort | tr "\n" " " | tr -s ' ')
    utest "$res" "$expect" "myls prints sizes ($cmd)"

    cmd="../myls  | cut -f 6 | sort | tr '\n' ' ' | tr -s ' '"
    res=$(eval $cmd)
    expect=$(ls -Cla --time-style=+"%a %b %_d %H:%M:%S %Y" | awk '{print $6 " " $7 " " $8 " " $9 " " $10}' | grep -v '^[[:space:]]*$' | sort | tr "\n" " " | tr -s ' ')
    utest "$res" "$expect" "myls prints dates ($cmd)"


    cd ..
    rm -rf _test_dir

    cd ..
    echo
}

function test_mytouch(){
    echo "--- TEST MYTOUCH ---"

    cd mytouch

    cur_time=$(ctime)
    sec_time=$(date +%s)
    touch -d "$cur_time" test.txt
    
    sleep 1

    new_time=$(ctime)

    cmd="./mytouch test.txt | tr '\n' ' ' | tr -s ' '"
    res=$(eval $cmd)
    expect="Last Modified: $cur_time New Modified: $new_time "
    utest "$res" "$expect" "mytouch output accurate ($cmd)"

    cmd="./mytouch test.txt >/dev/null ; stat --printf=\"%X\" test.txt | awk '{ print \$1-1 }' "
    res=$(eval $cmd)
    expect="$sec_time"
    utest "$res" "$expect" "mytouch updates access time is accurate ($cmd)"

    cur_time=$(stattime)
    ./mytouch test.txt > /dev/null
    cmd="stat --printf=\"%Y\" test.txt | awk '{ print \$1-1 }'"
    res=$(eval $cmd)
    expect="$sec_time"
    utest "$res" "$expect" "mytouch updates modification time is accurate ($cmd)"

    rm -f test.txt
    cmd="./mytouch __BAD_FILE 2>&1"
    res=$(eval $cmd)
    expect="./mytouch: No such file or directory"
    utest "$res" "$expect" "prints error on file does not exist ($cmd)"

    cmd="./mytouch __BAD_FILE >/dev/null 2>err; cat err; rm -f err"
    res=$(eval $cmd)
    expect="./mytouch: No such file or directory"
    utest "$res" "$expect" "error to stderr ($cmd)"

    cmd="[ -e __BAD_FILE ] ; echo \$?"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "EXTRA CREDIT -- ignore previous two fails if passes ($cmd)"
    rm -f __BAD_FILE

    cd ..
    echo
}

function test_makefile_all(){
    echo "--- TEST MAKEFILE (others)---"

    clean_mycp
    cd mycp
    make 1>/dev/null 2>&1
    res=$(ls mycp 2>/dev/null)
    utest_nz "$res" "mycp (make)"

    make clean 1>/dev/null 2>&1
    res=$(ls mycp 2>/dev/null)
    utest_z "$res" "mycp (make clean)"
    cd ..

    clean_myls
    cd myls
    make 1>/dev/null 2>&1
    res=$(ls myls 2>/dev/null)
    utest_nz "$res" "myls (make)"

    make clean 1>/dev/null 2>&1
    res=$(ls myls 2>/dev/null)
    utest_z "$res" "myls (make clean)"
    cd ..

    clean_mytouch
    cd mytouch
    make 1>/dev/null 2>&1
    res=$(ls mytouch 2>/dev/null)
    utest_nz "$res" "mytouch (make)"

    make clean 1>/dev/null 2>&1
    res=$(ls mytouch 2>/dev/null)
    utest_z "$res" "mytouch (make clean)"
    cd ..

    echo
}


if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

clean
test_makefile_all
compile

echo


test_makefile_simple
test_makefile_multi
test_mycp
test_myls
test_mytouch


# test_term-status
# test_timer
# test_mini-sh
# test_makefile
