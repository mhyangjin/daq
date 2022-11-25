
//======================================================================*/
//   Create Date: 2022/11/12
//   ClassName  : TopicSubscribers
//   Author     : mhjin julu1@naver.com
//   Class Def  : 모든 topic을 모두 sub하기 위한 클래스
//                ros::spin() thread를 block하고 대기하여, 여러개의 topic을
//                함께 sub할 수 없다.
//                multi-thread여야 하기 때문에 ros::spiner를 사용한다.
//======================================================================*/
#ifndef TOPPICSUBSCRIBER_H
#define TOPPICSUBSCRIBER_H
#include "init.h"
#include <QStringListModel>
#include <QListView>
#include <QThread>

#include <std_msgs/String.h>
#include <ros/ros.h>
#include <ros/network.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <daq/Radar.h>
#include <daq/Car.h>
#include <daq/Sensor_status.h>

class SignalsSlot : public QObject {
Q_OBJECT    
public:
    explicit SignalsSlot(QObject *parent=0):QObject(parent){}
    QStringListModel* getListModel(){return &qstringList;};
signals:
    void dataUpdated();
protected:
    QStringListModel qstringList;

};

template <class T>  
class TopicSubscribers : public QThread, SignalsSlot {
public:
    TopicSubscribers(QString, ros::MultiThreadedSpinner*);
    void subscribeCallBack(const class T::ConstPtr& msg);
    void run();
//signals:
 //  void dataUpdated();
private:
    bool running;
    ros::Subscriber subscriber;
    ros::NodeHandle nodeHandle;   
    ros::MultiThreadedSpinner* spiner;
    QString topicName;
};

#endif