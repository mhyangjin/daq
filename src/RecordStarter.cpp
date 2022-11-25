//======================================================================*/
//   Create Date: 2022/11/09
//   ClassName  : RecordStarter
//   Author     : mhjin julu1@naver.com
//   Class Def  : Record start/stop controller
//======================================================================*/
#include "RecordStarter.h"
#include <QDateTime>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>
RecordStarter::RecordStarter()
:my_pid(0){

}

RecordStarter::~RecordStarter(){
    stopRecord();
}

QString RecordStarter::startRecord(QString _dirName) {
    QString fileName=QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss");
    dirName=_dirName.toStdString();
    bagFile=fileName.toStdString();
    this->start(); 
    return fileName;
}

void RecordStarter::stopRecord(){

    string args="pkill record";
    system(args.data());
    
}

void RecordStarter::run() {
    string args="./scripts/record.sh " + dirName + " " + bagFile;
    system(args.data());
}