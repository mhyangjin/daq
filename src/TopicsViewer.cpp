//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : TopicsViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  :  VisualizationManager
//                를 통해 GUI로 보내기 위한  class.
//                sensor 별로 이 클래스를 상속받아 하위로 구현한다.
//======================================================================*/
#include "TopicsViewer.h"

TopicsViewer::TopicsViewer(Ui::DaqMain* ui, SignalsSlot* _topicSubscribers, QString _title)
:DAQViz(ui, _title),
topicSubscribers(_topicSubscribers )
{
    QObject::connect(topicSubscribers, &SignalsSlot::dataUpdated, this, &TopicsViewer::on_data_update_triggered);
    QStringListModel* qstringList=topicSubscribers->getListModel();
    qlistView.setModel(qstringList);
    //DAQViz::display_layout.addWidget(&qlistView);
    qlistView.hide();
}

TopicsViewer::~TopicsViewer() {

}


void TopicsViewer::showWindow() {
    cout << "TopicsViewer::start() " <<endl;
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,0);
    ui->rviz_layout->addWidget(&qlistView,1,0);
    
    DAQViz::title->show();
    qlistView.show();
    ui->rviz_layout->update();
    
}


void TopicsViewer::showWindow(int xpos, int ypos) {
    cout << "TopicsViewer::start() " <<endl;
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,xpos-1,ypos);
    ui->rviz_layout->addWidget(&qlistView,xpos,ypos);
    
    DAQViz::title->show();
    qlistView.show();
    ui->rviz_layout->update();
    DAQViz::buttonState=ButtonState::ON;
}

void TopicsViewer::closeWindow() {
    cout << "TopicsViewer::stop() " <<endl;
    DAQViz::buttonState=ButtonState::OFF;
    DAQViz::title->hide();
    qlistView.hide();
    
    ui->rviz_layout->removeWidget(DAQViz::title);
    ui->rviz_layout->removeWidget(&qlistView);
    ui->rviz_layout->update();
}

void TopicsViewer::on_data_update_triggered() {
    if (DAQViz::buttonState) {
        qlistView.scrollToBottom();
    }
}