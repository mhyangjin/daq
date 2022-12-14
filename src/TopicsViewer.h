//======================================================================*/
//   Create Date: 2022/11/08
//   ClassName  : TopicsViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  : 토픽들의 window controll class
//======================================================================*/
#ifndef TopicsViewer_H
#define TopicsViewer_H
#include "init.h"
#include "DAQViz.h"
#include "TopicSubscribers.h"
#include <std_msgs/String.h>

#include <QStringListModel>
#include <QListView>
#include <QThread>


class TopicsViewer :public DAQViz {
    Q_OBJECT
private:

public:

    TopicsViewer(Ui::DaqMain*,SignalsSlot*, QString, int, int, int);
    ~TopicsViewer();
    virtual void showWindow();
    virtual void showWindow(int, int,bool interval=false);
    virtual void closeWindow();
    

public slots:
    void on_data_update_triggered( const QString&);

private:


    SignalsSlot*   topicSubscribers;
    QListView           qlistView;
    QStringListModel qstringList;
    bool            interval_mode;
};
#endif