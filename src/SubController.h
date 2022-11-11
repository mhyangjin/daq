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
#include <ros/ros.h>
#include <ros/network.h>
#include <std_msgs/String.h>
#include <QStringListModel>
#include <QListView>
#include <QThread>
class RosDaqSub : public QThread {
    Q_OBJECT
public:
    RosDaqSub(QString,ros::MultiThreadedSpinner* );
    void subscribeCallBack(const std_msgs::String::ConstPtr& messages);
    void run();
    QStringListModel* getListModel();
signals:
    void dataUpdated();
private:
    ros::Subscriber subscriber;
    ros::NodeHandle nodeHandle;
    QStringListModel qstringList;
    ros::MultiThreadedSpinner* spiner;
};

class SubController :public DAQViz {
    Q_OBJECT
private:

public:
    SubController(Ui::DaqMain*,QString, QString, ros::MultiThreadedSpinner* );
    ~SubController();
    void clicked();
    virtual void showWindow();
    virtual void closeWindow();
public slots:
    void on_data_update_triggered();

private:
    RosDaqSub*   rosDaqSub;    
    QListView      qlistView; 
};
#endif