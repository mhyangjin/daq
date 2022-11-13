//======================================================================*/
//   Create Date: 2022/11/08
//   ClassName  : SubController
//   Author     : mhjin julu1@naver.com
//   Class Def  : LiDAR_Top을 송출하기 위한 class
//======================================================================*/
#ifndef SUBCONTROLLER_H
#define SUBCONTROLLER_H
#include "init.h"
#include "DAQViz.h"
#include "TopicSubscribers.h"
#include <std_msgs/String.h>

#include <QStringListModel>
#include <QListView>
#include <QThread>


class SubController :public DAQViz {
    Q_OBJECT
private:

public:

    SubController(Ui::DaqMain*,SignalsSlot*, QString);
    ~SubController();
    void clicked();
    virtual void showWindow();
    virtual void closeWindow();
public slots:
    void on_data_update_triggered();

private:
    SignalsSlot*   topicSubscribers;    
    QListView           qlistView; 
};
#endif