#! /bin/sh

echo "enter a num: "
read x

if [ $((x % 3)) -eq 0 ]
then
	echo "yes"
else
	echo "no"
fi
