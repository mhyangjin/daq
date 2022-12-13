//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : TopicsViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  :  토픽들의 window controll class
//======================================================================*/
#include "TopicsViewer.h"

TopicsViewer::TopicsViewer(Ui::DaqMain* ui, SignalsSlot* _topicSubscribers, QString _title)
:DAQViz(ui, _title),
topicSubscribers(_topicSubscribers )
{
    DAQViz::buttonState=ButtonState::OFF;
    QObject::connect(topicSubscribers, &SignalsSlot::dataUpdated, this, &TopicsViewer::on_data_update_triggered);
    //QStringListModel* qstringList=topicSubscribers->getListModel();
    qstringList=new QStringListModel();
    qlistView.setModel(qstringList);
    //DAQViz::display_layout.addWidget(&qlistView);
    qlistView.hide();
    ROS_INFO("DAQ: Topic viewer is ready: %s",qPrintable(_title) );
}

TopicsViewer::~TopicsViewer() {

}

void TopicsViewer::showWindow() {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,0);
    ui->rviz_layout->addWidget(&qlistView,1,0);
    DAQViz::title->show();
    qlistView.show();
    ui->rviz_layout->update();

}


void TopicsViewer::showWindow(int xpos, int ypos) {
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
    topicSubscribers->reset();
    ui->rviz_layout->removeWidget(DAQViz::title);
    ui->rviz_layout->removeWidget(&qlistView);
    ui->rviz_layout->update();
}

void TopicsViewer::on_data_update_triggered(const QString& data) {
    //ROS_INFO("DAQ: Topic viewer is data: %s",qPrintable(data) );
    if (DAQViz::buttonState) {
        QStringList list(data);
        qstringList->setStringList(list);
    }
}