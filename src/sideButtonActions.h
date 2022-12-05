//======================================================================*/
//   Create Date: 2022/11/6
//   ClassName  : SideButtonActions
//   Author     : mhjin julu1@naver.com
//   Class Def  : side button을 클릭했을 때 수행할 동작들
//======================================================================*/
#ifndef SIDEBUTTIONASCTIONS_H
#define SIDEBUTTIONASCTIONS_H
#include <QMainWindow>
#include <QPixmap>
#include "init.h"
#include "AcquisitionStatus.h"
#include "DAQViz.h"
#include "RvizViewer.h"
#include "RecordStarter.h"
#include "ConfigLoader.h"
#include "RosRunManager.h"
#include "RecordPlayer.h"
#include "RosRunner.h"

class SideButtonActions {
public:
    SideButtonActions(Ui::DaqMain *);
    ~SideButtonActions();
    void createRvizViewers();
    void createTopicSubViewers();

    bool sensorStart();
    void sensorStop();
    bool replayStart(QString file);
    void replayStop();


    void allViewClicked();
    void cameraClicked();
    void carInfoClicked();
    void gpsClicked();
    void imuClicked();
    void lidarSideClicked();
    void lidarTopClicked();
    void radarClicked();

    QString recordStart(QString);
    void recordStop();
    
private:
    void allStart(QString );
    void allStop(QString );
    Ui::DaqMain *ui;
    ConfigLoader config;
    QMap <QString, QList<DAQViz*>* > rvizMap;
    ros::MultiThreadedSpinner* spiner=NULL;
    RecordStarter recordStarter;
    RosRunner rosRunner;
    RecordPlayer recordPlayer;

};
#endif