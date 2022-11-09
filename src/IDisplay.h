//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : IDisplay
//   Author     : mhjin julu1@naver.com
//   Class Def  : .rviz Display를  rendering하여 GUI로 보내기 위한 최상위 Interface.
//                sensor 별로 이 인터페이스를 상속받아 하위로 구현한다.
//======================================================================*/

#ifndef IDISPLAY_H
#define IDISPLAY_H
#include "init.h"
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>


class IDisplay {
public:
    virtual rviz::RenderPanel* makeRender()=0;
    virtual void visualManagerStart()=0;
    virtual void visualManagerStop()=0;
protected:
    rviz::VisualizationManager* manager=NULL;
    rviz::RenderPanel* panel=NULL;
};

#endif