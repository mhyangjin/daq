//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : TopicsViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  :  토픽들의 window controll class
//======================================================================*/
#include "TopicsViewer.h"

TopicsViewer::TopicsViewer(Ui::DaqMain* ui, SignalsSlot* _topicSubscribers, QString _title, int x, int y,int frame)
:DAQViz(ui, _title,x, y, frame),
topicSubscribers(_topicSubscribers )
{
    interval_mode=false;
    DAQViz::buttonState=ButtonState::OFF;
    QObject::connect(topicSubscribers, &SignalsSlot::dataUpdated, this, &TopicsViewer::on_data_update_triggered);
    qlistView.setModel(&qstringList);
    //DAQViz::display_layout.addWidget(&qlistView);
    qlistView.hide();
    ROS_INFO("DAQ: Topic viewer is ready: %s",qPrintable(_title) );
}

TopicsViewer::~TopicsViewer() {

}

void TopicsViewer::showWindow() {
    interval_mode=false;
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,0);
    ui->rviz_layout->addWidget(&qlistView,1,0);
    DAQViz::title->show();
    qlistView.show();
    ui->rviz_layout->update();

}


void TopicsViewer::showWindow(int xpos, int ypos, bool interval) {
   interval_mode=interval;
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,xpos-1,ypos);
    ui->rviz_layout->addWidget(&qlistView,xpos,ypos);
    DAQViz::title->show();
    qlistView.show();
    ui->rviz_layout->update();
}


void TopicsViewer::closeWindow() {
    DAQViz::buttonState=ButtonState::OFF;
    DAQViz::title->hide();
    qlistView.hide();
    QStringList list("");
    qstringList.setStringList(list);
    ui->rviz_layout->removeWidget(DAQViz::title);
    ui->rviz_layout->removeWidget(&qlistView);
    ui->rviz_layout->update();
}

void TopicsViewer::on_data_update_triggered(const QString& data) {
    //ROS_INFO("DAQ: Topic viewer is data: %s",qPrintable(data) );
    static int cnt=0;
    if (DAQViz::buttonState) {
        if ( interval_mode) {
            if ( cnt >= frame_cnt ) {
                ROS_DEBUG("TopicsViewer::showWindow normal %d", cnt);
                QStringList list(data);
                qstringList.setStringList(list);
                cnt=0;
            }
            else {
                ROS_DEBUG("TopicsViewer::showWindow normal--- %d", cnt);
                cnt++;
            }
        }
        else {
            ROS_DEBUG("TopicsViewer::showWindow normal" );
            QStringList list(data);
            qstringList.setStringList(list);
        }
    }
}