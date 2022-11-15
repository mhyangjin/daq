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

#include "DaqRecorder.h"
#include <ros/ros.h>

class RecordStarter : public QThread{
public:
    RecordStarter();
    ~RecordStarter();
    void run();
    void setRecordDir(QString);
    QString start_record();
    QString stop_record();

private:
    QString dirName;
    QString fileName;
    ButtonState buttonState;
    
    rosbag::RecorderOptions options;
    DaqRecorder* recorder=NULL;
};
#endif