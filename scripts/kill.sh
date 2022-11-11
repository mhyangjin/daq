#!/bin/bash

# Kill roscore
if [ -n "$(ps -ef | grep roscore | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep roscore)
    kill -9 $(ps -ef | grep roscore | grep -v 'grep' | awk '{print $2}')
fi

# Kill master
if [ -n "$(ps -ef | grep rosmaster | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep rosmaster | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep rosmaster | grep -v 'grep' | awk '{print $2}')
fi

# Kill roslaunch
if [ -n "$(ps -ef | grep roslaunch | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep roslaunch | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep roslaunch | grep -v 'grep' | awk '{print $2}')
fi

# Kill diagnostic
if [ -n "$(ps -ef | grep diagnostic* | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep diagnostic* | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep diagnostic* | grep -v 'grep' | awk '{print $2}')
fi

# Kill usb_cam
if [ -n "$(ps -ef | grep usb_cam* | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep usb_cam* | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep usb_cam* | grep -v 'grep' | awk '{print $2}')
fi

# Kill undist_cam
if [ -n "$(ps -ef | grep undist* | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep undist* | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep undist* | grep -v 'grep' | awk '{print $2}')
fi

# Kill Ouster os1-64 Gen2
if [ -n "$(ps -ef | grep os_cloud_node | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep os_cloud_node | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep os_cloud_node | grep -v 'grep' | awk '{print $2}')
fi
if [ -n "$(ps -ef | grep os_node | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep os_node | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep os_node | grep -v 'grep' | awk '{print $2}')
fi

# Kill Velodyne VLP-16
if [ -n "$(ps -ef | grep velodyne | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep velodyne | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep velodyne | grep -v 'grep' | awk '{print $2}')
fi
if [ -n "$(ps -ef | grep os_node | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep os_node | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep os_node | grep -v 'grep' | awk '{print $2}')
fi

# Kill NovAtel PwrPak7D-E1
if [ -n "$(ps -ef | grep novatel* | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep novatel* | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep novatel* | grep -v 'grep' | awk '{print $2}')
fi

# Kill CAN
if [ -n "$(ps -ef | grep can_parsing* | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep can_parsing* | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep can_parsing* | grep -v 'grep' | awk '{print $2}')
fi
if [ -n "$(ps -ef | grep socketcan_bridg* | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep socketcan_bridg* | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep socketcan_bridg* | grep -v 'grep' | awk '{print $2}')
fi

# Kill rosout
if [ -n "$(ps -ef | grep rosout | grep -v 'grep' | awk '{print $2}')" ]
then
    echo $(ps -ef | grep rosout | grep -v 'grep' | awk '{print $2}')
    kill -9 $(ps -ef | grep rosout | grep -v 'grep' | awk '{print $2}')
fi

echo ""
echo " ======================================================= "
echo " ==================== Stop Sensors ===================== "
echo " ======================================================= "
echo ""
sleep 2