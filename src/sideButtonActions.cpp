//======================================================================*/
//   Create Date: 2022/11/6
//   ClassName  : SideButtionActions
//   Author     : mhjin julu1@naver.com
//   Class Def  : side button을 클릭했을 때 수행할 동작들
//======================================================================*/
#include "sideButtonActions.h"
#include "CameraViewer.h"
#include "TopicsViewer.h"
#include "TopicSubscribers.h"
#include "CanSubscribers.h"
#include <QFileDialog>

#include <std_msgs/String.h>
#include <ros/ros.h>
#include <ros/network.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <daq/Radar.h>
#include <daq/Car.h>
#include <daq/Can.h>

 SideButtonActions::SideButtonActions(Ui::DaqMain *_ui)
 :ui(_ui){
    ROS_DEBUG("SideButtonActions::SideButtonActions");
    //미리 선언된 rivs config file로부터  display
    createRvizViewers();
    ROS_DEBUG("SideButtonActions::SideButtonActions-createRvizViewers");
    //topic을 읽어서 창에 string으로 display
    createTopicSubViewers();
    ROS_DEBUG("SideButtonActions::SideButtonActions-createTopicSubViewers");
 }
SideButtonActions::~SideButtonActions() {
    for (auto iter=rvizMap.begin(); iter != rvizMap.end(); ++iter) {
        QList<DAQViz*> *daqList=iter.value();
        for (auto list_iter=daqList->begin();list_iter != daqList->end(); ++list_iter) {
            delete *list_iter;
        }
        delete daqList;
    }
    delete spiner;
}

void SideButtonActions::createRvizViewers() {

    QString Dir=config.getRvizConfig();
    //윈도우 생성시 미리 GUI창을 미리 만들어 둔다.
    QList<DAQViz*> *lidar_tmp= new QList<DAQViz*>();
    //RvizViewer (windiow widget, rivze  file 위치, 윈도우 상에 보여줄 title)
    lidar_tmp->append( (DAQViz*) new RvizViewer(ui, Dir + "/ouster.rviz","LiDAR top",4,1));
    QList<DAQViz*> *camera_tmp= new QList<DAQViz*>();
    camera_tmp->append( (DAQViz*) new CameraViewer(ui, Dir + "/cameras.rviz", "Camera", 1,0 ));

    QList<DAQViz*> *l_side_tmp= new QList<DAQViz*>();
    l_side_tmp->append( (DAQViz*) new RvizViewer(ui, Dir + "/left_vel.rviz", "LiDAR left" , 4,0));
    l_side_tmp->append( (DAQViz*) new RvizViewer(ui, Dir + "/right_vel.rviz", "LiDAR right" ,4,2));

    //click event를 받았을 때  display를 hide, show 처리를 위해 map에 넣어둔다.
    rvizMap.insert("lidarTop", lidar_tmp);
    rvizMap.insert("lidarSide", l_side_tmp);
    rvizMap.insert("cameras", camera_tmp);

 }

void SideButtonActions::createTopicSubViewers(){
    //subscriber 개수만큼 ros thread를 생성한다.
    spiner= new ros::MultiThreadedSpinner(5);

    //topic들을 subscribe해 둔다.
    //gps
    TopicSubscribers<sensor_msgs::NavSatFix>* gps_topic= new TopicSubscribers<sensor_msgs::NavSatFix>("/gps/fix", spiner);
    QList<DAQViz*> *gps_tmp= new QList<DAQViz*>();
    //TopicsViewer (windiow widget, topic subscriber, 윈도우 상에 보여줄 title)
    gps_tmp->append( (DAQViz*) new TopicsViewer(ui, (SignalsSlot*)gps_topic, "GPS",6,1));
    //imu
    TopicSubscribers<sensor_msgs::Imu>* imu_topic= new TopicSubscribers<sensor_msgs::Imu>("/gps/imu", spiner);
    //TopicSubscribers<sensor_msgs::Imu>* imu_topic= new TopicSubscribers<sensor_msgs::Imu>("/diagnostic", spiner);
    QList<DAQViz*> *imu_tmp= new QList<DAQViz*>();
    imu_tmp->append( (DAQViz*) new TopicsViewer(ui, (SignalsSlot*)imu_topic, "IMU",6,2));
    //radar
    CanSubscribers* radar_topic= new CanSubscribers("/can/radar", spiner);
    QList<DAQViz*> *radar_tmp= new QList<DAQViz*>();
    radar_tmp->append( (DAQViz*) new TopicsViewer(ui,(SignalsSlot*)radar_topic,"Radar",6,3));
    //car
    CanSubscribers* car_topic= new CanSubscribers("/can/car", spiner);
    QList<DAQViz*> *car_tmp= new QList<DAQViz*>();
    car_tmp->append( (DAQViz*) new TopicsViewer(ui,(SignalsSlot*)car_topic,"Car Info",6,0 ));

    //click event를 받았을 때  display를 hide, show 처리를 위해 map에 넣어둔다.
    rvizMap.insert("gps", gps_tmp);
    rvizMap.insert("imu", imu_tmp);
    rvizMap.insert("radar", radar_tmp);
    rvizMap.insert("car", car_tmp);
}

bool SideButtonActions::sensorStart() {
    rosRunner.startRosNode();
    return true;
}
void SideButtonActions::sensorStop() {
    rosRunner.stopRosNode();
    
}

bool SideButtonActions::replayStart(QString file) {
    recordPlayer.startReplay(file);
    return true;
}
void SideButtonActions::replayStop() {
    recordPlayer.stopReplay();
}


QString SideButtonActions::recordStart(QString dir){
    QString save_to=recordStarter.startRecord(dir);
    return save_to;
}
void SideButtonActions::recordStop(){
   recordStarter.stopRecord();

}