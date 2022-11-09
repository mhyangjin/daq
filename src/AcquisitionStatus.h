//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : AcquisitionStatus
//   Author     : mhjin julu1@naver.com
//   Class Def  : AcquisitionStatus 바의 상태 체크를 위한 클래스
//======================================================================*/
#ifndef ACQUISITIONSTATUS_H
#define ACQUISITIONSTATUS_H
#include <QMainWindow>
#include "init.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DaqMain; }
QT_END_NAMESPACE

class AcquisitionStatus
{
private:
    enum AcquisitonStateEnum {
        DEFAULT=0,
        RUN,
        STOP
    };

public:
    AcquisitionStatus(Ui::DaqMain* daqMain);
    ~AcquisitionStatus();
    void setDefaultImages();
    void setRunStatus(QString);
    void setStopStatus(QString);
private:
    /// @brief 
    Ui::DaqMain* ui;
    const QString img_source[3]={
        ":img/images/state_gray.png",
        ":img/images/state_blue.png",
        ":img/images/state_red.png"
    };
    QMap<QString, QLabel*>* statusLabelMap;
};
#endif // DAQMAIN_H
