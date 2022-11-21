//======================================================================*/
//   Create Date: 2022/11/01
//   ClassName  : main
//   Author     : mhjin, julu1@naver.com
//   Class Def  : daq.exe
//======================================================================*/
#include "daqmain.h"
#include <ros/ros.h>
#include <QApplication>
#include "init.h"

int main(int argc, char *argv[])
{
  if (!ros::master::check()) {
    cout <<"ros::master::check fail" <<endl;
    //system("roscore &");
  }
  if( !ros::isInitialized() )
  {
    cout <<"ros::unisInitialized" <<endl;
    ros::init( argc, argv, "daq", ros::init_options::AnonymousName );
  }
    QApplication a(argc, argv);
    Daqmain w;
    w.show();
    int res= a.exec();
    //ros::waitForShutdown();
    return res;
}
