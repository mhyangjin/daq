//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RosRunManager
//   Author     : mhjin julu1@naver.com
//   Class Def  : ros launchers, node의 start/stop을 관리하는 managers
//======================================================================*/
#include "RosRunManager.h"

 RosRunManager::RosRunManager() {
    ROS_DEBUG("DAQ::RosRunManager::RosRunManager");
    QMap<QString, QString> nodeMap=config.getnodes();
    QMap<QString, QString> launcherMap=config.getlaunchers();
    ROS_DEBUG("DAQ::RosRunManager::nodeMap-%d",nodeMap.size() );
    for (auto iter=nodeMap.constBegin(); iter != nodeMap.constEnd(); ++iter) {
        nodeList.push_back(new RosNode(RosNode::NODE, iter.key(),iter.value()));
    }
    ROS_DEBUG("DAQ::RosRunManager::nodeMap");
    for (auto iter=launcherMap.constBegin(); iter != launcherMap.constEnd(); ++iter) {
        nodeList.push_back(new RosNode(RosNode::LAUNCHER, iter.key(),iter.value()));
    }
    ROS_DEBUG("DAQ::RosRunManager::nodeMap");
 }
bool RosRunManager::start() {
    ROS_INFO(" RosRunManager::start() : %d ",nodeList.size() );
    for (int i=0; i< nodeList.size(); i++) {
        RosNode* node=nodeList.at(i);
        node->startNode();
    }
    return true;
}
bool RosRunManager::stop() {
    ROS_INFO(" RosRunManager::stop():" );
    for (int i=0; i< nodeList.size(); i++) {
        RosNode* node=nodeList.at(i);
        node->stopNode();
    }
    return true;
}

RosRunManager::~RosRunManager() {
    for (auto iter=nodeList.begin(); iter!=nodeList.end(); iter++) {
        delete *iter;
    }  
}