//======================================================================*/
//   Create Date: 2022/11/01
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : DAQ의 MainWindow
//======================================================================*/
#include "daqmain.h"
#include "DAQViz.h"
#include <QFileDialog>

Daqmain::Daqmain(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::DaqMain)
{
    ui->setupUi(this);
  
    //button을 클릭할 떄 수행할 Actions를 등록해 준다.
    connect(ui->btn_acquisition, SIGNAL(clicked()), this, SLOT(acquisitionClicked()));
    connect(ui->btn_all, SIGNAL(clicked()), this, SLOT(allViewClicked()));
    connect(ui->btn_camera, SIGNAL(clicked()), this, SLOT(cameraClicked()));
    connect(ui->btn_carInfo, SIGNAL(clicked()), this, SLOT(carInfoClicked()));
    connect(ui->btn_gps, SIGNAL(clicked()), this, SLOT(gpsClicked()));
    connect(ui->btn_imu, SIGNAL(clicked()), this, SLOT(imuClicked()));
    connect(ui->btn_lidarSide, SIGNAL(clicked()), this, SLOT(lidarSideClicked()));
    connect(ui->btn_lidarTop, SIGNAL(clicked()), this, SLOT(lidarTopClicked()));
    connect(ui->btn_radar, SIGNAL(clicked()), this, SLOT(radarClicked()));
    connect(ui->btn_start, SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(stopClicked()));
    

    sideButtonActions=new SideButtonActions(ui);
    acquisitionStatus=new AcquisitionStatus(ui);
    
    ui->btn_start->setDisabled(true);
    ui->btn_stop->setDisabled(true);
}

Daqmain::~Daqmain()
{
}

void Daqmain::acquisitionClicked(){
    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory", "/home/mhjin/project", QFileDialog::ShowDirsOnly);
    //QString dir = QFileDialog::getExistingDirectory(this, "Open Directory", "/home/jiat/Data", QFileDialog::ShowDirsOnly);
    if (dir != NULL) 
        sideButtonActions->acquisitionClicked(dir );

}
void Daqmain::allViewClicked(){
    sideButtonActions->allViewClicked();

}
void Daqmain::cameraClicked(){
    sideButtonActions->cameraClicked();

}
void Daqmain::carInfoClicked(){
    sideButtonActions->carInfoClicked();

}
void Daqmain::gpsClicked(){
    sideButtonActions->gpsClicked();

}
void Daqmain::imuClicked(){
    sideButtonActions->imuClicked();

}
void Daqmain::lidarSideClicked(){
    sideButtonActions->lidarSideClicked();

}
void Daqmain::lidarTopClicked(){
    
    sideButtonActions->lidarTopClicked();
}
void Daqmain::radarClicked(){
    sideButtonActions->radarClicked();

}

void Daqmain::startClicked(){
    sideButtonActions->startClicked();

}
void Daqmain::stopClicked(){
    sideButtonActions->stopClicked();

}

void Daqmain::closeEvent(QCloseEvent *event) {
    ros::shutdown();
    system ("/home/mhjin/script/kill.sh");
    //system ("/home/jiat/script/kill.sh");
}