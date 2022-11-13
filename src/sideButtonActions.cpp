//======================================================================*/
//   Create Date: 2022/11/6
//   ClassName  : SideButtionActions
//   Author     : mhjin julu1@naver.com
//   Class Def  : side button을 클릭했을 때 수행할 동작들
//======================================================================*/
#include "sideButtonActions.h"
#include "DaqCameraDisplay.h"
#include "SubController.h"
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

 void SideButtonActions::createRvizViewers() {

    //윈도우 생성시 미리 GUI창을 미리 만들어 둔다.
    rvizMap=new QMap<QString, QList<DAQViz*>*>();
    QList<DAQViz*> *lidar_tmp= new QList<DAQViz*>();
    lidar_tmp->append( (DAQViz*) new RvizController(ui,"./rvizs/ouster.rviz","liDar Top"));

    QList<DAQViz*> *camera_tmp= new QList<DAQViz*>();
    camera_tmp->append( (DAQViz*) new DaqCameraDisplay(ui,"./rvizs/cameras.rviz", "Camera" ));

    QList<DAQViz*> *l_side_tmp= new QList<DAQViz*>();
    l_side_tmp->append( (DAQViz*) new RvizController(ui,"./rvizs/left_vel.rviz", "liDAR Side-Left",1,0 ));
    l_side_tmp->append( (DAQViz*) new RvizController(ui,"./rvizs/right_vel.rviz", "LiDAR Side-right",1,1 ));

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
    gps_tmp->append( (DAQViz*) new SubController(ui, (SignalsSlot*)gps_topic, "GPS"));
    //imu
    TopicSubscribers<sensor_msgs::Imu>* imu_topic= new TopicSubscribers<sensor_msgs::Imu>("/gps/imu", spiner);
    QList<DAQViz*> *imu_tmp= new QList<DAQViz*>();
    imu_tmp->append( (DAQViz*) new SubController(ui, (SignalsSlot*)imu_topic, "IMU"));
    //radar
    TopicSubscribers<daq::Radar>* radar_topic= new TopicSubscribers<daq::Radar>("/can/radar", spiner);
    QList<DAQViz*> *radar_tmp= new QList<DAQViz*>();
    radar_tmp->append( (DAQViz*) new SubController(ui,(SignalsSlot*)radar_topic,"radar"));
    //car
    TopicSubscribers<daq::Car>* car_topic= new TopicSubscribers<daq::Car>("/can/car", spiner);
     QList<DAQViz*> *car_tmp= new QList<DAQViz*>();
    car_tmp->append( (DAQViz*) new SubController(ui,(SignalsSlot*)car_topic,"Car" ));
    
    //click event를 받았을 때  display를 hide, show 처리를 위해 map에 넣어둔다.
    rvizMap->insert("gps", gps_tmp);
    rvizMap->insert("imu", imu_tmp);
    rvizMap->insert("radar", radar_tmp);
    rvizMap->insert("car", car_tmp);

 
}
void SideButtonActions::allViewClicked(){
    this->allStop("nothing");
    cout << "SideButtonActions::allViewClicked()"<<endl;
}
void SideButtonActions::cameraClicked(){
    this->allStop("cameras");
    cout << "SideButtonActions::cameraClicked()"<<endl;
    DaqCameraDisplay* controller=(DaqCameraDisplay*)rvizMap->find("cameras").value()->at(0);
    controller->clicked();    
}

void SideButtonActions::carInfoClicked(){
    this->allStop("car");
    cout << "SideButtonActions::carClicked()"<<endl;
    SubController* controller=(SubController*)rvizMap->find("car").value()->at(0);
    controller->clicked();

}
void SideButtonActions::gpsClicked(){
    this->allStop("gps");
    cout << "SideButtonActions::gpsClicked()"<<endl;
    SubController* controller=(SubController*)rvizMap->find("gps").value()->at(0);
    controller->clicked();
}
void SideButtonActions::imuClicked(){
    this->allStop("imu");
    cout << "SideButtonActions::imuClicked()"<<endl;
    SubController* controller=(SubController*)rvizMap->find("imu").value()->at(0);
    controller->clicked();
}
void SideButtonActions::radarClicked(){
    this->allStop("radar");
    cout << "SideButtonActions::radarClicked()"<<endl;
    SubController* controller=(SubController*)rvizMap->find("radar").value()->at(0);
    controller->clicked();
}

void SideButtonActions::lidarSideClicked(){
    this->allStop("lidarSide");
    cout << "SideButtonActions::lidarSideClicked()"<<endl;
    QList<DAQViz*> *dapArray=rvizMap->find("lidarSide").value();
    for (int i=0; i < dapArray->size(); i++) {
        RvizController* controller=(RvizController*)dapArray->at(i);
        controller->clicked();
    }
}
void SideButtonActions::lidarTopClicked(){
    this->allStop("lidarTop");
    cout << "SideButtonActions::lidarTopClicked()"<<endl;
    RvizController* controller=(RvizController*)rvizMap->find("lidarTop").value()->at(0);
    controller->clicked();
}


void SideButtonActions::acquisitionClicked(QString dir){

    cout << "SideButtonActions::acquisitionClicked()"<<qPrintable(dir)<<endl;
    recordStarter.setRecordDir(dir);
    ui->label_Path->setText(dir);
    ui->btn_start->setEnabled(true);
}

void SideButtonActions::startClicked(){
    cout << "SideButtonActions::startClicked()"<<endl;
    QString save_to=recordStarter.start_record();
    ui->label_fileName->setText(save_to);
    ui->btn_start->setDisabled(true);
    ui->btn_stop->setEnabled(true);

}
void SideButtonActions::stopClicked(){
    cout << "SideButtonActions::stopClicked()"<<endl;
    QString dir=recordStarter.stop_record();
    ui->label_fileName->setText("");
    ui->btn_start->setEnabled(true);
    ui->btn_stop->setDisabled(true);
}

void SideButtonActions::allStart(QString except_one) {
    for (auto iter=rvizMap->constBegin(); iter != rvizMap->constEnd(); ++iter) {
        if ( iter.key() == except_one) continue;
        QList<DAQViz*> *dapArray=iter.value();
        for (int i=0; i < dapArray->size(); i++) {
            DAQViz* controller=dapArray->at(i);
            if (controller->getButtonState() == ButtonState::OFF)
                controller->showWindow();
        }
            
    }
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