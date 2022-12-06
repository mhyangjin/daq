#!/bin/bash
source /home/jiat/daq_ws/devel/setup.bash
LOGDIR=./LOG
OUSTER_LOG=$LOGDIR/ouster.log 
VELODYNE_LOG=$LOGDIR/velodyne_pointcloud.log 
SOLATI_LOG=$LOGDIR/solati.log 
NOVATEL_LOG=$LOGDIR/novatel_oem7_driver.log 
USB_CAM_LOG=$LOGDIR/usb_cam.log 
JIAT_LOG=$LOGDIR/jiat_diagnostic.log 

function logCheck() {
    if [ ! -d $LOGDIR ]; then
        echo "$LOGDIR is not exist"
        mkdir $LOGDIR
    fi

    if [ ! -f $OUSTER_LOG ]; then
        touch $OUSTER_LOG
    fi

    if [ ! -f $VELODYNE_LOG ]; then
        touch $VELODYNE_LOG
    fi

    if [ ! -f $SOLATI_LOG ]; then
        touch $SOLATI_LOG
    fi

    if [ ! -f $NOVATEL_LOG ]; then
        touch $NOVATEL_LOG
    fi

    if [ ! -f $JIAT_LOG ]; then
        touch $JIAT_LOG
    fi

    if [ ! -f $USB_CAM_LOG ]; then
        touch $USB_CAM_LOG
    fi

    if [ ! -f $JIAT_LOG ]; then
        touch $JIAT_LOG
    fi
}

function runnodes() {
    echo "[`date`]ouster_ros start...." >> $OUSTER_LOG;
    roslaunch ouster_ros 64ch.launch >> $OUSTER_LOG &

    echo "[`date`]ouster_ros start...." >> $VELODYNE_LOG;
    roslaunch velodyne_pointcloud 16ch.launch >> $VELODYNE_LOG &
    
    echo "[`date`]ouster_ros start...." >> $SOLATI_LOG;
    rosrun solati solati_decode >> $SOLATI_LOG &
    
    echo "[`date`]ouster_ros start...." >> $NOVATEL_LOG;
    roslaunch novatel_oem7_driver oem7_net.launch >> $NOVATEL_LOG &
    
    echo "[`date`]ouster_ros start...." >> $USB_CAM_LOG;
    roslaunch usb_cam cameras.launch  >> $USB_CAM_LOG &
    
    echo "[`date`]ouster_ros start...." >> $JIAT_LOG;
    python3 /home/jiat/daq_ws/src/diagnostic/scripts/jiat_diagnostic.py >> $JIAT_LOG &
}


function killnodes() {
    echo "[`date`]ouster_ros stop...." >> $OUSTER_LOG;
    pkill ouster_ros

    echo "[`date`]ouster_ros stop...." >> $VELODYNE_LOG;
    pkill velodyne_pointcloud
    
    echo "[`date`]ouster_ros stop...." >> $SOLATI_LOG;
    pkill solati
    
    echo "[`date`]ouster_ros stop...." >> $NOVATEL_LOG;
    pkill novatel_oem7_driver
    
    echo "[`date`]ouster_ros stop...." >> $USB_CAM_LOG;
    pkill usb_cam
    
    echo "[`date`]ouster_ros stop...." >> $JIAT_LOG;
    pkill jiat_diagnostic
}

function main() {
    logCheck;
    echo "RosNode will be $1"
    if [ $1 == "run" ]; then 
        runnodes;
    fi
    if [ $1 == "kill" ]; then 
        killnodes;
    fi
}

main $*;