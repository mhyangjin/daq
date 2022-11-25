//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RosNode
//   Author     : mhjin julu1@naver.com
//   Class Def  : node or launcher
//======================================================================*/
#include "RosNode.h"

RosNode::RosNode(RosType _rosType, QString _nodeName, QString _fileName)
:my_pid(0),
rosType(_rosType) {
    nodeName=_nodeName.toStdString();
    fileName=_fileName.toStdString();
    string pkill_name="pkill " + nodeName;
    system(pkill_name.data());

}

RosNode::~RosNode() {
    stopNode();
}

void RosNode::startNode() {
    ROS_DEBUG("RosNode::start()");
    if (my_pid > 0 ) {
        return;
    }
    this->start();
}

void RosNode::stopNode() {
    if ( my_pid == 0 ) return;

    int32_t status;
    ::kill(my_pid, SIGTERM);
    ::waitpid(my_pid, &status, 0 );
    ROS_DEBUG("RosNode: %s is Stoped!", nodeName.data());
    my_pid=0;
}

void RosNode::run() {
    pid_t pid = ::fork();
    ROS_INFO("RosNode::fork() %d",pid);
    if ( pid == 0 ) {
        ROS_DEBUG("RosNode: %s is Start -file[%s]", nodeName.data(), fileName.data());
        
        ::setsid();
        ::signal(SIGINT, SIG_IGN);
        ::fclose(stdout);
        ::fclose(stdin);
        ::fclose(stderr);
        if ( rosType == RosNode::NODE) {
            ::execlp("rosrun","rosrun", nodeName.data(), fileName.data(), NULL);
            exit(0);
        }
        else {
            ::execlp("roslaunch","roslaunch", nodeName.data(), fileName.data(), NULL);
            exit(0);
        }
    }
    else {
        my_pid = pid;
    }
}