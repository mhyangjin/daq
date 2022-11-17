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

#include <QFileDialog>

#include <std_msgs/String.h>
#include <ros/ros.h>
#include <ros/network.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <daq/Radar.h>
#include <daq/Car.h>


 SideButtonActions::SideButtonActions(Ui::DaqMain *_ui)
 :ui(_ui){
    //미리 선언된 rivs config file로부터  display
    createRvizViewers();
    //topic을 읽어서 창에 string으로 display
    createTopicSubViewers();
 }
SideButtonActions::~SideButtonActions() {

}

void SideButtonActions::createRvizViewers() {

    //윈도우 생성시 미리 GUI창을 미리 만들어 둔다.
    rvizMap=new QMap<QString, QList<DAQViz*>*>();
    QList<DAQViz*> *lidar_tmp= new QList<DAQViz*>();
    lidar_tmp->append( (DAQViz*) new RvizViewer(ui,"./rvizs/ouster.rviz","liDAR Top"));

    QList<DAQViz*> *camera_tmp= new QList<DAQViz*>();
    camera_tmp->append( (DAQViz*) new CameraViewer(ui,"./rvizs/cameras.rviz", "Camera" ));

    QList<DAQViz*> *l_side_tmp= new QList<DAQViz*>();
    l_side_tmp->append( (DAQViz*) new RvizViewer(ui,"./rvizs/left_vel.rviz", "liDAR Left" ));
    l_side_tmp->append( (DAQViz*) new RvizViewer(ui,"./rvizs/right_vel.rviz", "LiDAR Right" ));

    //click event를 받았을 때  display를 hide, show 처리를 위해 map에 넣어둔다.
    rvizMap->insert("lidarTop", lidar_tmp);
    rvizMap->insert("cameras", camera_tmp);
    rvizMap->insert("lidarSide", l_side_tmp);

 }

void SideButtonActions::createTopicSubViewers(){
    //subscriber 개수만큼 ros thread를 생성한다.
    spiner= new ros::MultiThreadedSpinner(5);

    //topic들을 subscribe해 둔다.
    //gps
    TopicSubscribers<sensor_msgs::NavSatFix>* gps_topic= new TopicSubscribers<sensor_msgs::NavSatFix>("/gps/fix", spiner);
    QList<DAQViz*> *gps_tmp= new QList<DAQViz*>();
    gps_tmp->append( (DAQViz*) new TopicsViewer(ui, (SignalsSlot*)gps_topic, "GPS"));
    //imu
    TopicSubscribers<sensor_msgs::Imu>* imu_topic= new TopicSubscribers<sensor_msgs::Imu>("/gps/imu", spiner);
    QList<DAQViz*> *imu_tmp= new QList<DAQViz*>();
    imu_tmp->append( (DAQViz*) new TopicsViewer(ui, (SignalsSlot*)imu_topic, "IMU"));
    //radar
    TopicSubscribers<daq::Radar>* radar_topic= new TopicSubscribers<daq::Radar>("/can/radar", spiner);
    QList<DAQViz*> *radar_tmp= new QList<DAQViz*>();
    radar_tmp->append( (DAQViz*) new TopicsViewer(ui,(SignalsSlot*)radar_topic,"radar"));
    //car
    TopicSubscribers<daq::Car>* car_topic= new TopicSubscribers<daq::Car>("/can/car", spiner);
    QList<DAQViz*> *car_tmp= new QList<DAQViz*>();
    car_tmp->append( (DAQViz*) new TopicsViewer(ui,(SignalsSlot*)car_topic,"Car" ));

    //click event를 받았을 때  display를 hide, show 처리를 위해 map에 넣어둔다.
    rvizMap->insert("gps", gps_tmp);
    rvizMap->insert("imu", imu_tmp);
    rvizMap->insert("radar", radar_tmp);
    rvizMap->insert("car", car_tmp);


}

bool SideButtonActions::sensorStart() {

    return true;
}
void SideButtonActions::sensorStop() {

}
bool SideButtonActions::replayStart(QString file) {
    return true;
}
void SideButtonActions::replayStop() {

}

void SideButtonActions::allViewClicked(){
    cout << "SideButtonActions::allViewClicked()"<<endl;
    this->allStop("nothing");
    this->allStart("nothing");
}

void SideButtonActions::cameraClicked(){
    this->allStop("cameras");
    cout << "SideButtonActions::cameraClicked()"<<endl;
    CameraViewer* controller=(CameraViewer*)rvizMap->find("cameras").value()->at(0);
    controller->showWindow();
}

void SideButtonActions::carInfoClicked(){
    this->allStop("car");
    cout << "SideButtonActions::carClicked()"<<endl;
    TopicsViewer* controller=(TopicsViewer*)rvizMap->find("car").value()->at(0);
    controller->showWindow();

}
void SideButtonActions::gpsClicked(){
    this->allStop("gps");
    cout << "SideButtonActions::gpsClicked()"<<endl;
    TopicsViewer* controller=(TopicsViewer*)rvizMap->find("gps").value()->at(0);
    controller->showWindow();
}
void SideButtonActions::imuClicked(){
    this->allStop("imu");
    cout << "SideButtonActions::imuClicked()"<<endl;
    TopicsViewer* controller=(TopicsViewer*)rvizMap->find("imu").value()->at(0);
    controller->showWindow();
}
void SideButtonActions::radarClicked(){
    this->allStop("radar");
    cout << "SideButtonActions::radarClicked()"<<endl;
    TopicsViewer* controller=(TopicsViewer*)rvizMap->find("radar").value()->at(0);
    controller->showWindow();
}

void SideButtonActions::lidarSideClicked(){
    this->allStop("lidarSide");
    cout << "SideButtonActions::lidarSideClicked()"<<endl;
    QList<DAQViz*> *dapArray=rvizMap->find("lidarSide").value();
    for (int i=0; i < dapArray->size(); i++) {
        RvizViewer* controller=(RvizViewer*)dapArray->at(i);
        controller->showWindow(1, i);
    }
}
void SideButtonActions::lidarTopClicked(){
    this->allStop("lidarTop");
    cout << "SideButtonActions::lidarTopClicked()"<<endl;
    RvizViewer* controller=(RvizViewer*)rvizMap->find("lidarTop").value()->at(0);
    controller->showWindow();
}

QString SideButtonActions::recordStart(QString dir){
    recordStarter.setRecordDir(dir);
    cout << "SideButtonActions::startClicked()"<<endl;
    QString save_to=recordStarter.start_record();
    return save_to;
}
void SideButtonActions::recordStop(){
    cout << "SideButtonActions::stopClicked()"<<endl;
    QString dir=recordStarter.stop_record();

}
void SideButtonActions::allStart(QString except_one) {
    DAQViz* controller=NULL;
    //각각의 열에는 title, window 두개. camera는 3개가 들어가므로 1,4,6 로 xpos 지정

    //1열 - camera. ypos는 사용하지 않음
    controller=rvizMap->find("cameras").value()->at(0);
    controller->showWindow(1,0);

    //2열 - LiDAR left, Top, right
    controller=rvizMap->find("lidarTop").value()->at(0);
    controller->showWindow(4,1);
    QList<DAQViz*> *dapArray=rvizMap->find("lidarSide").value();
    controller=dapArray->at(0);
    controller->showWindow(4, 0);
    controller=dapArray->at(1);
    controller->showWindow(4, 2);

    //3열 car, gps, imu,radar
    controller=rvizMap->find("car").value()->at(0);
    controller->showWindow(6,0);
    controller=rvizMap->find("gps").value()->at(0);
    controller->showWindow(6,1);
    controller=rvizMap->find("imu").value()->at(0);
    controller->showWindow(6,2);
    controller=rvizMap->find("radar").value()->at(0);
    controller->showWindow(6,3);
}

void SideButtonActions::allStop(QString except_one) {
    for (auto iter=rvizMap->constBegin(); iter != rvizMap->constEnd(); ++iter) {
        if ( iter.key() == except_one) continue;
        QList<DAQViz*> *dapArray=iter.value();
        for (int i=0; i < dapArray->size(); i++) {
            DAQViz* controller=dapArray->at(i);
            if (controller->getButtonState() == ButtonState::ON)
                 controller->closeWindow();
        }

    }
}