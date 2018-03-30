#!/bin/bash

red='\e[0;31m'
green='\e[0;32m'
nc='\e[0m'     

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}

function ctime(){
    date +"%a %b %d %H:%M:%S %Y"
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

function test_makefile(){
    echo "--- TEST MAKEFILE ---"

    cd unroll
    rm -f sleep-unroll
    make 1>/dev/null 2>&1
    res=$(ls sleep-unroll)
    utest_nz "$res" "sleep-unroll (make)"

    make clean 1>/dev/null 2>&1
    res=$(ls sleep-unroll 2>/dev/null)
    utest_z "$res" "sleep-unroll (make clean)"
    cd ..

    cd babypipe
    rm -f babypipe
    make 1>/dev/null 2>&1
    res=$(ls babypipe)
    utest_nz "$res" "babypipe (make)"

    make clean 1>/dev/null 2>&1
    res=$(ls babypipe 2>/dev/null)
    utest_z "$res" "babypipe (make clean)"
    cd ..

    echo
}


function test_unroll(){
    echo "--- TEST UNROLL ---"

    cd unroll    

    cmd="gcc -g -Wall sleep-unroll.c -o sleep-unroll > /dev/null 2>&1" 
    res=$(eval $cmd)
    utest_z "$res" "compiles without warnings or errors ($res)"


    cmd="{ time ./sleep-unroll \"sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "\"sleep 1\" runs for 1 second ($cmd)"

    cmd="{ time ./sleep-unroll \"sleep 1 | sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "\"sleep 1 | sleep 1\" runs for 1 second ($cmd)"

    cmd="{ time ./sleep-unroll \"sleep 1 | sleep 1 | sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "\"sleep 1 | sleep 1 | sleep 1\" runs for 1 second ($cmd)"


    cmd="{ time ./sleep-unroll \"sleep 1 | sleep 2 | sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="2"
    utest "$res" "$expect" "\"sleep 1 | sleep 2 | sleep 1\" runs for 2 second ($cmd)"


    cmd="{ time ./sleep-unroll \"sleep 0 | sleep 2 | sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="2"
    utest "$res" "$expect" "\"sleep 0 | sleep 2 | sleep 1\" runs for 2 second ($cmd)"

    cmd="{ ./sleep-unroll \"sleep 2\" & }; pid=\$!; sleep 1; [ \"\$(ps --ppid \$pid -o pid | tail -1)\" == \"\$(ps --ppid \$pid -o pgid | tail -1)\" ] ; echo \$?"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "child in own group ($cmd)"

    cmd="{ ./sleep-unroll \"sleep 2 | sleep 2 | sleep 2 | sleep 2\" & }; pid=\$!; sleep 1; [ \"\$(ps --ppid \$pid -o pid | tail -4 | head -1)\" == \"\$(ps --ppid \$pid -o pgid | tail -4 | uniq)\" ] ; echo \$?"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "all children in same group, with 1st child as leader ($cmd)"

    cmd="./sleep-unroll \"head -c 20 /dev/zero\" | wc -c "
    res=$(eval $cmd)
    expect="20"
    utest "$res" "$expect" "executes normal commands ($cmd)"


    cd ..
    echo
}

function test_babypipe(){
    echo "--- TEST BABYPIPE ---"
    echo " (note: if it hangs, did you rememebr to widow?)"
    echo
    
    cd babypipe


    cmd="make clean > /dev/null; make 1 > /dev/null; ./babypipe"
    expect="32"
    res=$(eval $cmd)
    utest "$res" "$expect" "make 1 ($cmd)"

    cmd="make clean > /dev/null; make 2 > /dev/null; ./babypipe"
    expect="87"
    res=$(eval $cmd)
    utest "$res" "$expect" "make 2 ($cmd)"



    cmd="make clean > /dev/null; make 3 > /dev/null; cat sample-db.csv | ./babypipe"
    expect="87"
    res=$(eval $cmd)
    utest "$res" "$expect" "make 3 ($cmd)"
    
    cmd="make clean > /dev/null; make 4 > /dev/null; ./babypipe"
    expect=$(cat <<EOF
Nan,Koppinger,Shimotani, Grace T,88827 Frankford Ave,Greensboro,Guilford,NC,27401,336-370-5333,336-564-1492,nan@koppinger.com,http://www.shimotanigracet.com
Izetta,Dewar,Lisatoni, Jean Esq,2 W Scyene Rd #3,Baltimore,Baltimore City,MD,21217,410-473-1708,410-522-7621,idewar@dewar.com,http://www.lisatonijeanesq.com
Sharen,Bourbon,Mccaleb, John A Esq,62 W Austin St,Syosset,Nassau,NY,11791,516-816-1541,516-749-3188,sbourbon@yahoo.com,http://www.mccalebjohnaesq.com
Roslyn,Chavous,Mcrae, James L,63517 Dupont St,Jackson,Hinds,MS,39211,601-234-9632,601-973-5754,roslyn.chavous@chavous.org,http://www.mcraejamesl.com
Rasheeda,Sayaphon,Kummerer, J Michael Esq,251 Park Ave #979,Saratoga,Santa Clara,CA,95070,408-805-4309,408-997-7490,rasheeda@aol.com,http://www.kummererjmichaelesq.com
Alpha,Palaia,Stoffer, James M Jr,43496 Commercial Dr #29,Cherry Hill,Camden,NJ,08003,856-312-2629,856-513-7024,alpha@yahoo.com,http://www.stofferjamesmjr.com
Janey,Gabisi,Dobscha, Stephen F Esq,40 Cambridge Ave,Madison,Dane,WI,53715,608-967-7194,608-586-6912,jgabisi@hotmail.com,http://www.dobschastephenfesq.com
Gail,Similton,Johnson, Wes Esq,62 Monroe St,Thousand Palms,Riverside,CA,92276,760-616-5388,760-493-9208,gail_similton@similton.com,http://www.johnsonwesesq.com
Carlee,Boulter,Tippett, Troy M Ii,8284 Hart St,Abilene,Dickinson,KS,67410,785-347-1805,785-253-7049,carlee.boulter@hotmail.com,http://www.tippetttroymii.com
Jovita,Oles,Pagano, Philip G Esq,8 S Haven St,Daytona Beach,Volusia,FL,32114,386-248-4118,386-208-6976,joles@gmail.com,http://www.paganophilipgesq.com
EOF
	  )
    res=$(eval $cmd)
    utest "$res" "$expect" "make 4 ($cmd)"


    cmd="make clean > /dev/null; make 5 > /dev/null; ./babypipe"
    expect=$(cat <<EOF
James,Butt,Benton, John B Jr,6649 N Blue Gum St,New Orleans,Orleans,LA,70116,504-621-8927,504-845-1427,jbutt@gmail.com,http://www.bentonjohnbjr.com
Josephine,Darakjy,Chanay, Jeffrey A Esq,4 B Blue Ridge Blvd,Brighton,Livingston,MI,48116,810-292-9388,810-374-9840,josephine_darakjy@darakjy.org,http://www.chanayjeffreyaesq.com
Art,Venere,Chemel, James L Cpa,8 W Cerritos Ave #54,Bridgeport,Gloucester,NJ,08014,856-636-8749,856-264-4130,art@venere.org,http://www.chemeljameslcpa.com
Simona,Morasca,Chapman, Ross E Esq,3 Mcauley Dr,Ashland,Ashland,OH,44805,419-503-2484,419-800-6759,simona@morasca.com,http://www.chapmanrosseesq.com
Kris,Marrier,King, Christopher A Esq,228 Runamuck Pl #2808,Baltimore,Baltimore City,MD,21224,410-655-8723,410-804-4694,kris@gmail.com,http://www.kingchristopheraesq.com
Minna,Amigon,Dorl, James J Esq,2371 Jerrold Ave,Kulpsville,Montgomery,PA,19443,215-874-1229,215-422-8694,minna_amigon@yahoo.com,http://www.dorljamesjesq.com
Cammy,Albares,Rousseaux, Michael Esq,56 E Morehead St,Laredo,Webb,TX,78045,956-537-6195,956-841-7216,calbares@gmail.com,http://www.rousseauxmichaelesq.com
Meaghan,Garufi,Bolton, Wilbur Esq,69734 E Carrillo St,Mc Minnville,Warren,TN,37110,931-313-9635,931-235-7959,meaghan@hotmail.com,http://www.boltonwilburesq.com
Willard,Kolmetz,Ingalls, Donald R Esq,618 W Yakima Ave,Irving,Dallas,TX,75062,972-303-9197,972-896-4882,willard@hotmail.com,http://www.ingallsdonaldresq.com
Maryann,Royster,Franklin, Peter L Esq,74 S Westgate St,Albany,Albany,NY,12204,518-966-7987,518-448-8982,mroyster@royster.com,http://www.franklinpeterlesq.com
EOF
	  )
    res=$(eval $cmd)
    utest "$res" "$expect" "make 5 ($cmd)"
    

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

test_makefile
test_unroll
test_babypipe


