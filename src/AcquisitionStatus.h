//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : AcquisitionStatus
//   Author     : mhjin julu1@naver.com
//   Class Def  : AcquisitionStatus 바의 상태 체크를 위한 클래스
//======================================================================*/
#ifndef ACQUISITIONSTATUS_H
#define ACQUISITIONSTATUS_H
#include <QMainWindow>
#include <QThread>
#include <QTime>
#include "init.h"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "daq/Sensor_status.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DaqMain; }
QT_END_NAMESPACE


class AcquisitionStatus : public QThread
{
private:
    class SensorStatus {
    public:
        SensorStatus(QString,QLabel*);
        void changeState(AcquisitonStateEnum);
        inline AcquisitonStateEnum getState(){return label_state;}
        
    protected:
        
        AcquisitonStateEnum label_state;
        QString sensor_name;
        QLabel* label;
    };

public:
    AcquisitionStatus(Ui::DaqMain* daqMain);
    ~AcquisitionStatus();
    void run();
    void setRunStatus(QString);
    void setStopStatus(QString);
    void subscribeCallBack(const daq::Sensor_status&);
private:
    Ui::DaqMain* ui;   
    QMap<StsName, AcquisitionStatus::SensorStatus*>* statusMap;
    ros::Subscriber subscriber;
    ros::NodeHandle nodeHandle;
    QStringList  sensorTopicList;
    //message가 들어온 마지막 시간만 저장해 둔다
    QTime lastTime;
};
#endif // DAQMAIN_H
