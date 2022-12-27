//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RosRunManager
//   Author     : mhjin julu1@naver.com
//   Class Def  : ros launchers, node의 start/stop을 관리하는 managers
//======================================================================*/
#ifndef ROS_RUN_MANAGER_H
#define ROS_RUN_MANAGER_H
#include "init.h"
#include "RosNode.h"
#include "ConfigLoader.h"

#include <QThread>
#include <QString>

#include <ros/ros.h>

class RosRunManager {
public:
    RosRunManager();
    ~RosRunManager();
    bool start();
    bool stop();
    bool shutDown();

private:
    QList<RosNode*> nodeList;
};
#endif