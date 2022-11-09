//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : DAQCameraDisplay
//   Author     : mhjin julu1@naver.com
//   Class Def  : Camera Display를  rendering하여 GUI로 보내기 위한 class
//======================================================================*/
#include "DaqCameraDisplay.h"
#include <rviz/image/image_display_base.h>

using namespace rviz;
// CameraDisplay::CameraDisplay() {
//     IDisplay::panel= new rviz::RenderPanel();  
//     IDisplay::manager= new rviz::VisualizationManager(IDisplay::panel);

// }
// CameraDisplay::~CameraDisplay(){
//     delete IDisplay::panel;
//     delete IDisplay::manager;
// }
// rviz::RenderPanel* CameraDisplay::makeRender(){

//     IDisplay::panel->initialize(IDisplay::manager->getSceneManager(), manager);
//     IDisplay::manager->initialize();  
//     return panel;
// }
// void CameraDisplay::visualManagerStart(){
//     IDisplay::manager->startUpdate();
//     rviz::CameraDisplay* front_camera=(rviz::CameraDisplay* )IDisplay::manager->createDisplay("rviz/Image","front_camera", true);
//     front_camera->setTopic("/front_camera/image_raw","raw");
// }
// void CameraDisplay::visualManagerStop(){
//     IDisplay::manager->stopUpdate();
//     IDisplay::manager->removeAllDisplays();

// }

 

 DAQCameraDisplay::DAQCameraDisplay()
 {
   rviz::CameraDisplay::image_position_property_ =
       new EnumProperty("Image Rendering", BOTH,
                        "Render the image behind all other geometry or overlay it on top, or both.", this,
                        SLOT(rviz::CameraDisplay::forceRender()));
   rviz::CameraDisplay::image_position_property_->addOption(BACKGROUND);
   rviz::CameraDisplay::image_position_property_->addOption(OVERLAY);
   rviz::CameraDisplay::image_position_property_->addOption(BOTH);
  
   rviz::CameraDisplay::alpha_property_ = new FloatProperty(
       "Overlay Alpha", 0.5,
       "The amount of transparency to apply to the camera image when rendered as overlay.", this,
       SLOT(rviz::CameraDisplay::updateAlpha()));
   rviz::CameraDisplay::alpha_property_->setMin(0);
   rviz::CameraDisplay::alpha_property_->setMax(1);
  
   rviz::CameraDisplay::zoom_property_ = new FloatProperty(
       "Zoom Factor", 1.0,
       "Set a zoom factor below 1 to see a larger part of the world, above 1 to magnify the image.", this,
       SLOT(rviz::CameraDisplay::forceRender()));
   rviz::CameraDisplay::zoom_property_->setMin(0.00001);
   rviz::CameraDisplay::zoom_property_->setMax(100000);
 }
  /*
 DAQCameraDisplay::~DAQCameraDisplay()
 {
   if (initialized())
   {
     render_panel_->getRenderWindow()->removeListener(this);
  
     CameraDisplay::unsubscribe();
  
     delete render_panel_;
     delete bg_screen_rect_;
     delete fg_screen_rect_;
  
     removeAndDestroyChildNode(bg_scene_node_->getParentSceneNode(), bg_scene_node_);
     removeAndDestroyChildNode(fg_scene_node_->getParentSceneNode(), fg_scene_node_);
  
     context_->visibilityBits()->freeBits(vis_bit_);
   }
 }
 */
  