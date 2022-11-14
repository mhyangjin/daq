//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : AcquisitionStatus
//   Author     : mhjin julu1@naver.com
//   Class Def  : AcquisitionStatus 바의 상태 체크를 위한 클래스
//======================================================================*/
#include "AcquisitionStatus.h"
#include <sstream>

AcquisitionStatus::SensorStatus::SensorStatus(QString _sensor_name, QLabel* _label) 
:sensor_name(_sensor_name),
label(_label),
label_state(AcquisitonStateEnum::DEFAULT)
{
    changeState(label_state);
}

void AcquisitionStatus::SensorStatus::changeState(AcquisitonStateEnum _state) {
    label_state=_state;
    label->setPixmap(img_source[label_state]);
    label->setAlignment(Qt::AlignCenter);
}

AcquisitionStatus::AcquisitionStatus(Ui::DaqMain* daqMain)
:ui(daqMain)
{
    //sensor 상태를 보내주는 /diagnostic topic msg의 sensor_name 
    //배열은 init.h에서 정의한 StsName enum의 순서와 1대1 mapping 된다.
    //따라서 순서가 바뀌면 안됨
    sensorTopicList<<"Front_Camera"
    <<"Left_Camera"
    << "Right_Camera"
    << "IMU"
    << "CAN"    //2022/11/10 CAR와 RADAR 의 sensor_name 구분이 안되었음.
    << "CAN1"    //일단 CAN으로 동일하게 설정
    << "Top_LiDAR"
    << "Left_LiDAR"
    << "Right_LiDAR"
    <<"GPS";

    statusMap= new QMap<StsName, AcquisitionStatus::SensorStatus*>();

    statusMap->insert(StsName::CAM_F1, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::CAM_F1],ui->img_camf1));
    statusMap->insert(StsName::CAM_S1, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::CAM_S1],ui->img_cams1));
    statusMap->insert(StsName::CAM_S2, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::CAM_S2],ui->img_cams2));
    statusMap->insert(StsName::IMU, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::IMU], ui->img_imu));
    statusMap->insert(StsName::CAR, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::CAR], ui->img_car));
    statusMap->insert(StsName::RADAR, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::RADAR], ui->img_radar));
    statusMap->insert(StsName::LIDAR_T1, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::LIDAR_T1], ui->img_lidar_top));
    statusMap->insert(StsName::LIDAR_S1, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::LIDAR_S1], ui->img_lidar_side1));
    statusMap->insert(StsName::LIDAR_S2, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::LIDAR_S2], ui->img_lidar_side2));
    statusMap->insert(StsName::GPS, 
                new AcquisitionStatus::SensorStatus(sensorTopicList[StsName::GPS], ui->img_gps));
                
    subscriber = nodeHandle.subscribe(qPrintable(pubName), 10, &AcquisitionStatus::subscribeCallBack,this );
    
    //topic 이 제대로 들어오는지 감시하기 위한 thread
    this->start();
}

AcquisitionStatus::~AcquisitionStatus(){

}

void AcquisitionStatus::run() {
    QTime befores=lastTime;
    QThread::sleep(2);
    while (true) {
        if ( befores == lastTime)
        {
            ui->statusbar->showMessage("sensor 상태 메시지가 없습니다" );
        } 
        else {
            ui->statusbar->clearMessage( );
            
            befores=lastTime;
        } 
        QThread::sleep(2);
    }
}


void AcquisitionStatus::subscribeCallBack(const daq::Sensor_status& msg) {
    QString sensorName=msg.sensor_name.data();
    //cout << "AcquisitionStatus::subscribeCallBack: msg Num:" << msg <<endl;
    AcquisitonStateEnum status=AcquisitonStateEnum::DEFAULT;
    //sensorTopicList 배열의 위치는  StsName 과 같다.
    StsName stsEnum =(StsName)sensorTopicList.indexOf(sensorName);
    if ( msg.status== 0)
        status=AcquisitonStateEnum::STOP;
    else 
        status=AcquisitonStateEnum::RUN;
    
    auto iter=statusMap->find(stsEnum);
    iter.value()->changeState(status);

    lastTime = QTime::currentTime();
}


void AcquisitionStatus::setRunStatus(QString labelName){
    for (auto iter=statusMap->constBegin(); iter != statusMap->constEnd(); ++iter) {
        iter.value()->changeState(AcquisitonStateEnum::RUN);
    }
}

void AcquisitionStatus::setStopStatus(QString labelName){
    for (auto iter=statusMap->constBegin(); iter != statusMap->constEnd(); ++iter) {
        iter.value()->changeState(AcquisitonStateEnum::STOP);
    }
}