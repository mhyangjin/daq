//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : CameraDisplay
//   Author     : mhjin julu1@naver.com
//   Class Def  : Camera Display를  rendering하여 GUI로 보내기 위한 class
//======================================================================*/

#ifndef DAQCAMERADISPLAY_H
#define DAQCAMERADISPLAY_H
#include "init.h"
#include "DAQViz.h"
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/config.h>
#include <yaml-cpp/yaml.h>


class DaqCameraDisplay : public DAQViz{
public:
    DaqCameraDisplay(Ui::DaqMain*,QString, QString);
    DaqCameraDisplay(Ui::DaqMain*,QString, QString, int xpos, int ypos);
    ~DaqCameraDisplay();

    void clicked();
    virtual void showWindow();
    virtual void closeWindow();

private:
    private:
    void loadConfig( QString,rviz::Config*);
    //verify loading config from .rviz
    void printConfig(rviz::Config*);
    //test reading from .rviz
    void printNodes(YAML::Node*);
    //load config from .rviz file
    void loadNodes(YAML::Node*, rviz::Config*);

    rviz::VisualizationManager* manager=NULL;
    rviz::RenderPanel* panel_=NULL;
    QString rvizName;
    rviz::Config config;
};
#endif