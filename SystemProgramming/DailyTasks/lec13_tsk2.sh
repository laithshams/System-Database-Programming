#!/bin/bash

let x=1;
while [ $x -le 2 ];
do
    echo "enter number";
    read n;
    let n=$(($n%2));
    if [ $n -eq 0 ];
    then
        echo "even";
    fi
    let x=$(($x+1));
done