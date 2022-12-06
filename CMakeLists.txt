cmake_minimum_required(VERSION 3.5)
project(daq)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
set(CMAKE_PREFIX_PATH "/opt/ros/noetic/lib;/opt/ros/noetic;${CMAKE_MODULE_PATH};/usr/lib/aarch64-linux-gnu/qt5;/usr/lib/aarch64-linux-gnu;/usr/include")

find_package(
  catkin 
  REQUIRED COMPONENTS
  roscpp
  rviz
  message_generation
  std_msgs
  sensor_msgs
  rosbag
)

add_message_files(
  FILES 
  Sensor_status.msg 
  Car.msg 
  Radar.msg 
  Track.msg 
  Sim.msg )

generate_messages(
  DEPENDENCIES 
  std_msgs)

#catkin_install_python(
 # PROGRAMS
 # scripts/jiat_diagnostic.py
 # DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

####################################################
# QT Environment
###################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(RVIZ_HAVE_YAMLCPP_05 ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
#QT5_WARP_UI(QT_FORMS_HPP ${QT_FORMS})

include_directories(
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

add_definitions( -std=c++11 -fPIC)


##############################################################################
# Sources
##############################################################################
set( QT_SOURCES
  src/main.cpp
  src/defines.h
  src/init.h
  src/daqmain.h
  src/daqmain.cpp
  src/RosNode.h
  src/RosNode.cpp
  src/RecordPlayer.h
  src/RecordPlayer.cpp
  src/RosRunner.h
  src/RosRunner.cpp
  src/TopicSubscribers.h
  src/TopicSubscribers.cpp
  src/RvizViewer.h
  src/RvizViewer.cpp
  src/YmlLoader.h
  src/YmlLoader.cpp
  src/DaqVisualizationManager.h
  src/DaqVisualizationManager.cpp
  src/CameraViewer.h
  src/CameraViewer.cpp
  src/RecordStarter.h
  src/RecordStarter.cpp
  src/TopicsViewer.h
  src/TopicsViewer.cpp
  src/sideButtonActions.h
  src/sideButtonActions.cpp
  src/AcquisitionStatus.h
  src/AcquisitionStatus.cpp
  src/DAQViz.h
  src/DAQViz.cpp
  src/daqmain.ui
  src/images.qrc
  src/DialogConfig.ui
  src/DialogConfig.h
  src/DialogConfig.cpp
  src/ConfigLoader.h
  src/ConfigLoader.cpp
)

#set (CONFIG scripts/config.yml)
## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)
##############################################################################
# DAQ run scrpit. config parameters
##############################################################################
#catkin_install_python( PROGRAMS
#scrpits/runDAQ.py
#)

#DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
##############################################################################
# Binaries
##############################################################################
add_executable(${PROJECT_NAME} ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP} ${FILES} )

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  libyaml-cpp.so
)
install(TARGETS ${PROJECT_NAME} 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  )