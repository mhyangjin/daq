
//======================================================================*/
//   Create Date: 2022/11/07
//   ClassName  : CameraDisplay
//   Author     : mhjin julu1@naver.com
//   Class Def  : rviz/default_plugin에 포함된 camera_display를 수정한 클래스
//                 - default camera_display는 윈도우 창을 따로 띄움.
//======================================================================*/
/*
 * Copyright (c) 2012, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <boost/bind/bind.hpp>

#include <OgreManualObject.h>
#include <OgreMaterialManager.h>
#include <OgreRectangle2D.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreTechnique.h>
#include <OgreCamera.h>
#include <OgreRoot.h>
#include <tf2_ros/message_filter.h>

#include <rviz/bit_allocator.h>
#include <rviz/frame_manager.h>
#include <rviz/ogre_helpers/axes.h>
#include <rviz/ogre_helpers/compatibility.h>
#include <rviz/properties/enum_property.h>
#include <rviz/properties/float_property.h>
#include <rviz/properties/int_property.h>
#include <rviz/properties/ros_topic_property.h>
#include <rviz/render_panel.h>
#include <rviz/uniform_string_stream.h>
#include <rviz/validate_floats.h>
#include <rviz/display_context.h>
#include <rviz/properties/display_group_visibility_property.h>
#include <rviz/load_resource.h>

#include <sensor_msgs/CameraInfo.h>
#include <image_transport/camera_common.h>

#include <sensor_msgs/image_encodings.h>
#include "DaqCameraDisplay.h"


DaqCameraDisplay::DaqCameraDisplay(rviz::RenderPanel* panel)
  : ImageDisplay()
{
 
}

DaqCameraDisplay::~DaqCameraDisplay()
{
}

rviz::RenderPanel* DaqCameraDisplay::getRenderPanel() {
  return ImageDisplay::render_panel_;
}

/*
void DaqCameraDisplay::onInitialize(){
  ImageDisplay::onInitialize();
}
void DaqCameraDisplay::update(float wall_dt, float ros_dt){
  ImageDisplay::update(wall_dt, ros_dt);
}
void DaqCameraDisplay::reset(){
  ImageDisplay::reset();
}

void DaqCameraDisplay::onEnable(){
  ImageDisplay::onEnable();
}
void DaqCameraDisplay::onDisable(){
  ImageDisplay::onDisable();
}
void DaqCameraDisplay::processMessage(const sensor_msgs::Image::ConstPtr& msg) {
  ImageDisplay::processMessage( msg) ;
} */