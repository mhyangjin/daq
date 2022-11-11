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
public:
    DAQViz(Ui::DaqMain*, QString,QString);
    ~DAQViz();
    virtual void showWindow()=0;
    virtual void closeWindow()=0;
    inline ButtonState getButtonState() {return buttonState;};
public:
    QLabel*  title;
protected:
    Ui::DaqMain* ui=NULL;
    ButtonState buttonState;
    QGridLayout display_layout;
    QString rvizName;
};
#endif // DAQVIZ_H
