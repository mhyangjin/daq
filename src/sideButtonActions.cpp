//======================================================================*/
//   Create Date: 2022/11/6
//   ClassName  : SideButtionActions
//   Author     : mhjin julu1@naver.com
//   Class Def  : side button을 클릭했을 때 수행할 동작들
//======================================================================*/
#include "sideButtonActions.h"
#include "DaqCameraDisplay.h"
#include "SubController.h"
#include <QFileDialog>
 SideButtonActions::SideButtonActions(Ui::DaqMain *_ui)
 :ui(_ui){
    spiner= new ros::MultiThreadedSpinner(4);
    //윈도우 생성시 미리 GUI창을 미리 만들어 둔다.
    rvizMap=new QMap<QString, QList<DAQViz*>*>();
    QList<DAQViz*> *lidar_tmp= new QList<DAQViz*>();
    lidar_tmp->append( (DAQViz*) new RvizController(ui,"./rvizs/ouster.rviz" ));

    QList<DAQViz*> *camera_tmp= new QList<DAQViz*>();
    camera_tmp->append( (DAQViz*) new RvizController(ui,"./rvizs/cameras.rviz" ));

    QList<DAQViz*> *l_side_tmp= new QList<DAQViz*>();
    l_side_tmp->append( (DAQViz*) new RvizController(ui,"./rvizs/left_vel.rviz" ));
    l_side_tmp->append( (DAQViz*) new RvizController(ui,"./rvizs/right_vel.rviz" ));

    QList<DAQViz*> *gps_tmp= new QList<DAQViz*>();
    gps_tmp->append( (DAQViz*) new SubController(ui,"/gps/fix", spiner));
     QList<DAQViz*> *imp_tmp= new QList<DAQViz*>();
    imp_tmp->append( (DAQViz*) new SubController(ui,"/gps/imu", spiner ));
     QList<DAQViz*> *radar_tmp= new QList<DAQViz*>();
    radar_tmp->append( (DAQViz*) new SubController(ui,"/can/radar", spiner ));
     QList<DAQViz*> *car_tmp= new QList<DAQViz*>();
    car_tmp->append( (DAQViz*) new SubController(ui,"/can/car", spiner ));

    rvizMap->insert("lidarTop", lidar_tmp);
    rvizMap->insert("cameras", camera_tmp);
    rvizMap->insert("lidarSide", l_side_tmp);
    rvizMap->insert("gps", gps_tmp);
    rvizMap->insert("imu", imp_tmp);
    rvizMap->insert("radar", radar_tmp);
    rvizMap->insert("car", car_tmp);
    
    acquisitionStatus=new AcquisitionStatus(ui);
    acquisitionStatus->setDefaultImages();
    
 }


void SideButtonActions::sensorRunStatus(){
    acquisitionStatus->setRunStatus("all");

}
void SideButtonActions::sensorStopStatus(){
    acquisitionStatus->setStopStatus("all");

}

void SideButtonActions::allViewClicked(){
    this->allStop("nothing");
    cout << "SideButtonActions::allViewClicked()"<<endl;
}
void SideButtonActions::cameraClicked(){
    this->allStop("cameras");
    cout << "SideButtonActions::cameraClicked()"<<endl;
    RvizController* controller=(RvizController*)rvizMap->find("cameras").value()->at(0);
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

void SideButtonActions::sesorClicked(){
    this->allStop("something");
    cout << "SideButtonActions::sesorClicked()"<<endl;

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
            RvizController* controller=(RvizController*)dapArray->at(i);
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
            RvizController* controller=(RvizController*)dapArray->at(i);
            if (controller->getButtonState() == ButtonState::ON)
                 controller->closeWindow();
        }
           
    }
}