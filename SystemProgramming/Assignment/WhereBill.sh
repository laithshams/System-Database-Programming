#! /bin/sh

cd ~/htu/SystemProgramming/Assignment

if [ $# -eq 1 ] && [ -f bills.csv ]
then
    grep -woP "(?<=^$1 ).*" bills.csv > bill.csv
    ./WhereItem.sh -b $1
fi

if [ ! -s bill.csv ] || [ $# -eq 0 ]
then
    ./WhereItem.sh
    rm -rf bill.csv
fi
