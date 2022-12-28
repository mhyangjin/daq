//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : RvizViewer
//   Author     : mhjin julu1@naver.com
//   Class Def  : Rviz file로부터 영상이미지를 위한 윈도우 콘트롤 클래스
//======================================================================*/
#ifndef RVIZVIEWER_H
#define RVIZVIEWER_H
#include "init.h"
#include "DAQViz.h"
#include "DaqVisualizationManager.h"
#include <rviz/render_panel.h>
#include <rviz/config.h>
#include <yaml-cpp/yaml.h>

class RvizViewer :public DAQViz{
public:
    RvizViewer(Ui::DaqMain*,QString,QString, int, int, int);
    ~RvizViewer();

    virtual void showWindow();
    virtual void showWindow(int, int,bool interval=false);
    virtual void closeWindow();

private:
    DaqVisualizationManager* manager=NULL;
    rviz::RenderPanel* panel_=NULL;
    rviz::Config config;
    QString rvizName;
};
#endif