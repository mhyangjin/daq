//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RecordPlayer
//   Author     : mhjin julu1@naver.com
//   Class Def  : Record Player
//======================================================================*/
#include "RecordPlayer.h"
#include <rosbag/player.h>

RecordPlayer::RecordPlayer() 
:my_pid(0){

}
RecordPlayer::~RecordPlayer()  {
    stopReplay();
}
void RecordPlayer::startReplay(QString _bagFile){
    bagFile=_bagFile.toStdString();
    this->start();
}
void RecordPlayer::stopReplay(){
    string args="pkill play";
    system(args.data());
}  
void RecordPlayer::run(){
    string args="./scripts/replay.sh " + bagFile;
    system(args.data());
}
