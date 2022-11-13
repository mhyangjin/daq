//======================================================================*/
//   Create Date: 2022/11/01
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : DAQ의 MainWindow
//======================================================================*/
#ifndef DAQMAIN_H
#define DAQMAIN_H
#include <QMainWindow>
#include <QPixmap>
#include "AcquisitionStatus.h"
#include "init.h"
#include "sideButtonActions.h"
QT_BEGIN_NAMESPACE
namespace Ui { class DaqMain; }
QT_END_NAMESPACE


class Daqmain : public QMainWindow
{
Q_OBJECT
    public slots:

    void acquisitionClicked();
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


public:
    Daqmain(QWidget *parent = nullptr);
    ~Daqmain();
    

private:
    Ui::DaqMain *ui;
    SideButtonActions *sideButtonActions;
    AcquisitionStatus *acquisitionStatus;

};
#endif // DAQMAIN_H
