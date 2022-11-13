//======================================================================*/
//   Create Date: 2022/11/04
//   ClassName  : DAQViz
//   Author     : mhjin julu1@naver.com
//   Class Def  : .rviz file을 읽어서 rviz::Config로 만든 후 VisualizationManager
//                를 통해 GUI로 보내기 위한 최상위 class.
//                sensor 별로 이 클래스를 상속받아 하위로 구현한다.
//======================================================================*/
#include "DAQViz.h"
#include <QFile>
#include <rviz/yaml_config_reader.h>
#include <rviz/display_group.h>
#include <rviz/config.h>

DAQViz::DAQViz(Ui::DaqMain* daqMain,  QString _title)
:ui(daqMain),
title(new QLabel(_title)),
buttonState(ButtonState::OFF)
{
    title->setMaximumSize(10000,20);
    title->adjustSize();
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);    //display_layout.addWidget(&title);
    title->setAlignment(Qt::AlignCenter);
    title->hide();
}

DAQViz::~DAQViz() {

}
