# humanoid_driver_interface

`RobotDriverPlugin` is the hardware-neutral pluginlib contract used by the generic driver node.
The contract has explicit configure/connect/activate and reverse lifecycle operations, separate
stream control, an idempotent safety stop, and health reporting.

All numeric joint data at this boundary is SI: radians, radians per second, radians per second
squared, and newton-metres. `JointMapping` keeps the ROS-facing logical name separate from a
vendor name and vendor group. It can also hold a per-joint affine conversion from a vendor
position convention into logical radians, so a configuration can account for degrees, reversed
axes, and zero offsets without leaking them into the rest of the platform.

`Ros2DriverPlugin` is an optional extension for plugins that adapt vendor ROS 2 topics. The
runtime supplies its existing node; an adapter must not create or spin a private node/executor.

`legacy_robot_driver_adapter.hpp` reserves a dependency-free seam for a future
`robo_manip::execution::RobotDriver` adapter. This package intentionally does not include or link
the legacy Demo tree.
