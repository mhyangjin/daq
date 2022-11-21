//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RosNode
//   Author     : mhjin julu1@naver.com
//   Class Def  : node or launcher
//======================================================================*/
#ifndef ROS_NODE_H
#define ROS_NODE_H

#include "init.h"
#include <QThread>
#include <QString>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ros/ros.h>
#include <ros/console.h>
class RosNode: public QThread {
public:
    enum RosType {
        NODE=0,
        LAUNCHER
    };
public:
    RosNode(RosType, QString, QString);
    ~RosNode();
    void startNode();
    void stopNode();
private:
    void run();

    string nodeName;
    string fileName;
    RosType rosType;
    pid_t   my_pid;

};
#endif