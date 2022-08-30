#! /bin/sh

if [ $# -eq 2 ] && [ "$1" = "-b" ] && [ -f billItems.csv ]
then
    grep -woP "(?<=^$2 ).*" billItems.csv > item.csv
elif [ $# -eq 2 ] && [ ! "$1" = "-b" ] && [ -f $2 ]
then
    grep -nw "^$1" $2 | cut -f1 -d: | xargs echo -n > item.csv
    [ -s item.csv ] && echo -n " " >> item.csv
    grep -w "^$1" $2 >> item.csv
fi

if [ ! -s item.csv ] || [ $# -eq 0 ]
then
    rm -rf item.csv
fi
