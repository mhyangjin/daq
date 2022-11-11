#!/bin/bash

if [ -z $1 ]
then
    echo ""
    echo " Please enter a sensor name."
    echo ""
    echo "-------- example --------"
    echo "| view.sh <sensor name> |"
    echo "-------------------------"
    echo ""
    echo "------------------------------- Sensor List ------------------------------"
    echo "| lidar_t | lidar_r | lidar_l | cameras | gps | imu | radar | car | all | "
    echo "--------------------------------------------------------------------------"
    echo ""
elif [ $1 == "lidar_t" ]
then
    rviz -d /home/jiat/config/ouster.rviz
elif [ $1 == "lidar_r" ]
then
    rviz -d /home/jiat/config/right_vel.rviz
elif [ $1 == "lidar_l" ]
then
    rviz -d /home/jiat/config/left_vel.rviz
elif [ $1 == "cameras" ]
then
    rviz -d /home/jiat/config/cameras.rviz
elif [ $1 == "gps" ]
then
    gnome-terminal --geometry 40x19+450+0 --title=GPS -- rostopic echo /gps/fix
elif [ $1 == "imu" ]
then
    gnome-terminal --geometry 40x30+450+0 --title=IMU -- rostopic echo /gps/imu
elif [ $1 == "radar" ]
then
    source /home/jiat/daq_ws/devel/setup.bash
    gnome-terminal --geometry 40x50+450+0 --title=Radar -- rostopic echo /can/radar
elif [ $1 == "car" ]
then
    source /home/jiat/daq_ws/devel/setup.bash
    gnome-terminal --geometry 40x8+450+0 --title=Car_info -- rostopic echo /can/car
elif [ $1 == "all" ]
then
    all_view.sh
else
    echo ""
    echo " Please enter a correct sensor name."
    echo ""
    echo "------------------------------- Sensor List ------------------------------"
    echo "| lidar_t | lidar_r | lidar_l | cameras | gps | imu | radar | car | all | "
    echo "--------------------------------------------------------------------------"
    echo ""
fi