// Copyright 2026 czy
// SPDX-License-Identifier: LicenseRef-Proprietary

#ifndef HUMANOID_DRIVER_INTERFACE__TYPES_HPP_
#define HUMANOID_DRIVER_INTERFACE__TYPES_HPP_

#include <chrono>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace humanoid_driver_interface
{

enum class DriverError : std::uint8_t
{
  kNone = 0,
  kInvalidConfiguration,
  kInvalidState,
  kNotConnected,
  kNotActive,
  kCommunication,
  kRejectedCommand,
  kInternal,
  // A ROS-backed driver may need to wait for its first valid state sample after activation.
  // This is transient during its configured startup grace period; it is not a hardware fault.
  kNoFeedback,
};

struct DriverResult
{
  bool successful{true};
  DriverError error{DriverError::kNone};
  std::string message;

  explicit operator bool() const noexcept {return successful;}

  static DriverResult success(std::string detail = {})
  {
    return DriverResult{true, DriverError::kNone, std::move(detail)};
  }

  static DriverResult failure(DriverError code, std::string detail)
  {
    return DriverResult{false, code, std::move(detail)};
  }
};

// The logical name is exposed on ROS topics. The vendor fields are populated from YAML and are
// only interpreted by a driver plugin.
struct JointMapping
{
  std::string logical_name;
  std::string vendor_name;
  std::string vendor_group;

  // The plugin converts a vendor position to the logical SI position as
  // logical_position_rad = vendor_to_logical_scale * vendor_position +
  // vendor_to_logical_offset_rad. The scale must be finite and non-zero. These defaults cover
  // the normal radians-to-radians, same-direction case. Velocity and acceleration use the same
  // scale; effort is transformed according to virtual work.
  double vendor_to_logical_scale{1.0};
  double vendor_to_logical_offset_rad{0.0};
};

struct DriverConfiguration
{
  std::vector<JointMapping> joints;

  // Plugin-specific settings use text values so the plugin contract stays independent of ROS.
  // The generic node accepts these as YAML strings in the form "key=value". Any physical value
  // in this map must use the SI base/derived unit named by its key (for example, latency_s).
  std::unordered_map<std::string, std::string> parameters;
};

// All values crossing the plugin boundary use SI units:
// position [rad], velocity [rad/s], acceleration [rad/s^2], and effort [N*m].
struct JointCommand
{
  std::vector<std::string> joint_names;
  std::vector<std::string> vendor_joint_names;
  std::vector<std::string> vendor_groups;
  std::vector<double> positions;
  std::vector<double> velocities;
  std::vector<double> accelerations;
  std::vector<double> efforts;
};

struct JointState
{
  std::vector<std::string> joint_names;
  std::vector<double> positions;
  std::vector<double> velocities;
  std::vector<double> efforts;
  std::chrono::steady_clock::time_point sample_time{std::chrono::steady_clock::now()};
};

enum class HealthLevel : std::uint8_t
{
  kOk = 0,
  kWarning = 1,
  kError = 2,
  kStale = 3,
};

struct DriverHealth
{
  HealthLevel level{HealthLevel::kStale};
  bool communication_ok{false};
  bool connected{false};
  bool active{false};
  std::string message{"not configured"};
  std::unordered_map<std::string, std::string> details;
};

}  // namespace humanoid_driver_interface

#endif  // HUMANOID_DRIVER_INTERFACE__TYPES_HPP_
