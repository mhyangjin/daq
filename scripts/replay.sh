#!/bin/bash

if [ -z $1 ]
then
    echo ""
    echo " Please enter a directory name."
    echo ""
    echo "----------- example ----------"
    echo "| replay.sh <directory name> |"
    echo "------------------------------"
    echo ""
elif [ -z $2 ]
then
    echo ""
    echo " Please enter a file name."
    echo ""
    echo "------------- example ------------"
    echo "| replay.sh $1 <file name> |"
    echo "----------------------------------"
    echo ""
else
    roscore &
    sleep 2

    rosbag play -l /home/jiat/Data/$1/$2.bag
fi