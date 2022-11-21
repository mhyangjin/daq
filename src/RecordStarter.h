//======================================================================*/
//   Create Date: 2022/11/09
//   ClassName  : RecordStarter
//   Author     : mhjin julu1@naver.com
//   Class Def  : Record start/stop controller
//======================================================================*/
#ifndef RECORDSTARTER_H
#define RECORDSTARTER_H
#include "init.h"
#include <QStringList>
#include <vector>
#include <QThread>

#include <ros/ros.h>

class RecordStarter : public QThread{
public:
    RecordStarter();
    ~RecordStarter();
    QString startRecord(QString);
    void stopRecord();
private:
    void run();   

private:
    string  bagFile;
    string  dirName;
    pid_t   my_pid;
};
#endif