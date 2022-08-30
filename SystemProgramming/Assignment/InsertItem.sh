#! /bin/sh

#insert item in items: $0 barcode name price quantity items.csv
#take items customer want to buy: $0 barcode name price quantity billItem.csv
#insert items customer into bill: $0 id

cd ~/htu/SystemProgramming/Assignment

if [ $# -eq 5 ]
then
    echo "$1 $2 $3 $4" >> $5
elif [ $# -eq 1 ]
then
    while read barcode name price quantity
    do
        echo "$1 $barcode $name $price $quantity" >> billItems.csv
    done < billItem.csv
    rm -rf billItem.csv
fi