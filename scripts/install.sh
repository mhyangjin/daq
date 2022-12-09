#!/bin/bash
if [ $ROS_ENV == "TEST" ]; then
    CATKIN_HOME=/home/mhjin/project/catkin_ws
else
    CATKIN_HOME=/home/jiat/daq_ws
fi

ROS_HOME=/opt/ros/noetic
EXEC_PATH=
######catkin_home/install 을 사용한다면 
#INSTALL_DIR=install
######catkin_home/devel 을 사용한다면
INSTALL_DIR=devel
VERSION=

function copy_dirs() {
    if [ ${INSTALL_DIR} == 'devel' ]; then
        EXEC_PATH=${CATKIN_HOME}/${INSTALL_DIR}/lib/daq
        if [ ! -d ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/rvizs ]; then
            echo ".....copy rvizs to ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/rvizs "
            mkdir ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/rvizs
            cp ${CATKIN_HOME}/src/daq/src/rvizs/* ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/rvizs/
        fi

        if [ ! -d ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/scripts ]; then
            echo ".....copy scripts to ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/scripts "
            mkdir ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/scripts
            cp ${CATKIN_HOME}/src/daq/scripts/* ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/scripts/
        fi

        if [ ! -f ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/daq_icon.png ]; then
            echo ".....copy jiat logo to ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq "
            cp ${CATKIN_HOME}/src/daq/src/images/daq_icon.png ${CATKIN_HOME}/${INSTALL_DIR}/lib/daq/
        fi
    fi

    if [ ${INSTALL_DIR} == 'install' ]; then
        EXEC_PATH=${CATKIN_HOME}/${INSTALL_DIR}/bin
        if [ ! -d ${CATKIN_HOME}/${INSTALL_DIR}/bin/rvizs ]; then
            echo ".....copy rvizs to b${CATKIN_HOME}/${INSTALL_DIR}/bin/rvizs "
            mkdir ${CATKIN_HOME}/${INSTALL_DIR}/bin/rvizs
            cp ${CATKIN_HOME}/src/daq/src/rvizs/* ${CATKIN_HOME}/${INSTALL_DIR}/bin/rvizs/
        fi

        if [ ! -d ${CATKIN_HOME}/${INSTALL_DIR}/bin/scripts ]; then
            echo ".....copy scripts to ${CATKIN_HOME}/${INSTALL_DIR}/bin/scripts"
            mkdir ${CATKIN_HOME}/${INSTALL_DIR}/bin/scripts
            cp ${CATKIN_HOME}/src/daq/scripts/* ${CATKIN_HOME}/${INSTALL_DIR}/bin/scripts/
        fi

        if [ ! -f ${CATKIN_HOME}/${INSTALL_DIR}/bin/daq_icon.png ]; then
            echo ".....copy jiat logo to ${CATKIN_HOME}/${INSTALL_DIR}/bin "
            cp ${CATKIN_HOME}/src/daq/src/images/daq_icon.png ${CATKIN_HOME}/${INSTALL_DIR}/bin/
        fi
    fi
}
function makeDaqExe() {
    if [ ! -f ${EXEC_PATH}/daq.sh ]; then 
        echo "#!/bin/bash" >> ${EXEC_PATH}/daq.sh
        echo "source ${ROS_HOME}/setup.bash" >> ${EXEC_PATH}/daq.sh
        echo "source ${CATKIN_HOME}/${INSTALL_DIR}/setup.bash" >> ${EXEC_PATH}/daq.sh
        echo "${EXEC_PATH}/daq"  >> ${EXEC_PATH}/daq.sh
        chmod +x ${EXEC_PATH}/daq.sh
    fi
}

function makeIcons() {
    VERSION=`head -n 1 ../CHANGELOG.md | awk -F ' ' '{print $3}'`
	if [ ! -f $HOME/Desktop/daq.desktop ]; then
		echo "#!/usr/bin/env xdg-open" >> $HOME/Desktop/daq.desktop
		echo "[Desktop Entry]" >> $HOME/Desktop/daq.desktop
		echo "Version=${VERSION}" >> $HOME/Desktop/daq.desktop
		echo "Type=Application" >> $HOME/Desktop/daq.desktop
		echo "Terminal=true" >> $HOME/Desktop/daq.desktop
		echo "Exec=${EXEC_PATH}/daq.sh" >> $HOME/Desktop/daq.desktop
        echo "Path=${EXEC_PATH}/" >> $HOME/Desktop/daq.desktop
        echo "Name=Daq" >> $HOME/Desktop/daq.desktop
        echo "Comment=Daq" >> $HOME/Desktop/daq.desktop
        echo "Icon=${EXEC_PATH}/daq_icon.png" >> $HOME/Desktop/daq.desktop

        chmod +x $HOME/Desktop/daq.desktop
	fi
    
}

function main() {
    echo "====================>> start install.sh"
    copy_dirs;
    makeDaqExe;
    makeIcons;
    echo "====================>> end istall.sh"
}

main $*;
