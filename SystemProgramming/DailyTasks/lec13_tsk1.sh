#!/bin/bash

if [ $# -eq 4 ];
then
    for x;
    do
        let x=$(($x*$x));
        echo "$x";
    done
else
    echo "you shoud have four parameters";
fi