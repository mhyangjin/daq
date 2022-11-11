#!/bin/bash

if [ -z  $1 ]
then
    echo ""
    echo " Please enter a directory name what you want to save."
    echo ""
    echo "---------- example ---------"
    echo "| make.sh <directory name> |"
    echo "----------------------------"
    echo ""
elif [ -d /home/jiat/Data/$1 ]
then
    echo ""
    echo " Error: Directory that already exists."
    echo ""
else
    mkdir -p /home/jiat/Data/$1
fi