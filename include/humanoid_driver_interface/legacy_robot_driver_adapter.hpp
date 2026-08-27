// Copyright 2026 czy
// SPDX-License-Identifier: LicenseRef-Proprietary

#ifndef HUMANOID_DRIVER_INTERFACE__LEGACY_ROBOT_DRIVER_ADAPTER_HPP_
#define HUMANOID_DRIVER_INTERFACE__LEGACY_ROBOT_DRIVER_ADAPTER_HPP_

#include <memory>
#include <utility>

#include "humanoid_driver_interface/robot_driver_plugin.hpp"

namespace robo_manip::execution
{
class RobotDriver;
}  // namespace robo_manip::execution

namespace humanoid_driver_interface
{

// Reserved integration seam for the original robo_manip::execution::RobotDriver. This declaration
// deliberately owns no Demo headers and creates no link dependency. A future vendor package can
// implement this adapter against the production SDK without contaminating the generic interface.
class LegacyRobotDriverAdapter : public RobotDriverPlugin
{
public:
  ~LegacyRobotDriverAdapter() override = default;

protected:
  explicit LegacyRobotDriverAdapter(
    std::shared_ptr<robo_manip::execution::RobotDriver> legacy_driver)
  : legacy_driver_(std::move(legacy_driver)) {}

  std::shared_ptr<robo_manip::execution::RobotDriver> legacy_driver_;
};

}  // namespace humanoid_driver_interface

#endif  // HUMANOID_DRIVER_INTERFACE__LEGACY_ROBOT_DRIVER_ADAPTER_HPP_
