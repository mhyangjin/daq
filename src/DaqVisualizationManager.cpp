/*
 * Copyright (c) 2008, Willow Garage, Inc.
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
#include "DaqVisualizationManager.h"
#include <algorithm>

#include <QApplication>
#include <QCursor>
#include <QPixmap>
#include <QTimer>
#include <QWindow>

#include <boost/bind/bind.hpp>

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreViewport.h>
#include <OgreMaterialManager.h>
#include <OgreMaterial.h>
#include <OgreRenderWindow.h>
#include <OgreSharedPtr.h>
#include <OgreCamera.h>

#include <boost/filesystem.hpp>
#include <utility>

#include <ros/package.h>
#include <ros/callback_queue.h>

#include <rviz/display.h>
#include <rviz/display_factory.h>
#include <rviz/display_group.h>
#include <rviz/displays_panel.h>
#include <rviz/frame_manager.h>
#include <rviz/ogre_helpers/qt_ogre_render_window.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/parse_color.h>
#include <rviz/properties/property.h>
#include <rviz/properties/property_tree_model.h>
#include <rviz/properties/status_list.h>
#include <rviz/properties/tf_frame_property.h>
#include <rviz/properties/int_property.h>
#include <rviz/render_panel.h>
#include <rviz/selection/selection_manager.h>
#include <rviz/tool.h>
#include <rviz/tool_manager.h>
#include <rviz/viewport_mouse_event.h>
#include <rviz/view_controller.h>
#include <rviz/view_manager.h>
#include <rviz/load_resource.h>
#include <rviz/ogre_helpers/ogre_render_queue_clearer.h>
#include <rviz/ogre_helpers/render_system.h>

#include <rviz/window_manager_interface.h>

class DaqVisualizationManagerPrivate
{
public:
  ros::CallbackQueue threaded_queue_;
  boost::thread_group threaded_queue_threads_;
  ros::NodeHandle update_nh_;
  ros::NodeHandle threaded_nh_;
  boost::mutex render_mutex_;
};

DaqVisualizationManager::DaqVisualizationManager(RenderPanel* render_panel,
                                           WindowManagerInterface* wm,
                                           std::shared_ptr<tf2_ros::Buffer> tf_buffer,
                                           std::shared_ptr<tf2_ros::TransformListener> tf_listener)
  : VisualizationManager(render_panel, wm,tf_buffer, tf_listener )
{
  
}

DaqVisualizationManager::~DaqVisualizationManager()
{

}


void DaqVisualizationManager::load(const Config& config)
{
  stopUpdate();

  emitStatusUpdate("Creating tools");
  tool_manager_->load(config.mapGetChild("Tools"));

  emitStatusUpdate("Creating views");
  view_manager_->load(config.mapGetChild("Views"));

  startUpdate();
}


void DaqVisualizationManager::addDisplay(Display* display, bool enabled)
{
  root_display_group_->addDisplay(display);
}