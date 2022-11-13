//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : SubController
//   Author     : mhjin julu1@naver.com
//   Class Def  :  VisualizationManager
//                를 통해 GUI로 보내기 위한  class.
//                sensor 별로 이 클래스를 상속받아 하위로 구현한다.
//======================================================================*/
#include "SubController.h"

SubController::SubController(Ui::DaqMain* ui, SignalsSlot* _topicSubscribers, QString _title)
:DAQViz(ui, _title),
topicSubscribers(_topicSubscribers )
{
    QObject::connect(topicSubscribers, &SignalsSlot::dataUpdated, this, &SubController::on_data_update_triggered);
    QStringListModel* qstringList=topicSubscribers->getListModel();
    qlistView.setModel(qstringList);
    //DAQViz::display_layout.addWidget(&qlistView);
    qlistView.hide();
}

SubController::~SubController() {

}

void SubController::clicked(){
    cout <<"SubController::clicked()" <<endl;
    if ( buttonState == ButtonState::ON){
        closeWindow();
        DAQViz::buttonState=ButtonState::OFF;
    }
    else {
        showWindow();
        DAQViz::buttonState=ButtonState::ON;
    }
}

void SubController::showWindow() {
    cout << "SubController::start() " <<endl;

    ui->rviz_layout->addWidget(DAQViz::title,0,0);
    ui->rviz_layout->addWidget(&qlistView,1,0);
    
    DAQViz::title->show();
    qlistView.show();
    ui->rviz_layout->update();
    DAQViz::buttonState=ButtonState::ON;
}

void SubController::closeWindow() {
    cout << "SubController::stop() " <<endl;
    DAQViz::title->hide();
    qlistView.hide();
    DAQViz::buttonState=ButtonState::OFF;
    ui->rviz_layout->removeWidget(DAQViz::title);
    ui->rviz_layout->removeWidget(&qlistView);
    ui->rviz_layout->update();
}

void SubController::on_data_update_triggered() {
    if (DAQViz::buttonState) {
        qlistView.scrollToBottom();
    }
}