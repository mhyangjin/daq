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
    rviz::VisualizationManager* manager=NULL;
    rviz::RenderPanel* panel_=NULL;
    rviz::Config config;
    QString rvizName;
};
#endif