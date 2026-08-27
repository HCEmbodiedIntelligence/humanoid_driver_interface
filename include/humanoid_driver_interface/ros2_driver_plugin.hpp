// Copyright 2026 czy
// SPDX-License-Identifier: LicenseRef-Proprietary

#ifndef HUMANOID_DRIVER_INTERFACE__ROS2_DRIVER_PLUGIN_HPP_
#define HUMANOID_DRIVER_INTERFACE__ROS2_DRIVER_PLUGIN_HPP_

#include "humanoid_driver_interface/robot_driver_plugin.hpp"

namespace rclcpp
{
class Node;
}  // namespace rclcpp

namespace humanoid_driver_interface
{

// Optional extension for plugins that communicate with a vendor ROS 2 driver. The generic
// contract deliberately remains usable by non-ROS SDK drivers; DriverRuntime only calls this
// method when the selected plugin implements this extension.
class Ros2DriverPlugin : public RobotDriverPlugin
{
public:
  ~Ros2DriverPlugin() override = default;

  // The runtime owns the node lifetime. Plugins must not add it to another executor or spin it.
  virtual DriverResult attachRosNode(rclcpp::Node & node) = 0;
};

}  // namespace humanoid_driver_interface

#endif  // HUMANOID_DRIVER_INTERFACE__ROS2_DRIVER_PLUGIN_HPP_
