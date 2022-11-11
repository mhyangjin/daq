#!/bin/bash

cd daq_ws/ && source devel/setup.bash

roscore &
sleep 3

if [ -n "$1" ]
then
    python3 src/data_converter/src/jiat_data_converter.py $1
else
    echo " Please enter a directory name what you want to convert."
fi

echo " "
roscore_pid=$(ps -ef | grep roscore* | awk '{ if($8 != "grep") print $2}')
rosmaster_pid=$(ps -ef | grep rosmaster* | awk '{ if($8 != "grep") print $2}')
if [ -n "${roscore_pid}" ] || [ -n "${rosmaster_pid}" ]; then
    kill -9 ${roscore_pid} ${rosmaster_pid}
fi

wait