#!/bin/bash

#echo "4111111111111111"
#Mike Hanling
#Discussed with Chris Daves
rand_card_num=$(./rand16)
status=2
while [ $status -eq 2 ]
do 
  output=$(./creditcardcheck $rand_card_num)
  status=$?
  if [ $status -eq 0 ] 
  then 
    echo $rand_card_num 
    exit 0
  fi 
  let rand_card_num=$rand_card_num+1
done
