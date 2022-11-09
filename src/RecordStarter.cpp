//======================================================================*/
//   Create Date: 2022/11/09
//   ClassName  : RecordStarter
//   Author     : mhjin julu1@naver.com
//   Class Def  : Record start/stop controller
//======================================================================*/
#include "RecordStarter.h"
#include <QDateTime>

RecordStarter::RecordStarter()
:buttonState(ButtonState::OFF)
{
}
RecordStarter::~RecordStarter(){

}
void RecordStarter::setRecordDir( QString dirName_){
    dirName=dirName_;
}
QString RecordStarter::start_record(){
    fileName=QDateTime::currentDateTime().toString("yyyy-mm-dd-hh-mm-ss") + ".bag";
    return fileName;
}

QString RecordStarter::stop_record(){
    return dirName;
}
