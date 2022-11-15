#!/bin/bash

echo ""
echo " ======================================================= "
echo " ==================== Start Sensors ==================== "
echo " ======================================================= "
echo ""
#sleep 1

# Set ROS Framework
echo ""
echo " ======================================================= "
echo " ================== Set ROS Framework ================== "
echo " ======================================================= "
echo ""

source /opt/ros/noetic/setup.bash
roscore &
sleep 5

# Set Workspace
echo ""
echo " ======================================================= "
echo " ==================== Set Workspace ==================== "
echo " ======================================================= "
echo ""

source /home/jiat/daq_ws/devel/setup.bash
#sleep 

# Run Ouster OS1-64 Gen2
echo ""
echo " ======================================================= "
echo " =================== Run Ouster LiDAR ================== "
echo " ======================================================= "
echo ""

roslaunch ouster_ros 64ch.launch &
#sleep 15

# Run Velodyne VLP-16s
echo ""
echo " ======================================================= "
echo " ================== Run Velodyne LiDAR ================= "
echo " ======================================================= "
echo ""

roslaunch velodyne_pointcloud 16ch.launch &
#sleep 2

# Run CAN (Radar, Car Information)
echo ""
echo " ======================================================= "
echo " ======================= Run CAN ======================= "
echo " ======================================================= "
echo ""

rosrun solati solati_decode &
#sleep 2

# Run GPS
echo ""
echo " ======================================================= "
echo " ======================= Run GPS ======================= "
echo " ======================================================= "
echo ""

roslaunch novatel_oem7_driver oem7_net.launch &
#sleep 2

# Run Cameras
echo ""
echo " ======================================================= "
echo " ===================== Run Cameras ===================== "
echo " ======================================================= "
echo ""

roslaunch usb_cam cameras.launch &
#sleep 3

# Rus Sensor Diagnostic
echo ""
echo " ======================================================= "
echo " ================= Run Sensor Diagnostic =============== "
echo " ======================================================= "
echo ""

#python3 /home/jiat/daq_ws/src/diagnostic/scripts/jiat_diagnostic.py &
#sleep 1#

# rosrun cam_undistort_pkg undistortion_img.py &
# sleep 1

# Running Sensors
echo ""
echo " ======================================================= "
echo " =================== Running Sensors =================== "
echo " ======================================================= "
echo ""

wait