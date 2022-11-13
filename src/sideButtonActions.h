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
#include "RvizController.h"
#include "RecordStarter.h"

class SideButtonActions {
public:
    SideButtonActions(Ui::DaqMain *);
    void createRvizViewers();
    void createTopicSubViewers();
    void acquisitionClicked(QString);
    void allViewClicked();
    void cameraClicked();
    void carInfoClicked();
    void gpsClicked();
    void imuClicked();
    void lidarSideClicked();
    void lidarTopClicked();
    void radarClicked();
    void startClicked();
    void stopClicked();    
private:
    void allStart(QString );
    void allStop(QString );
    Ui::DaqMain *ui;
    QMap <QString, QList<DAQViz*>* > *rvizMap;
    ros::MultiThreadedSpinner* spiner=NULL;
    RecordStarter recordStarter;
    
};
#endif