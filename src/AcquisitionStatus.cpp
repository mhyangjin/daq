//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : AcquisitionStatus
//   Author     : mhjin julu1@naver.com
//   Class Def  : AcquisitionStatus 바의 상태 체크를 위한 클래스
//======================================================================*/
#include "AcquisitionStatus.h"

AcquisitionStatus::AcquisitionStatus(Ui::DaqMain* daqMain)
:ui(daqMain)
{
    statusLabelMap= new QMap<QString, QLabel*>();
    statusLabelMap->insert("camf1", ui->img_camf1);
    statusLabelMap->insert("cams1", ui->img_cams1);
    statusLabelMap->insert("cams2", ui->img_cams2);
    statusLabelMap->insert("imu", ui->img_imu);
    statusLabelMap->insert("car", ui->img_car);
    statusLabelMap->insert("radar", ui->img_radar);
    statusLabelMap->insert("lidartop1", ui->img_lidar_top);
    statusLabelMap->insert("lidarside1", ui->img_lidar_side1);
    statusLabelMap->insert("lidarside2", ui->img_lidar_side2);
    statusLabelMap->insert("gps", ui->img_gps);
}

AcquisitionStatus::~AcquisitionStatus(){

}

void AcquisitionStatus::setDefaultImages() {
    for (auto iter=statusLabelMap->constBegin(); iter != statusLabelMap->constEnd(); ++iter) {
        iter.value()->setPixmap(img_source[AcquisitonStateEnum::DEFAULT]);
        iter.value()->setAlignment(Qt::AlignCenter);
    }
}

void AcquisitionStatus::setRunStatus(QString labelName){
    if ( labelName=="all") {
        for (auto iter=statusLabelMap->constBegin(); iter != statusLabelMap->constEnd(); ++iter) {
            iter.value()->setPixmap(img_source[AcquisitonStateEnum::RUN]);
            iter.value()->setAlignment(Qt::AlignCenter);
        }
    }
    else {
         auto iter=statusLabelMap->find(labelName);
        iter.value()->setPixmap(img_source[AcquisitonStateEnum::RUN]);
        iter.value()->setAlignment(Qt::AlignCenter);
    }
}

void AcquisitionStatus::setStopStatus(QString labelName){
    if ( labelName=="all") {
        for (auto iter=statusLabelMap->constBegin(); iter != statusLabelMap->constEnd(); ++iter) {
            iter.value()->setPixmap(img_source[AcquisitonStateEnum::STOP]);
            iter.value()->setAlignment(Qt::AlignCenter);
        }
    }
    else {
        auto iter=statusLabelMap->find(labelName);
        iter.value()->setPixmap(img_source[AcquisitonStateEnum::STOP]);
        iter.value()->setAlignment(Qt::AlignCenter);
    }
}