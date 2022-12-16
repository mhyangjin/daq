#!/bin/bash
if [ -z $ROS_ENV ]; then
    ROS_ENV="JIAT"
fi

if [ $ROS_ENV == "TEST" ]; then
    source /home/mhjin/project/catkin_ws/devel/setup.bash
else
    source /home/jiat/daq_ws/devel/setup.bash
fi

LOGDIR=./LOG
OUSTER_LOG=$LOGDIR/ouster.log 
VELODYNE_LOG=$LOGDIR/velodyne_pointcloud.log 
SOLATI_LOG=$LOGDIR/solati.log 
NOVATEL_LOG=$LOGDIR/novatel_oem7_driver.log 
USB_CAM_LOG=$LOGDIR/usb_cam.log 
JIAT_LOG=$LOGDIR/jiat_diagnostic.log 
LOG_MAX_SIZE=1000000        # LOG size 1M

function logCheck() {
    if [ ! -d $LOGDIR ]; then
        echo "$LOGDIR is not exist"
        mkdir $LOGDIR
    fi

    if [ ! -f $OUSTER_LOG ]; then
        touch $OUSTER_LOG
    else
        file_size=`wc -c < $OUSTER_LOG`
        if [ $file_size -ge $LOG_MAX_SIZE ]; then
            rm $OUSTER_LOG
            touch $OUSTER_LOG
        fi
    fi

    if [ ! -f $VELODYNE_LOG ]; then
        touch $VELODYNE_LOG
    else
        file_size=`wc -c < $VELODYNE_LOG`
        if [ $file_size -ge $LOG_MAX_SIZE ]; then
            rm $VELODYNE_LOG
            touch $VELODYNE_LOG
        fi
    fi

    if [ ! -f $SOLATI_LOG ]; then
        touch $SOLATI_LOG
    else
        file_size=`wc -c < $SOLATI_LOG`
        if [ $file_size -ge $LOG_MAX_SIZE ]; then
            rm $SOLATI_LOG
            touch $SOLATI_LOG
        fi
    fi

    if [ ! -f $NOVATEL_LOG ]; then
        touch $NOVATEL_LOG
    else
        file_size=`wc -c < $NOVATEL_LOG`
        if [ $file_size -ge $LOG_MAX_SIZE ]; then
            rm $NOVATEL_LOG
            touch $NOVATEL_LOG
        fi
    fi

    if [ ! -f $JIAT_LOG ]; then
        touch $JIAT_LOG
    else
        file_size=`wc -c < $JIAT_LOG`
        if [ $file_size -ge $LOG_MAX_SIZE ]; then
            rm $JIAT_LOG
            touch $JIAT_LOG
        fi
    fi

    if [ ! -f $USB_CAM_LOG ]; then
        touch $USB_CAM_LOG
    else
        file_size=`wc -c < $USB_CAM_LOG`
        if [ $file_size -ge $LOG_MAX_SIZE ]; then
            rm $USB_CAM_LOG
            touch $USB_CAM_LOG
        fi
    fi

    if [ ! -f $JIAT_LOG ]; then
        touch $JIAT_LOG
    else
        file_size=`wc -c < $JIAT_LOG`
        if [ $file_size -ge $LOG_MAX_SIZE ]; then
            rm $JIAT_LOG
            touch $JIAT_LOG
        fi
    fi
}

function runnodes() {
    echo "[`date`]ouster_ros start...." >> $OUSTER_LOG;
    roslaunch ouster_ros 64ch.launch >> $OUSTER_LOG &

    echo "[`date`]velodyne_pointcloud start...." >> $VELODYNE_LOG;
    roslaunch velodyne_pointcloud 16ch.launch >> $VELODYNE_LOG &
    
    echo "[`date`]solati_decode start...." >> $SOLATI_LOG;
    rosrun solati solati_decode >> $SOLATI_LOG &
    
    echo "[`date`]novatel_oem7_driver start...." >> $NOVATEL_LOG;
    roslaunch novatel_oem7_driver oem7_net.launch >> $NOVATEL_LOG &
    
    echo "[`date`]usb_cam start...." >> $USB_CAM_LOG;
    roslaunch usb_cam cameras.launch  >> $USB_CAM_LOG &
    
    echo "[`date`]diagnostic_talker start...." >> $JIAT_LOG;
    python3 /home/jiat/daq_ws/src/diagnostic/script/jiat_diagnostic.py >> $JIAT_LOG &
}

function killnodes() {
    pkill roslaunch
    pkill rosrun
    pkill rosbag
    
    echo "[`date`]jiat_diagnostic stop...." >> $JIAT_LOG;
    pid=`ps -ef | grep jiat_diagnostic | grep -v 'grep' | awk '{print $2}'`
    kill -9 $pid
}



function runnodes_test() {
    echo "[`date`]car start...." ;
    python3 /home/mhjin/project/catkin_ws/devel/lib/daq/car_sender.py &

    echo "[`date`]gps_sender start...." ;
    python3 /home/mhjin/project/catkin_ws/devel/lib/daq/gps_sender.py  &

    echo "[`date`]imu_sender start...." ;
    python3 /home/mhjin/project/catkin_ws/devel/lib/daq/imu_sender.py  &

    echo "[`date`]radar_sender start...." ;
    python3 /home/mhjin/project/catkin_ws/devel/lib/daq/radar_sender.py  &

    echo "[`date`]diagnostic_talker start...." ;
    python3 /home/mhjin/project/catkin_ws/devel/lib/daq/diagnostic_talker.py &
}

function killnodes_test() {
    echo "[`date`]car_sender stop...." ;
    pid=`ps -ef | grep car_sender | grep -v 'grep' | awk '{print $2}'`
    if [ ! -z $pid ]; then 
        kill -9 $pid
    fi

    echo "[`date`]gps_sender stop....";
    pid=`ps -ef | grep gps_sender | grep -v 'grep' | awk '{print $2}'`
    if [ ! -z $pid ]; then 
        kill -9 $pid
    fi
    
    echo "[`date`] imu_sender....";
    pid=`ps -ef | grep imu_sender | grep -v 'grep' | awk '{print $2}'`
    if [ ! -z $pid ]; then 
        kill -9 $pid
    fi
    
    echo "[`date`]radar_sender stop...." ;
    pid=`ps -ef | grep radar_sender | grep -v 'grep' | awk '{print $2}'`
    if [ ! -z $pid ]; then 
        kill -9 $pid
    fi
    

    echo "[`date`]diagnostic_talker stop...." ;
    pid=`ps -ef | grep diagnostic_talker | grep -v 'grep' | awk '{print $2}'`
    if [ ! -z $pid ]; then 
        kill -9 $pid
    fi

    echo "[`date`]rosbag stop...." ;
    pids=`ps -ef | grep rosbag | grep -v 'grep' | awk '{print $2}'`
    for pid in $pids
    do
        if [ ! -z $pid ]; then 
            kill -9 $pid
        fi
    done
    

}

function main() {
    echo "$ROS_ENV:RosNode will be $1"
    case "$1" in
        "run")
            if [ $ROS_ENV == "TEST" ]; then
                runnodes_test;
            else
                runnodes;
            fi
            ;;
        "kill")
            if [ $ROS_ENV == "TEST" ]; then
                killnodes_test;
            else
                killnodes;
            fi
            ;;
        "init")
            logCheck;
            ;;
        *)
            return;
    esac
}

main $*;