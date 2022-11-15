//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : RvizViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  : LiDAR_Top을 송출하기 위한 class
//======================================================================*/
#ifndef RVIZVIEWER_H
#define RVIZVIEWER_H
#include "init.h"
#include "DAQViz.h"
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/config.h>
#include <yaml-cpp/yaml.h>

class RvizViewer :public DAQViz{
public:
    RvizViewer(Ui::DaqMain*,QString,QString);
    ~RvizViewer();

    virtual void showWindow();
    virtual void showWindow(int, int );
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
    rviz::Config config;
    QString rvizName;
};
#endif