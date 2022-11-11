//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : SubController
//   Author     : mhjin julu1@naver.com
//   Class Def  :  VisualizationManager
//                를 통해 GUI로 보내기 위한  class.
//                sensor 별로 이 클래스를 상속받아 하위로 구현한다.
//======================================================================*/
#include "SubController.h"

RosDaqSub::RosDaqSub(QString rvizName,ros::MultiThreadedSpinner* _spiner) 
:spiner(_spiner){ 
    ros::start(); 
    subscriber = nodeHandle.subscribe(qPrintable(rvizName), 1000, &
RosDaqSub::subscribeCallBack,this );
    this->start();
        
}

void RosDaqSub::run() {
    spiner->spin();
}
QStringListModel*  RosDaqSub::getListModel() {
    return &qstringList;
}
void RosDaqSub::subscribeCallBack(const std_msgs::String::ConstPtr& messages) {
    cout<<"subscribeCallBack" << messages->data.c_str()<<endl;
    QVariant new_data(QString(messages->data.c_str()));
    qstringList.insertRows(qstringList.rowCount(), 1);
    qstringList.setData(qstringList.index(qstringList.rowCount()-1), new_data);
    Q_EMIT dataUpdated();
}


SubController::SubController(Ui::DaqMain* ui, QString _rvizName, QString _title, ros::MultiThreadedSpinner* spnner)
:DAQViz(ui, _rvizName,_title),
rosDaqSub(new RosDaqSub(_rvizName, spnner) )
{
    QObject::connect(rosDaqSub, &RosDaqSub::dataUpdated, this, &SubController::on_data_update_triggered);
    QStringListModel* qstringList=rosDaqSub->getListModel();
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
    cout << "SubController::start() " << qPrintable(DAQViz::rvizName)<<endl;

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