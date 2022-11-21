//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RosRunManager
//   Author     : mhjin julu1@naver.com
//   Class Def  : ros launchers, node의 start/stop을 관리하는 managers
//======================================================================*/
#include "RosRunManager.h"

 RosRunManager::RosRunManager() {
    cout << " RosRunManager::RosRunManager() " <<endl;
    QMap<QString, QString> nodeMap=config.getnodes();
    QMap<QString, QString> launcherMap=config.getlaunchers();
    for (auto iter=nodeMap.constBegin(); iter != nodeMap.constEnd(); ++iter) {
        nodeList.push_back(new RosNode(RosNode::NODE, iter.key(),iter.value()));
    }
    for (auto iter=launcherMap.constBegin(); iter != launcherMap.constEnd(); ++iter) {
        nodeList.push_back(new RosNode(RosNode::LAUNCHER, iter.key(),iter.value()));
    }
 }
bool RosRunManager::start() {
    cout << " nodeList::start() "<< nodeList.size() <<endl;
    for (int i=0; i< nodeList.size(); i++) {
        cout << " nodeList::"<<i <<endl;
        RosNode* node=nodeList.at(i);
        node->startNode();
    }
    return true;
}
bool RosRunManager::stop() {
    cout << " RosRunManager::stop()::"<<endl;
    for (int i=0; i< nodeList.size(); i++) {
        RosNode* node=nodeList.at(i);
        node->stopNode();
    }
    return true;
}

RosRunManager::~RosRunManager() {
    for (int i=0; i< nodeList.size(); i++) {
        RosNode* node=nodeList.at(i);
        delete node;
    }  
}