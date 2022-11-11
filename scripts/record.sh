#!/bin/bash

if [ -z $1 ]
then
    echo ""
    echo " Please enter a directory name what you want to save."
    echo ""
    echo "----------- example ----------"
    echo "| record.sh <directory name> |"
    echo "------------------------------"
    echo ""
elif [ -z $2 ]
then
    echo ""
    echo " Please enter a file name."
    echo ""
    echo "------------- example ------------"
    echo "| record.sh $1 <file name> |"
    echo "----------------------------------"
    echo "* Enter \"date\" if you want the file name at the current time."
    echo ""
elif [ -e /home/jiat/Data/$1/$2.bag ]
then
    echo ""
    echo " Error: File that already exists."
    echo ""
elif [ $2 = "date" ]
then
    date=$(date '+%Y-%m-%d-%H-%M-%S')
    # rosbag record -b 0 -O /home/jiat/Data/$1/${date}.bag /rosout /rosout_agg
    # rosbag record -b 0 -O /home/jiat/Data/$1/${date}.bag /front_camera/image_raw /right_camera/image_raw /left_camera/image_raw /os_cloud_node/points /right_velodyne/velodyne_points /left_velodyne/velodyne_points /gps/fix /gps/imu /can /rosout /rosout_agg
    rosbag record -b 0 --duration=10 -O /home/jiat/Data/$1/${date}.bag /front_camera/image_raw /right_camera/image_raw /left_camera/image_raw /os_cloud_node/points /right_velodyne/velodyne_points /left_velodyne/velodyne_points /gps/fix /gps/imu /can /rosout /rosout_agg
else
    # rosbag record -b 0 -O /home/jiat/Data/$1/$2.bag /rosout /rosout_agg
    # rosbag record -b 0 -O /home/jiat/Data/$1/$2.bag /front_camera/image_raw /right_camera/image_raw /left_camera/image_raw /os_cloud_node/points /right_velodyne/velodyne_points /left_velodyne/velodyne_points /gps/fix /gps/imu /can /rosout /rosout_agg
    rosbag record -b 0 --duration=10 -O /home/jiat/Data/$1/$2.bag /front_camera/image_raw /right_camera/image_raw /left_camera/image_raw /os_cloud_node/points /right_velodyne/velodyne_points /left_velodyne/velodyne_points /gps/fix /gps/imu /can /rosout /rosout_agg
fi  