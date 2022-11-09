//======================================================================*/
//   Create Date: 2022/11/01
//   ClassName  : main
//   Author     : mhjin, julu1@naver.com
//   Class Def  : daq.exe
//======================================================================*/
#include "daqmain.h"
#include <ros/ros.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    if( !ros::isInitialized() )
  {
    ros::init( argc, argv, "daq", ros::init_options::AnonymousName );
  }
    QApplication a(argc, argv);
    Daqmain w;
    w.show();
    return a.exec();
}
