//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : CameraDisplay
//   Author     : mhjin julu1@naver.com
//   Class Def  : Camera Display를  rendering하여 GUI로 보내기 위한 class
//======================================================================*/

#ifndef DAQCAMERADISPLAY_H
#define DAQCAMERADISPLAY_H
#include "IDisplay.h"
#include <rviz/default_plugin/camera_display.h>

class DAQCameraDisplay : public rviz::CameraDisplay{
Q_OBJECT
public:
    DAQCameraDisplay() ;
    ~DAQCameraDisplay() ;
    // virtual rviz::RenderPanel* makeRender();
    // virtual void visualManagerStart();
    // virtual void visualManagerStop();
};
#endif