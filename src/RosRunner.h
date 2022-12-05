//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RosRunner
//   Author     : mhjin julu1@naver.com
//   Class Def  : Record Player
//======================================================================*/
#ifndef ROS_RUNNER_H
#define ROS_RUNNER_H
#include "init.h"
#include <QThread>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ros/ros.h>
#include <ros/console.h>

class RosRunner : public QThread {
public:
    RosRunner();
    ~RosRunner();
    void startRosNode( );
    void stopRosNode();
private:
    void run( );


    string  bagFile;
    pid_t   my_pid;
};
#endif