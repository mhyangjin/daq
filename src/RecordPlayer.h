//======================================================================*/
//   Create Date: 2022/11/19
//   ClassName  : RecordPlayer
//   Author     : mhjin julu1@naver.com
//   Class Def  : Record Player
//======================================================================*/
#ifndef RECORD_PLAYER_H
#define RECORD_PLAYER_H
#include "init.h"
#include <QThread>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ros/ros.h>
#include <ros/console.h>

class RecordPlayer : public QThread {
public:
    RecordPlayer();
    ~RecordPlayer();
    void startReplay(QString );
    void stopReplay();
private:
    void run( );


    string  bagFile;
    pid_t   my_pid;
};
#endif