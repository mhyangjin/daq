//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RosRunner
//   Author     : mhjin julu1@naver.com
//   Class Def  : RosRunner
//======================================================================*/
#include "RosRunner.h"
#include "ConfigLoader.h"

static ConfigLoader config;

RosRunner::RosRunner() 
:my_pid(0){
    ROS_DEBUG("DAQ::RosRunner::RosRunner");
}
RosRunner::~RosRunner()  {
    stopRosNode();
}
void RosRunner::startRosNode(){
    this->start();
}
void RosRunner::stopRosNode(){

    string args=config.getScriptConfig().toStdString() + "/run.sh kill";
    system(args.data());
}  
void RosRunner::run(){
    
    string args=config.getScriptConfig().toStdString() + "/run.sh run";
    system(args.data());
}
