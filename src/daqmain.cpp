//======================================================================*/
//   Create Date: 2022/11/01
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : DAQ의 MainWindow
//                  ui상의 controll들의 signal은 모두 여기에서 처리한다
//                  ui상의 signal 별로 ui의 disable, enable 도 여기에서 처리한다.
//                  그 외 로직은 모두 sideButtonActions안에서 처리
//======================================================================*/
#include "daqmain.h"
#include "DAQViz.h"
#include <QFileDialog>
#include "DialogConfig.h"

Daqmain::Daqmain(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::DaqMain)
{
    ui->setupUi(this);

   //button을 클릭할 떄 수행할 Actions를 등록해 준다.
    connect(ui->actionConfigrations, SIGNAL(triggered()), this, SLOT(actionConfigrations()));
    connect(ui->radioButton_sensor, SIGNAL(clicked()), this, SLOT(radioSensorClicked()));
    connect(ui->radioButton_replay, SIGNAL(clicked()), this, SLOT(radioReplayClicked()));
    connect(ui->btn_recordFile, SIGNAL(clicked()), this, SLOT(replayFileClicked()));
    connect(ui->btn_start, SIGNAL(clicked()), this, SLOT(runClicked()));
    connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(stopClicked()));
    connect(ui->btn_all, SIGNAL(clicked()), this, SLOT(allViewClicked()));
    connect(ui->btn_camera, SIGNAL(clicked()), this, SLOT(cameraClicked()));
    connect(ui->btn_carInfo, SIGNAL(clicked()), this, SLOT(carInfoClicked()));
    connect(ui->btn_gps, SIGNAL(clicked()), this, SLOT(gpsClicked()));
    connect(ui->btn_imu, SIGNAL(clicked()), this, SLOT(imuClicked()));
    connect(ui->btn_lidarSide, SIGNAL(clicked()), this, SLOT(lidarSideClicked()));
    connect(ui->btn_lidarTop, SIGNAL(clicked()), this, SLOT(lidarTopClicked()));
    connect(ui->btn_radar, SIGNAL(clicked()), this, SLOT(radarClicked()));
    connect(ui->btn_record, SIGNAL(clicked()), this, SLOT(recordClicked()));
    connect(ui->btn_recordStart, SIGNAL(clicked()), this, SLOT(recordStartClicked()));
    connect(ui->btn_recordStop, SIGNAL(clicked()), this, SLOT(recordStopClicked()));

    sideButtonActions=new SideButtonActions(ui);
    acquisitionStatus=new AcquisitionStatus(ui);
}

Daqmain::~Daqmain()
{
    delete ui;
}

void Daqmain::radioSensorClicked() {

    ui->label_replayFileName->setText("");
    ui->btn_recordFile->setDisabled(true);
    ui->btn_start->setEnabled(true);
    ui->btn_stop->setDisabled(true);

    ui->btn_record->setDisabled(true);
    ui->btn_recordStart->setDisabled(true);
    ui->btn_recordStop->setDisabled(true);

}

void Daqmain::radioReplayClicked() {
    ui->btn_recordFile->setEnabled(true);
    ui->btn_start->setEnabled(true);
    ui->btn_stop->setDisabled(true);

    ui->btn_record->setDisabled(true);
    ui->btn_recordStart->setDisabled(true);
    ui->btn_recordStop->setDisabled(true);
    
}

void Daqmain::replayFileClicked() {
    QString file = QFileDialog::getOpenFileName(this, "Open File", "/home/mhjin/project", tr("*.bag"));
    if (file != NULL) {
        ui->label_replayFileName->setText(file);
    }
}

void Daqmain::runClicked() {
    if (ui->radioButton_replay->isChecked()) {
        QString file=ui->label_replayFileName->text();
        if (file!="") {
            if (!sideButtonActions->replayStart(file))
                return;
        }
    }
    else {
        if (!sideButtonActions->sensorStart()) 
            return;
        sideButtonActions->sensorStart();
        ui->btn_record->setEnabled(true);
        ui->btn_recordStart->setEnabled(true);
        ui->btn_recordStop->setDisabled(true);
    }

    ui->btn_recordFile->setDisabled(true);
    ui->btn_start->setDisabled(true);
    ui->btn_stop->setEnabled(true);

    allViewEnabled();
    
}
void Daqmain::stopClicked() {
    if (ui->radioButton_replay->isChecked()) {
        sideButtonActions->replayStop();
        ui->btn_recordFile->setEnabled(true);
    }
    else {
        sideButtonActions->sensorStop();
        ui->btn_recordFile->setDisabled(true);
    }
    ui->btn_record->setDisabled(true);
    ui->btn_recordStart->setDisabled(true);
    ui->btn_recordStop->setDisabled(true);
    ui->btn_start->setEnabled(true);
    ui->btn_stop->setDisabled(true);
    allViewDisabled();
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
void Daqmain::recordClicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory", "/home/mhjin/project", QFileDialog::ShowDirsOnly);
    //QString dir = QFileDialog::getExistingDirectory(this, "Open Directory", "/home/jiat/Data", QFileDialog::ShowDirsOnly);
    if (dir != NULL) {
        ui->label_Path->setText(dir);
        ui->btn_recordStart->setEnabled(true);
        ui->btn_recordStop->setDisabled(true);
    }
}
void Daqmain::recordStartClicked(){
    QString Dir=ui->label_Path->text();
    QString save_to=sideButtonActions->recordStart(Dir);
    ui->label_fileName->setText(save_to);
    ui->btn_recordStart->setDisabled(true);
    ui->btn_recordStop->setEnabled(true);

    ui->radioButton_sensor->setDisabled(true);
    ui->radioButton_replay->setDisabled(true);
    ui->btn_start->setDisabled(true);
}

void Daqmain::recordStopClicked(){
    sideButtonActions->recordStop();
    ui->label_fileName->setText("");
    ui->btn_recordStart->setEnabled(true);
    ui->btn_recordStop->setDisabled(true);

    ui->radioButton_sensor->setEnabled(true);
    ui->radioButton_replay->setEnabled(true);
}
void Daqmain::actionConfigrations() {
    DialogConfig dialogConfig;
    dialogConfig.setModal(true);
    dialogConfig.exec();
}
void Daqmain::closeEvent(QCloseEvent *event) {
    ros::shutdown();
    system ("/home/mhjin/script/kill.sh");
    QApplication::quit();
    //system ("/home/jiat/script/kill.sh");
}

void Daqmain::allViewEnabled() {
    ui->btn_all->setEnabled(true);
    ui->btn_camera->setEnabled(true);
    ui->btn_carInfo->setEnabled(true);
    ui->btn_gps->setEnabled(true);
    ui->btn_imu->setEnabled(true);
    ui->btn_lidarSide->setEnabled(true);
    ui->btn_lidarTop->setEnabled(true);
    ui->btn_radar->setEnabled(true);
}

void Daqmain::allViewDisabled() {
    ui->btn_all->setDisabled(true);
    ui->btn_camera->setDisabled(true);
    ui->btn_carInfo->setDisabled(true);
    ui->btn_gps->setDisabled(true);
    ui->btn_imu->setDisabled(true);
    ui->btn_lidarSide->setDisabled(true);
    ui->btn_lidarTop->setDisabled(true);
    ui->btn_radar->setDisabled(true);
}