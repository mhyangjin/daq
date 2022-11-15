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
    vector<string> topics;
    topics.push_back("/front_camera/image_raw");
    topics.push_back("/right_camera/image_raw");
    topics.push_back("/left_camera/image_raw");
    topics.push_back("/os_cloud_node/points");
    topics.push_back("/right_velodyne/velodyne_points");
    topics.push_back("/left_velodyne/velodyne_points");
    topics.push_back("/gps/fix");
    topics.push_back("/gps/imu");
    topics.push_back("/can");
    topics.push_back("/rosout");
    topics.push_back("/rosout_agg");
    
    //rosbag의 기본 옵션은 record.sh 에 세팅된 값과 일치함
    //rosbag record -b 0 --duration=10
    options.buffer_size=0;          //rosbag -b 0 (0=infinite)
    ros::Duration duration(10,0); //ros::Duration(sec, nsec)
    options.max_duration=duration;
    options.topics=topics;
    recorder=new DaqRecorder( options);
    
}
RecordStarter::~RecordStarter(){

}
void RecordStarter::run() {
    cout <<"RecordStarter::run()" <<endl;
    recorder->run();
    cout <<"RecordStarter::stop()" <<endl;

}
void RecordStarter::setRecordDir( QString dirName_){
    dirName=dirName_;
}
/// @brief 
/// @return 
QString RecordStarter::start_record(){
    fileName=QDateTime::currentDateTime().toString("yyyy-mm-dd-hh-mm-ss") + ".bag";
    cout << "DIR:" << qPrintable(dirName) <<"RECORD FILENAME:" << qPrintable(fileName) <<endl;
    options.prefix=qPrintable(dirName + "/"+fileName);
    options.node="Recorder";
    options.append_date=false;
    recorder->reSet(options);
    this->start(); 
    return fileName;
}

QString RecordStarter::stop_record(){
    cout <<"record shutdown"<<endl;
    recorder->stopRecorder(true);
    //delete recorder;
    return dirName;
}
