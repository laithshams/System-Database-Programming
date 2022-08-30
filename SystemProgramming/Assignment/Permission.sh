#! /bin/sh

if [ $# -eq 1 ]
then
    chmod $1$2rwx *
    chmod go-x Permission.sh
else
    ls -l *.sh
fi
