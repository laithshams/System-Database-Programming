#! /bin/sh

cd ~/htu/SystemProgramming/Assignment

while read barcode name price bquantity
do
    ./WhereItem.sh $barcode items.csv
    read line barcode name price quantity < item.csv
    nquantity=$(($quantity - $bquantity))
    sed -i "${line}s/${quantity}$/${nquantity}/" items.csv
    if [ $nquantity -eq 0 ]
    then
        sed -i "${line}d" items.csv
    fi
done < billItem.csv

rm -rf item.csv

if [ ! -s items.csv ]
then
    rm -rf items.csv
fi
