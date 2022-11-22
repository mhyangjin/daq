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
#include "ConfigLoader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DaqMain; }
QT_END_NAMESPACE


class Daqmain : public QMainWindow
{
Q_OBJECT
    public slots:
    void radioSensorClicked();
    void radioReplayClicked();
    void replayFileClicked();
    void runClicked();
    void stopClicked();
    void allViewClicked();
    void cameraClicked();
    void carInfoClicked();
    void gpsClicked();
    void imuClicked();
    void lidarSideClicked();
    void lidarTopClicked();
    void radarClicked();
    void recordClicked();
    void recordStartClicked();
    void recordStopClicked();
    void actionConfigrations();
    void allViewEnabled();
    void allViewDisabled();
public:
    void closeEvent(QCloseEvent *event);
    Daqmain(QWidget *parent = nullptr);
    ~Daqmain();


private:
    Ui::DaqMain *ui;
    SideButtonActions *sideButtonActions;
    AcquisitionStatus *acquisitionStatus;
    ConfigLoader config;
    QLabel *statusMsg;

};
#endif // DAQMAIN_H
