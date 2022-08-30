#!/bin/bash -xv

let x=1;

let sum=0;

while [ $x -le 10 ];
do
    if [ $x -eq 5 -o $x -eq 7 ]
    then
        let x=$(($x+2));
        continue;
    fi

    let sum=$(($sum+$x));
    let x=$(($x+2));
done
echo "$sum";