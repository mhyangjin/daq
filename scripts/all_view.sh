#!/bin/bash

source /home/jiat/daq_ws/devel/setup.bash

# View Ouster LiDAR
gnome-terminal --title=ouster -- rviz -d /home/jiat/config/ouster.rviz &
sleep 2

# View right Velodyne LiDAR
gnome-terminal --title=right_vel -- rviz -d /home/jiat/config/right_vel.rviz &
sleep 2

# View left Velodyne LiDAR
gnome-terminal --title=left_vel -- rviz -d /home/jiat/config/left_vel.rviz &
sleep 2

# View All Cameras
gnome-terminal --title=Cameras -- rviz -d /home/jiat/config/cameras.rviz &
sleep 3

# View GPS
gnome-terminal --geometry 40x19+450+0 --title=GPS -- rostopic echo /gps/fix &
sleep 1

# View IMU
gnome-terminal --geometry 40x30+450+0 --title=IMU -- rostopic echo /gps/imu &
sleep 1

# View Radar
gnome-terminal --geometry 40x50+450+0 --title=Radar -- rostopic echo /can/radar &
sleep 1

# View Car_info
gnome-terminal --geometry 40x8+450+0 --title=Car_info -- rostopic echo /can/car &
sleep 1