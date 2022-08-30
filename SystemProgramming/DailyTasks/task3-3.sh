#! /bin/sh

echo "enter your mark: "
read x

if [ $x -ge 90 -a $x -le 100 ]
then
    echo " your mark is A"

elif [ $x -ge 80 -a $x -le 89 ]
then
    echo " your mark is B"

elif [ $x -ge 70 -a $x -le 79 ]
then
    echo " your mark is C"

elif [ $x -ge 60 -a $x -le 69 ]
then
    echo " your mark is D"

elif [ $x -ge 50 -a $x -le 59 ]
then
    echo " your mark is E"

elif [ $x -ge 0 -a $x -le 49 ]
then
    echo " your mark is F"

fi