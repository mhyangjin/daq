//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : RvizController
//   Author     : mhjin julu1@naver.com
//   Class Def  : LiDAR_Top을 송출하기 위한 class
//======================================================================*/
#ifndef LIDARTOP_H
#define LIDARTOP_H
#include "init.h"
#include "DAQViz.h"
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/config.h>
#include <yaml-cpp/yaml.h>

class RvizController :public DAQViz{
public:
    RvizController(Ui::DaqMain*,QString,QString);
    RvizController(Ui::DaqMain*,QString, QString,int xpos, int ypos);
    ~RvizController();

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
    rviz::Config config;
    int xpos=0;
    int ypos=0;
};
#endif