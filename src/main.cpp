//======================================================================*/
//   Create Date: 2022/11/01
//   ClassName  : main
//   Author     : mhjin, julu1@naver.com
//   Class Def  : daq.exe
//======================================================================*/
#include "daqmain.h"
#include <ros/ros.h>
#include <QApplication>
#include <QThread>
#include "init.h"
#include <stdio.h>
#include <signal.h>

static void sig_core(int);

int main(int argc, char *argv[])
{
  ROSCONSOLE_AUTOINIT;

  signal(SIGSEGV, sig_core);
  signal(SIGBUS, sig_core);

  log4cxx::LoggerPtr my_logger;
  my_logger=log4cxx::Logger::getLogger(ROSCONSOLE_DEFAULT_NAME);
  my_logger->setLevel(ros::console::g_level_lookup[ros::console::levels::Debug]);
  //my_logger->setLevel(ros::console::g_level_lookup[ros::console::levels::Info]);
  ROS_DEBUG("LOG Level >> over Debug");
  ROS_INFO("LOG Level >> over Info");
  ROS_WARN("LOG Level >> over Warn");
  ROS_ERROR("LOG Level >> over Error");
  ROS_FATAL("LOG Level >> over Fatal");

  if( !ros::isInitialized() )
  {
    ROS_INFO("ros::Initializing....");
    ros::init( argc, argv, "daq", ros::init_options::AnonymousName );
    
    if (!ros::master::check()) {
      ROS_INFO("ros::core startind.....");
      system("roscore &");
      QThread::sleep(3);
    }
  }
    ROS_INFO("DAQ: start service...");
    QApplication a(argc, argv);
    Daqmain w;
    w.show();
    int res= a.exec();
    return res;
}

void sig_core(int signal_no) {
  ROS_FATAL("DAQ: abnormal exit by signal-%d", signal_no);

  ConfigLoader config;
  string args=config.getScriptConfig().toStdString() + "/run.sh kill";
  system(args.data());
  system("pkill roscore");
  exit(1);
}

