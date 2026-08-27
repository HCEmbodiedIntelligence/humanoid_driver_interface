// Copyright 2026 czy
// SPDX-License-Identifier: LicenseRef-Proprietary

#ifndef HUMANOID_DRIVER_INTERFACE__ROBOT_DRIVER_PLUGIN_HPP_
#define HUMANOID_DRIVER_INTERFACE__ROBOT_DRIVER_PLUGIN_HPP_

#include "humanoid_driver_interface/types.hpp"

namespace humanoid_driver_interface
{

class RobotDriverPlugin
{
public:
  virtual ~RobotDriverPlugin() = default;

  virtual DriverResult configure(const DriverConfiguration & configuration) = 0;
  virtual DriverResult connect() = 0;
  virtual DriverResult disconnect() = 0;
  virtual DriverResult activate() = 0;
  virtual DriverResult deactivate() = 0;

  virtual DriverResult readJointState(JointState & state) = 0;
  virtual DriverResult startJointStream() = 0;
  virtual DriverResult writeJointCommand(const JointCommand & command) = 0;
  virtual DriverResult stopJointStream() = 0;

  // stopAll() is the safety path. Implementations must make it idempotent and must hold the
  // current position (or use an equally safe device-specific stop) before returning success.
  virtual DriverResult stopAll() = 0;
  virtual DriverHealth health() = 0;
};

}  // namespace humanoid_driver_interface

#endif  // HUMANOID_DRIVER_INTERFACE__ROBOT_DRIVER_PLUGIN_HPP_
