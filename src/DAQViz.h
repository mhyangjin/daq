//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : DAQViz
//   Author     : mhjin julu1@naver.com
//   Class Def  : .rviz file을 읽어서 rviz::Config로 만든 후 VisualizationManager
//                를 통해 GUI로 보내기 위한 최상위 class.
//                sensor 별로 이 클래스를 상속받아 하위로 구현한다.
//======================================================================*/
#ifndef DAQVIZ_H
#define DAQVIZ_H
#include "init.h"
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>

class DAQViz: public QObject
{
Q_OBJECT
public slots:
    void stopClicked();
    void allViewClicked();
    void cameraClicked();
    void carInfoClicked();
    void gpsClicked();
    void imuClicked();
    void lidarSideClicked();
    void lidarTopClicked();
    void radarClicked();
    
public:
    DAQViz(Ui::DaqMain*, QString, int,int);
    ~DAQViz();
    void setPosition(int,int);
    virtual void showWindow()=0;
    virtual void showWindow(int, int)=0;
    virtual void closeWindow()=0;
    inline ButtonState getButtonState() {return buttonState;};
public:
    QLabel*  title;
protected:
    Ui::DaqMain* ui=NULL;
    ButtonState buttonState;
    QGridLayout display_layout;
    int posx;
    int posy;

};
#endif // DAQVIZ_H
