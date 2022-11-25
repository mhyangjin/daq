//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : RvizViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  :Rviz file로부터 영상이미지를 위한 윈도우 콘트롤 클래스ㄴ
//======================================================================*/
#include "RvizViewer.h"
#include "YmlLoader.h"

RvizViewer::RvizViewer(Ui::DaqMain* ui, QString _rvizName,QString _title)
:DAQViz(ui, _title),
rvizName(_rvizName)
{
    YmlLoader::loadConfig(rvizName, &config);
    if ( !config.isValid()) {
        exit(-1);
    }
    panel_= new rviz::RenderPanel();
    manager= new rviz::VisualizationManager(panel_);

    rviz::Config childConfig=config.mapGetChild("Visualization Manager");
    if ( childConfig.isValid()) {
        ROS_DEBUG("showRviz:Visualization Manager is Valid! : %s ",qPrintable(rvizName));
    }
    panel_->initialize(manager->getSceneManager(), manager);
    manager->initialize();
    manager->load(childConfig);
    //DAQViz::display_layout.addWidget(panel_);
    //panel_->hide();
}

RvizViewer::~RvizViewer() {
    delete panel_;
    delete manager;
}

void RvizViewer::showWindow() {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title,0,0);
    ui->rviz_layout->addWidget(panel_,1,0);
    manager->startUpdate();
    DAQViz::title->show();
    panel_->show();
    ui->rviz_layout->update();

}

void RvizViewer::showWindow(int xpos, int ypos) {
    DAQViz::buttonState=ButtonState::ON;
    ui->rviz_layout->addWidget(DAQViz::title, xpos-1, ypos);
    ui->rviz_layout->addWidget(panel_, xpos, ypos);
    manager->startUpdate();
    DAQViz::title->show();
    panel_->show();
    ui->rviz_layout->update();
}

void RvizViewer::closeWindow(){
    DAQViz::buttonState=ButtonState::OFF;
    DAQViz::title->hide();
    panel_->hide();
    manager->stopUpdate();
    ui->rviz_layout->removeWidget(DAQViz::title);
    ui->rviz_layout->removeWidget(panel_);
    ui->rviz_layout->update();

}
