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


#ifndef DAQ_VISUALIZATION_MANAGER_H_
#define DAQ_VISUALIZATION_MANAGER_H_

#include <deque>

#include <ros/time.h>
#include <tf2_ros/transform_listener.h>

#include <rviz/bit_allocator.h>
#include <rviz/config.h>
#include <rviz/display_context.h>
#include <rviz/rviz_export.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/tf_frame_property.h>
#include <rviz/properties/status_list.h>
#include <rviz/properties/int_property.h>
#include <rviz/properties/bool_property.h>
#include <rviz/ogre_helpers/ogre_render_queue_clearer.h>
#include <rviz/visualization_manager.h>
#include <rviz/tool.h>
using namespace Ogre;

using namespace ros;

using namespace rviz;
/*
{
class ColorProperty;
class Display;
class DisplayFactory;
class DisplayGroup;
class FrameManager;
class Property;
class BoolProperty;
class IntProperty;
class PropertyTreeModel;
class RenderPanel;
class SelectionManager;
class StatusList;
class TfFrameProperty;
class ViewportMouseEvent;
class WindowManagerInterface;
class Tool;
class OgreRenderQueueClearer;

class VisualizationManagerPrivate;

};*/

// namespace rviz
/**
 * \brief The VisualizationManager class is the central manager class
 *        of rviz, holding all the Displays, Tools, ViewControllers,
 *        and other managers.
 *
 * It keeps the current view controller for the main render window.
 * It has a timer which calls update() on all the displays.  It
 * creates and holds pointers to the other manager objects:
 * SelectionManager, FrameManager, the PropertyManager s, and
 * Ogre::SceneManager.
 *
 * The "protected" members should probably all be "private", as
 * VisualizationManager is not intended to be subclassed.
 */

class DaqVisualizationManager : public VisualizationManager
{
public:
    explicit DaqVisualizationManager(
      RenderPanel* render_panel,
      WindowManagerInterface* wm = nullptr,
      std::shared_ptr<tf2_ros::Buffer> tf_buffer = std::shared_ptr<tf2_ros::Buffer>(),
      std::shared_ptr<tf2_ros::TransformListener> tf_listener =
      std::shared_ptr<tf2_ros::TransformListener>());

 
  ~DaqVisualizationManager();

  void startUpdate_Slow(int);

};


#endif /* RVIZ_VISUALIZATION_MANAGER_H_ */
