#! /bin/sh

echo "read 1st: "
read x1

echo "read 2nd: "
read x2

echo "read 3rd: "
read x3

if [ $x1 -ge $x2 -a $x1 -ge $x3 ]
then
	echo "max num is $x1"
elif [ $x2 -ge $x3 ]
then
	echo "max num is $x2"
else
	echo "max num is $x3"
fi
