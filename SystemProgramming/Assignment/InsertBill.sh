#! /bin/sh

#store bill: $0 total_price

cd ~/htu/SystemProgramming/Assignment

if [ ! -f bills.csv ]
then
    touch bills.csv
fi

id=$(wc -l < bills.csv)
id=$(($id+1))
if [ -s billItem.csv ]
then
    echo "$id $1" >> bills.csv
    ./InsertItem.sh $id
else
    echo "can't add bill with no items"
fi