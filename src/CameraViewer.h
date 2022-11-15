//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : CameraDisplay
//   Author     : mhjin julu1@naver.com
//   Class Def  : Camera Display를  rendering하여 GUI로 보내기 위한 class
//======================================================================*/

#ifndef CameraViewer_H
#define CameraViewer_H
#include "init.h"
#include "DAQViz.h"
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/config.h>
#include <yaml-cpp/yaml.h>
#include <QLabel>
#include <QStringList>


class CameraViewer : public DAQViz{
public:
    CameraViewer(Ui::DaqMain*,QString, QString);
    ~CameraViewer();

    virtual void showWindow();
    virtual void showWindow(int , int);
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

    void buildDisplay(rviz::Config* );

    rviz::VisualizationManager* managers[3];
    rviz::RenderPanel* panels[3];
    rviz::Display* displays[3];
    QLabel* titleLabels[3];
    QString rvizName;
    rviz::Config config;
    QStringList cameraTitles={"front", "left", "right"};
};
#endif