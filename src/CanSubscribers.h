
//======================================================================*/
//   Create Date: 2022/11/12
//   ClassName  : CanSubscribers
//   Author     : mhjin julu1@naver.com
//   Class Def  : 모든 topic을 모두 sub하기 위한 클래스
//                ros::spin() thread를 block하고 대기하여, 여러개의 topic을
//                함께 sub할 수 없다.
//                multi-thread여야 하기 때문에 ros::spiner를 사용한다.
//======================================================================*/
#ifndef CANSUBSCRIBER_H
#define CANSUBSCRIBER_H
#include "init.h"
#include "TopicSubscribers.h"
#include <QStringListModel>
#include <QListView>
#include <QThread>

#include <std_msgs/String.h>
#include <ros/ros.h>
#include <ros/network.h>
#include <daq/Radar.h>
#include <daq/Car.h>
#include <daq/Can.h>

class CanSubscribers : public QThread, SignalsSlot {
public:
    CanSubscribers(QString, ros::MultiThreadedSpinner*);
    void subscribeCallBack(const daq::Can& msg);
    void run();
private:
    bool running;
    ros::Subscriber subscriber;
    ros::NodeHandle nodeHandle;   
    ros::MultiThreadedSpinner* spiner;
    QString topicName;
};

#endif