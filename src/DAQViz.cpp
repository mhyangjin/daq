//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : DAQViz
//   Author     : mhjin julu1@naver.com
//   Class Def  : .rviz file을 읽어서 rviz::Config로 만든 후 VisualizationManager
//                를 통해 GUI로 보내기 위한 최상위 class.
//                sensor 별로 이 클래스를 상속받아 하위로 구현한다.
//======================================================================*/
#include "DAQViz.h"
#include <QFile>
#include <rviz/yaml_config_reader.h>
#include <rviz/display_group.h>
#include <rviz/config.h>

DAQViz::DAQViz(Ui::DaqMain* daqMain,  QString _title, int x,int y)
:ui(daqMain),
title(new QLabel(_title)),
buttonState(ButtonState::OFF)
{
    title->setMaximumSize(10000,20);
    title->adjustSize();
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);    //
    //display_layout.addWidget(&title);
    title->setAlignment(Qt::AlignCenter|Qt::AlignBottom);
    title->hide();
    setPosition(x,y);
    connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(stopClicked()));
    connect(ui->btn_all, SIGNAL(clicked()), this, SLOT(allViewClicked()));
    connect(ui->btn_camera, SIGNAL(clicked()), this, SLOT(cameraClicked()));
    connect(ui->btn_carInfo, SIGNAL(clicked()), this, SLOT(carInfoClicked()));
    connect(ui->btn_gps, SIGNAL(clicked()), this, SLOT(gpsClicked()));
    connect(ui->btn_imu, SIGNAL(clicked()), this, SLOT(imuClicked()));
    connect(ui->btn_lidarSide, SIGNAL(clicked()), this, SLOT(lidarSideClicked()));
    connect(ui->btn_lidarTop, SIGNAL(clicked()), this, SLOT(lidarTopClicked()));
    connect(ui->btn_radar, SIGNAL(clicked()), this, SLOT(radarClicked()));
}

DAQViz::~DAQViz() {

}

void DAQViz::setPosition(int x,int y) {
    posx=x;
    posy=y;
}

void DAQViz::allViewClicked(){
    showWindow(posx,posy);
}

void DAQViz::stopClicked(){
    closeWindow();
}

void DAQViz::cameraClicked(){
    if ( title->text() == "Camera")
        showWindow();
    else
        closeWindow();
}
void DAQViz::carInfoClicked(){
    if ( title->text() == "Car Info")
        showWindow();
    else
        closeWindow();
}
void DAQViz::gpsClicked(){
    if ( title->text()  == "GPS")
        showWindow();
    else
        closeWindow();
}
void DAQViz::imuClicked(){
    if ( title->text()  == "IMU")
        showWindow();
    else
        closeWindow();
}
void DAQViz::lidarSideClicked(){
    if ( title->text()  == "LiDAR left" || title->text()  == "LiDAR right" )
        showWindow();
    else
        closeWindow();
}
void DAQViz::lidarTopClicked(){
    if ( title->text()  == "LiDAR top")
        showWindow();
    else
        closeWindow();
}
void DAQViz::radarClicked(){
    if ( title->text()  == "Radar")
        showWindow();
    else
        closeWindow();
}